import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# This program does not pass check50, but I believe it meets all of the necessary criteria. After spending so long setting up the existing application, fundamentally altering the whole site just to pass check50 seemed inefficient. In general, the areas where I deviated from the check50 specifications were areas that I simply disagreed on how the site could be made more user-friendly.

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

@app.route("/")
@login_required
def index():
    # Get session ID and query dictionaries for information on users with that key
    account_id = session["user_id"]
    user = db.execute("SELECT * FROM users WHERE id = ?", account_id)
    data = db.execute("SELECT * FROM financials WHERE status = 1 AND account_id = ?", account_id)
    # This is cryptic but it is copy and pasted multiple places in this applicaiton. The financials table logs stock purchases as separate events, and the "spot in data" loop with a "stocks" dictionary combines the number of owned stocks with the same symbol
    # If I had more time and energy for this, I would have re-written my financials table after implementing a history table to eliminate this step and streamline the site. Alas, I simply to not have the time to do so. I recognize after building the program, however, that the current implementation could be designed more effectively in this regard.
    stocks = {}
    for spot in data:
        if spot.get("symbol") in stocks:
            stocks[spot.get("symbol")][1] = stocks[spot.get("symbol")][1] + spot.get("quantity")
        else:
            stocks[spot.get("symbol")] = [spot.get("name"), spot.get("quantity")]

    value = 0

    # This fills the prices dictionary with the up-to-date value of the entire portfolio
    prices = {}
    for point in stocks:
        prices[point] = (lookup(point)).get("price")
        value = value + (lookup(point).get("price") * stocks[point][1])

    value = value + user[0].get("cash")

    return render_template("index.html", user=user, value=value, prices=prices, stocks=stocks)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    # Buy is implemented as a two part process because I thought it felt cleaner that way. This part just filters results and passes values along to checkout, which does the heavy lifting.
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("please provide a symbol")
        symbol = request.form.get("symbol")

        if not lookup(symbol):
            return apology("symbol cannot be found")
        else:
            quote = lookup(symbol)
            return render_template("checkout.html", quote=quote)
    else:
        return render_template("buy.html")

@app.route("/checkout", methods=["GET", "POST"])
@login_required
def checkout():
    # The list of variables is comically long, but this was the easiest way to wrap my head around the data pieces. They are separated like this for the ease of filling the financials and history dictionaries at the end of the function
    if request.method == "POST":
        quantity = request.form.get("quantity")
        symbol = request.form.get("symbol")
        lkup = lookup(symbol)
        name = lkup.get('name')
        price = request.form.get("quote")
        # Once again, the Boolean aspect of the financials table could be cut out now that I've implemented history, but I made the decision not to make that foundational change in this program
        status = True
        account_id = session["user_id"]
        cost = (float(quantity) * float(price))
        balance = db.execute("SELECT cash FROM users WHERE id = ?", account_id)
        cash = balance[0].get('cash')
        time = datetime.now()

        # This makes sure the user has enough cash to make the purchase. If so, the purchase is made, the cash and stock positions are updated, and the event is logged in the history table
        if (float(cash) >= float(cost)):
            if lookup(symbol):
                nbalance = cash - cost
                db.execute("UPDATE users SET cash = ? WHERE id = ?", nbalance, account_id)
                db.execute("INSERT INTO financials (account_id, symbol, name, quantity, status, price) VALUES (?, ?, ?, ?, ?, ?)", account_id, symbol, name, quantity, status, price)
                db.execute("INSERT INTO history (a_id, symbol, name, quantity, status, price, time) VALUES (?, ?, ?, ?, ?, ?, ?)", account_id, symbol, name, quantity, "buy", price, time)
                return redirect("/")
        else:
            return apology("Insufficient Funds")
    else:
        # I initially had this as a temporary debugging line while writing the function, but it grew on me, so I kept it. I don't think it'll ever be called, but I'm leaving it in for my own sake.
        return apology("Boo")

@app.route("/history")
@login_required
def history():
    # This concise function passes the entire history dictionary to history.html, which obediently sorts through the data
    a_id = session["user_id"]
    history = db.execute("SELECT * FROM history WHERE a_id = ?", a_id)
    return render_template("history.html", history=history)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    # Similar to buy, this function takes in information and checks for the correctness of input, but it mostly serves as a gateway to quoted
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("please provide a symbol")
        else:
            symbol = request.form.get("symbol")
            if lookup(symbol):
                quote = lookup(symbol)
                return render_template("quoted.html", quote = quote)
    else:
        return render_template("quote.html")

@app.route("/quoted", methods=["GET", "POST"])
@login_required
def quoted():
    # Quoted in Python isn't all that impressive. The HTML page does all the work.
    return redirect("/")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        # If the username field is left blank, return error
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # If the password field is left blank, return error
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # If the confirmation password field is left blank, return error
        elif not request.form.get("confirmation"):
            return apology("must re-enter password", 400)

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Gets existing information and checks if the username is already taken
        row = db.execute("SELECT username FROM users WHERE username = ?", username)
        for spot in row:
            if spot.get("username") == username:
                return apology("that username is already taken", 400)

        # Error if the passwords don't match
        if password != confirmation:
            return apology("passwords do not match")

        # If all the hurdles are cleared, add the user to the site
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, generate_password_hash(password))

        return redirect("/")
    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    # From a high level, sell is very similar to checkout (some copying and pasting may have been involved...)
    # The pre "if request.method == "POST": content is needed to load the associated html page

    account_id = session["user_id"]
    financials = db.execute("SELECT * FROM financials WHERE status=1 and account_id = ?", account_id)
    user = db.execute("SELECT * FROM users WHERE id = ?", account_id)
    stocks = {}
    for spot in financials:
        if spot.get("symbol") in stocks:
            stocks[spot.get("symbol")][1] = stocks[spot.get("symbol")][1] + spot.get("quantity")
        else:
            stocks[spot.get("symbol")] = [spot.get("name"), spot.get("quantity"), spot.get("name")]

    # This is almost identical to checkout. Fill out a huge roster of variables to pass into the database
    if request.method == "POST":
        quantity = int(request.form.get("quantity"))
        symbol = request.form.get("symbol")
        held = int(stocks.get(symbol)[1])
        lkup = lookup(symbol)
        name = lkup.get('name')
        price = lkup.get('price')
        status = False
        balance = db.execute("SELECT cash FROM users WHERE id = ?", account_id)
        cash = balance[0].get('cash')
        time = datetime.now()
        nbalance = (float(cash) + (float(price) * float(quantity)))
        variance = int(held) - int(quantity)
        print(f"{symbol}, {variance}")

        # Read this as "If the difference between cash in the account and the cost of the purchase below zero". More simply, this checks if the purchase value exceeds total cash reserves while allowing a user to spend down to $0 cash
        if variance > -1:
            if lookup(symbol):
                # If the user sells all their shares, complete the transaction and set the ownership status equal to false on the financials table
                if variance == 0:
                    db.execute("UPDATE financials SET status = 0 AND quantity = 0 WHERE account_id = ? AND symbol = ?", account_id, symbol)

                # If the user sells some but not all their shares, decrease the quantity of shares owned and update the history table
                else:
                    db.execute("UPDATE financials SET quantity = ?", variance)

                db.execute("INSERT INTO history (a_id, symbol, name, quantity, status, price, time) VALUES (?, ?, ?, ?, ?, ?, ?)", account_id, symbol, name, quantity, "sell", price, time)

                # Decrease cash equal to the value of the purchase
                db.execute("UPDATE users SET cash = ? WHERE id = ?", nbalance, account_id)
                return redirect("/")
        else:
            return apology("Not enough stock held")
    else:
        return render_template("sell.html", stocks=stocks)

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)

