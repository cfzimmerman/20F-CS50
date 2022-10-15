def main():
    # Prompt user for input until an integer value between 1 and 8 is provided
    while True:
        height = input("Height: ")
        if (True == height.isdigit()):
            height = int(height)
            if ((height > 0) and (height < 9)):
                break
    # Print the pyramid. The if/else condition removes an extraneous space at the beginning of each line that arises when the code is  written as a single statement.
    h = "#"
    s = " "
    for i in range(1, (height + 1)):
        if ((height-i) == 0):
            print((h*i), (""), (h*i))
        else:
            print((s*(height-i-1)), (h*i), (""), (h*i))

if __name__ == "__main__":
    main()