-- To see the full thought process from beginning to end, start below and scroll through all three attempts
-- Lines 8 through 57 might be worth reading to see the beginning of the process, while the others below might be unnecessary
-- To see only the successful final attempt, skip to line 335
-- New attempts marked by dividing lines

_____________________________________________________________________

-- Given: July 28, 2020 (7/28/20) on Chamberlin Street

sqlite3 fiftyville.db
-- Enter the database

.tables
-- See the tables in the database: airports, atm_transactions, bank_accounts, courthouse_security_logs, crime_scene_reports, flights, interviews, passengers, people, phone_calls

.schema crime_scene_reports
-- Get a closer look at the layout of the crime scene reports table

SELECT description FROM crime_scene_reports;
-- Looks like a mess

SELECT month, day FROM crime_scene_reports;
-- Get a sense of the date layout

SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND year = 2020;
-- Filter report for crime on given day
-- "Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse. Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse."

SELECT DISTINCT street FROM crime_scene_reports ORDER BY street;
-- Get a sense of the layout of the street table

SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND year = 2020 AND street = "Chamberlin Street";
-- Final check of data from this table. Seems to be recommending looking at the courhouse.

.tables

.schema courthouse_security_logs
-- Check out the courthouse security logs

SELECT hour, minute, id, activity, license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 ORDER BY hour, minute;
-- Get a good look at activity that day including timestamps, ids, activities, and license plates. This query might be more useful later on.
-- Didn't really get much from that.

.tables

.schema interviews
-- Interviews might give more information to help with the courhouse logs

SELECT * FROM interviews;
-- What a mess

SELECT name, id, transcript FROM interviews WHERE year = 2020 AND month = 7 AND day = 28;
-- Read transcripts from the right day
-- Useful Transcripts:
-- Ruth | 161 | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
-- Eugene | 162 | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
-- Raymond | 163 | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

.tables

.schema courthouse_security_logs
-- Find out what time Eugene, ID 162, got to the courthouse to filter the ATM search

SELECT hour, minute, id, activity, license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 ORDER BY id, hour, minute;
-- Eugene's id doesn't show up. That's aggravating. Over to ATM transactions...

.schema atm_transactions
-- Eugene suggested looking at ATM transactions on Fifer Street that morning

SELECT DISTINCT atm_location FROM atm_transactions ORDER BY atm_location; 
-- Get a sense of what we're working with here

SELECT DISTINCT transaction_type FROM atm_transactions ORDER BY transaction_type; 
-- Same as location search

SELECT id FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw";
-- This was awesome. These are how my suspects:
-- ID:
-- 246
-- 264
-- 266
-- 267
-- 269
-- 313
-- 336

SELECT id FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 INTERSECT SELECT id FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw";
-- Suspect list
-- ID:
-- 246
-- 264
-- 266
-- 267
-- 269
-- 288

.tables

.schema phone_calls
-- The thief made a phone call about a plane flight

SELECT duration FROM phone_calls ORDER BY duration DESC;
-- See what formatting is
-- Assuming it's seconds

SELECT id FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 INTERSECT SELECT id FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 INTERSECT SELECT id FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw";
-- Suspects:
-- ID:
-- 246
-- 264
-- 266
-- 267
-- 269

SELECT id FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60 INTERSECT SELECT id FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 INTERSECT SELECT id FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw";
-- Nothing. Not cool.

.tables

.schema flights
-- Maybe there's something here

SELECT id FROM flights;
-- See if this data has anything to do with the other id. It doesn't.

.schema people
-- I'm kind of floundering at this point

SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND ID IN (SELECT id FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 INTERSECT SELECT id FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 INTERSECT SELECT id FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw") ORDER BY id, hour, minute;
-- Very cool, but it looks like the list of license plates is the same length as my list of suspects
-- License Plates:
-- P14PE2Q
-- G412CB7
-- 322W7JE
-- 0NTHK55
-- NRYN856

SELECT id FROM people WHERE SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND ID IN SELECT id FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 INTERSECT SELECT id FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 INTERSECT SELECT id FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw" ORDER BY id, hour, minute INTERSECT SELECT id FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 INTERSECT SELECT id FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 INTERSECT SELECT id FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw";
-- Lol. It's almost comical I expected this to work. Best to try for simpler connections to narrow my suspects.

.tables
-- Checked my notes above and saw the crime happened at 10:15 am (crime scene report) - that's super helpful

.schema courthouse_security_logs

SELECT license_plate, hour, minute FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 ORDER BY hour, minute;
-- Find ids that exited the parking lot between 10 and 11 am 

SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25 AND id IN (SELECT id FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 INTERSECT SELECT id FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 INTERSECT SELECT id FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw") ORDER BY id, hour, minute;
-- Search for those exiting the courthouse parking lot at a suspicious time
-- License Plates:
-- G412CB7
-- 322W7JE
-- 0NTHK55

SELECT id FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25 AND id IN (SELECT id FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 INTERSECT SELECT id FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 INTERSECT SELECT id FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw") ORDER BY id, hour, minute;
-- Turn above query into ids
-- ID:
-- 264
-- 266
-- 267

SELECT id FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration > 60 INTERSECT SELECT id FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 45 AND id IN (SELECT id FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 INTERSECT SELECT id FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 INTERSECT SELECT id FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw");
-- Check phone call length against suspects
-- No change

SELECT name, id, license_plate, passport_number FROM people WHERE license_plate = "G412CB7" OR license_plate = "322W7JE" OR license_plate = "0NTHK55";
-- Info on suspects
-- name | id | license_plate | passport_number
-- Roger | 398010 | G412CB7 | 1695452385
-- Russell | 514354 | 322W7JE | 3592750733
-- Evelyn | 560886 | 0NTHK55 | 8294398571

SELECT passport_number FROM flights JOIN passengers ON flights.id = passengers.flight_id WHERE year = 2020 AND month = 7 AND day = 29 INTERSECT SELECT passport_number FROM people WHERE license_plate = "G412CB7" OR license_plate = "322W7JE" OR license_plate = "0NTHK55";
-- Same three again
-- 1695452385
-- 3592750733
-- 8294398571

SELECT passport_number, hour, minute, origin_airport_id, destination_airport_id FROM passengers JOIN flights ON passengers.flight_id = flights.id WHERE year = 2020 AND month = 7 AND day = 29 AND passport_number = 1695452385 OR passport_number = 3592750733 OR passport_number = 8294398571 ORDER BY hour, minute;
-- Try to narrow down the culprity by seeing who left on the earliest flight out of town the next day
-- passport_number | hour | minute | origin_airport_id | destination_airport_id
-- 1695452385 | 8 | 20 | 8 | 4
-- 8294398571 | 8 | 20 | 8 | 4
-- 3592750733 | 10 | 19 | 8 | 5
-- 3592750733 | 16 | 0 | 8 | 6
-- 3592750733 | 16 | 27 | 7 | 8

SELECT id, full_name, city FROM airports WHERE id >= 4 AND id <= 8;
-- Get names of arriving and departing airports
-- id | full_name | city
-- 4 | Heathrow Airport | London
-- 5 | Dallas/Fort Worth International Airport | Dallas
-- 6 | Logan International Airport | Boston
-- 7 | Dubai International Airport | Dubai
-- 8 | Fiftyville Regional Airport | Fiftyville

-- Earliest flight out of Fiftyville the morning after the crime was 8:20, so the culprits narrow to two:
-- 1695452385 | 8 | 20 | 8 | 4 
-- Roger
-- 8294398571 | 8 | 20 | 8 | 4
-- Evelyn

SELECT id, name, phone_number FROM people WHERE passport_number = 1695452385 OR passport_number = 8294398571;
-- Get ids for Roger and Evelyn, might be useful for financial transactions
-- id | name
-- 398010 | Roger | (130) 555-0289
-- 560886 | Evelyn | (499) 555-9472

SELECT caller, receiver FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60 AND caller = "(130) 555-0289" or caller = "(499) 555-9472";
-- The thief initiated the call
-- (499) 555-9472 | (770) 555-1861
-- (130) 555-0289 | (996) 555-8899
-- (499) 555-9472 | (892) 555-8872
-- (499) 555-9472 | (717) 555-1342
-- (499) 555-9472 | (996) 555-8899
-- (499) 555-9472 | (020) 555-6715

SELECT hour, minute, activity FROM courthouse_security_logs WHERE id = 162;
-- Eugene 162 saw thief before he came to courthouse. Timing is unhelpful.
-- hour | minute | activity
-- 10 | 20 | entrance

SELECT * FROM people WHERE id = 398010 OR id = 560886;
-- id | name | phone_number | passport_number | license_plate
-- 398010 | Roger | (130) 555-0289 | 1695452385 | G412CB7
-- 560886 | Evelyn | (499) 555-9472 | 8294398571 | 0NTHK55

SELECT * FROm bank_accounts WHERE person_id = 398010 or person_id = 560886;

-- I'm so sorry to do this to whoever is grading this (most of this has been pointless), but I feel mixed up right now and am going to more or less restart after the line below:
________________________________________________________________________________

-- Assembled Information:
-- Given: July 28, 2020 (7/28/20) on Chamberlin Street
-- "Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse. Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse."
-- Useful Transcripts:
-- Ruth | 161 | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
-- Eugene | 162 | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
-- Raymond | 163 | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

SELECT id FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street";
-- Current list of suspects (those who made atm transactions at this location on that day)
-- id
-- 246
-- 264
-- 266
-- 267
-- 269
-- 275
-- 288
-- 313
-- 336

SELECT id FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25 INTERSECT SELECT id FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street";
-- id
-- 264
-- 266
-- 267

SELECT license_plate FROM courthouse_security_logs WHERE id IN (SELECT id FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25 INTERSECT SELECT id FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street");
-- license_plate
-- G412CB7
-- 322W7JE
-- 0NTHK55

SELECT * FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE id IN (SELECT id FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25 INTERSECT SELECT id FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street"));
-- id | name | phone_number | passport_number | license_plate
-- 398010 | Roger | (130) 555-0289 | 1695452385 | G412CB7
-- 514354 | Russell | (770) 555-1861 | 3592750733 | 322W7JE
-- 560886 | Evelyn | (499) 555-9472 | 8294398571 | 0NTHK55

SELECT caller, receiver, duration FROM phone_calls WHERE caller = "(130) 555-0289" OR caller = "(770) 555-1861" OR caller = "(499) 555-9472" ORDER BY duration;
-- All three culprits have calls less than a minute on that specific day

SELECT passport_number, seat, hour, minute, origin_airport_id, destination_airport_id FROM flights JOIN passengers ON flights.id = passengers.flight_id WHERE year = 2020 AND month = 7 AND day = 29 ORDER BY hour, minute;

SELECT passport_number, seat, hour, minute, origin_airport_id, destination_airport_id FROM flights JOIN passengers ON flights.id = passengers.flight_id WHERE year = 2020 AND month = 7 AND day = 29 AND passport_number = 1695452385 OR passport_number = 3592750733 OR passport_number = 8294398571 ORDER BY hour, minute;
-- passport_number | seat | hour | minute | origin_airport_id | destination_airport_id
-- 1695452385 | 3B | 8 | 20 | 8 | 4
-- 8294398571 | 6C | 8 | 20 | 8 | 4
-- 3592750733 | 6C | 10 | 19 | 8 | 5
-- 3592750733 | 4C | 16 | 0 | 8 | 6
-- 3592750733 | 2C | 16 | 27 | 7 | 8a

SELECT * FROM airports ORDER BY id;
-- 4 | LHR | Heathrow Airport | London
-- 5 | DFS | Dallas/Fort Worth International Airport | Dallas
-- 6 | BOS | Logan International Airport | Boston
-- 7 | DXB | Dubai International Airport | Dubai
-- 8 | CSF | Fiftyville Regional Airport | Fiftyville

-- The thief took the first flight out of Fiftyville on the morning of the 27th, so the thief either has passport number 1695452385 or 8294398571
-- Russel didn't take the earliest flight out, so he's removed from the suspect list

-- Suspect Profiles:
-- id | name | phone_number | passport_number | license_plate
-- 398010 | Roger | (130) 555-0289 | 1695452385 | G412CB7 - 264
-- 560886 | Evelyn | (499) 555-9472 | 8294398571 | 0NTHK55 - 267

SELECT * FROM atm_transactions WHERE id = 264 OR id = 267;
-- id | account_number | year | month | day | atm_location | transaction_type | amount
-- Roger: 264 | 28296815 | 2020 | 7 | 28 | Fifer Street | withdraw | 20
-- Evelyn: 267 | 49610011 | 2020 | 7 | 28 | Fifer Street | withdraw | 50

SELECT * FROM bank_accounts WHERE account_number = 28296815 OR account_number = 49610011;
-- account_number | person_id | creation_year
-- Evelyn: 49610011 | 686048 | 2010
-- Roger: 28296815 | 395717 | 2014

SELECT * FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND caller = "(130) 555-0289" OR caller = "(499) 555-9472";
-- id | caller | receiver | year | month | day | duration
-- 221 | (130) 555-0289 | (996) 555-8899 | 2020 | 7 | 28 | 51
-- 224 | (499) 555-9472 | (892) 555-8872 | 2020 | 7 | 28 | 36
-- 251 | (499) 555-9472 | (717) 555-1342 | 2020 | 7 | 28 | 50

SELECT * FROM bank_accounts JOIN people ON bank_accounts.person_id IN (SELECT people.id WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND caller = "(130) 555-0289" OR caller = "(499) 555-9472"));
-- Compare phone numbers and bank accounts to see if the people that Roger and Evelyn called had active accounts and to see who those people are
-- account_number | person_id | creation_year | id | name | phone_number | passport_number | license_plate
-- 26013199 | 514354 | 2012 | 514354 | Russell | (770) 555-1861 | 3592750733 | 322W7JE
-- 24907878 | 404704 | 2012 | 404704 | Catherine | (020) 555-6715 |  | NA31S0K
-- 69638157 | 567218 | 2012 | 567218 | Jack | (996) 555-8899 | 9029462229 | 52R0Y8U
-- 72161631 | 251693 | 2015 | 251693 | Larry | (892) 555-8872 | 2312901747 | O268ZZ0

-- Roger called Jack
-- Evelyn called Larry

SELECT * FROM flights JOIN passengers ON flights.id = passengers.flight_id WHERE year = 2020 AND month = 7 AND day = 29 AND passport_number = 9029462229 OR passport_number = 2312901747;
-- id | origin_airport_id | destination_airport_id | year | month | day | hour | minute | flight_id | passport_number | seat
-- 17 | 8 | 4 | 2020 | 7 | 28 | 20 | 16 | 17 | 2312901747 | 2B
-- 37 | 8 | 3 | 2020 | 7 | 27 | 7 | 37 | 37 | 2312901747 | 5B
-- 53 | 8 | 9 | 2020 | 7 | 29 | 15 | 20 | 53 | 2312901747 | 4D
-- This looks unfruitful

___________________________________________________________________
-- At this point, I went to a tutorial, and the instructor suggested I restart while paying close attention to IDs across tables. If some information seems to be assumed, it's because I've already done many of these operations multiple times.
-- ** Two stars will indicate design comments

SELECT license_plate FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location = "Fifer Street"));
-- Get a list of suspects by ATM information, show in license_plate form for cross compatability

SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25 AND activity = "exit" AND license_plate IN (SELECT license_plate FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND transaction_type = "withdraw")));
-- Filter the list of license plates above by conditions given regarding courthouse security from one of the witnesses
-- license_plate
-- 94KL13X
-- 4328GD8
-- L93JTIZ
-- 322W7JE

SELECT * FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25 AND activity = "exit" AND license_plate IN (SELECT license_plate FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND transaction_type = "withdraw"))));
-- This shows my suspects with the given license plates
-- id | name | phone_number | passport_number | license_plate
-- 396669 | Elizabeth | (829) 555-5269 | 7049073643 | L93JTIZ
-- 467400 | Danielle | (389) 555-5198 | 8496433585 | 4328GD8
-- 514354 | Russell | (770) 555-1861 | 3592750733 | 322W7JE
-- 686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X

SELECT passport_number FROM passengers JOIN flights ON flights.id = passengers.flight_id WHERE year = 2020 AND month = 7 AND day = 29 AND origin_airport_id = 8 INTERSECT SELECT passport_number FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25 AND activity = "exit" AND license_plate IN (SELECT license_plate FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND transaction_type = "withdraw"))));
-- This finds the passport numbers of my suspects who meet the criteria for going on a flight that day
-- passport_number
-- 3592750733
-- 5773159633
-- 8496433585

-- Copy and pasted from above from my suspects who continue to match the criteria
-- id | name | phone_number | passport_number | license_plate
-- 467400 | Danielle | (389) 555-5198 | 8496433585 | 4328GD8
-- 514354 | Russell | (770) 555-1861 | 3592750733 | 322W7JE
-- 686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X

SELECT * FROM flights JOIN passengers ON flights.id = passengers.flight_id WHERE year = 2020 AND month = 7 AND day = 29 AND origin_airport_id = 8 AND passport_number = 8496433585 OR passport_number = 3592750733 OR passport_number = 5773159633 ORDER BY hour, minute;
-- ** It was an intentional decision to hard code the three passport numbers. I could have nested my previous queries further, but the length of the query itself was becoming more time-intensive to manage than just copy and pasting three passport numbers.
-- id | origin_airport_id | destination_airport_id | year | month | day | hour | minute | flight_id | passport_number | seat
-- 36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20 | 36 | 5773159633 | 4A
-- 36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20 | 36 | 8496433585 | 7B

-- Ernest
-- Danielle

SELECT * FROM people WHERE name = "Danielle" OR name = "Ernest";
-- ** Once again, hard coded for ease and speed
-- id | name | phone_number | passport_number | license_plate
-- 467400 | Danielle | (389) 555-5198 | 8496433585 | 4328GD8
-- 686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X

SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60 AND caller IN (SELECT phone_number FROM people WHERE name = "Danielle" OR name = "Ernest");
-- ** With two easily typed names, it's way more efficient to continue hard coding 
-- Filter my two suspects looking for whoever made an outgoing call that meets the length requirement
-- caller
-- (367) 555-5533
-- All the information suggests Ernest did it

SELECT * FROM people WHERE phone_number = (SELECT receiver FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60 AND caller IN (SELECT phone_number FROM people WHERE name = "Danielle" OR name = "Ernest"));
-- ** Hard coding continues because I'm copy and pasting for nested queries for this point
-- Find the accomplice by seeing who Ernest called
-- id | name | phone_number | passport_number | license_plate
-- 864400 | Berthold | (375) 555-8161 |  | 4V16VO0
-- Accomplice is Berthold

SELECT * FROM flights JOIN passengers WHERE year = 2020 AND month = 7 AND day = 29 AND origin_airport_id = 8 AND passport_number = (SELECT passport_number FROM people WHERE name = "Ernest") ORDER BY hour, minute;
-- Search for the earliest outgoing flight the day after that Ernest was on. This flight matches
-- id | origin_airport_id | destination_airport_id | year | month | day | hour | minute | flight_id | passport_number | seat
-- 36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20 | 36 | 5773159633 | 4A

SELECT * FROM airports WHERE id = 4;
-- ** This is hard coded because it's just so much easier
-- Find the destination airport
-- id | abbreviation | full_name | city
-- 4 | LHR | Heathrow Airport | London