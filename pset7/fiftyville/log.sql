-- Find out who is the thief
SELECT name
FROM bakery_security_logs
JOIN people ON bakery_security_logs.license_plate = people.license_plate
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
JOIN phone_calls ON people.phone_number = phone_calls.caller
JOIN passengers ON passengers.passport_number = people.passport_number
JOIN flights ON passengers.flight_id = flights.id
WHERE (bakery_security_logs.year = 2021) AND (bakery_security_logs.month = 7) AND (bakery_security_logs.day = 28) AND (bakery_security_logs.hour = 10) AND (bakery_security_logs.minute > 15) AND (bakery_security_logs.minute < 25) AND (activity = "exit")
AND (atm_location = "Leggett Street") AND (transaction_type = "withdraw")
AND (duration < 60)
ORDER BY flights.hour, flights.minute LIMIT 1;

-- Find out the city thief escaped to
SELECT city
FROM flights
JOIN airports ON flights.destination_airport_id = airports.id
WHERE (year = 2021) AND (month = 7) AND (day = 29) ORDER BY hour, minute LIMIT 1;

-- Find out who is the accomplice
SELECT name
FROM phone_calls
JOIN people ON phone_calls.receiver = people.phone_number
WHERE caller = (SELECT phone_number FROM people WHERE (name = (SELECT name
FROM bakery_security_logs
JOIN people ON bakery_security_logs.license_plate = people.license_plate
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
JOIN phone_calls ON people.phone_number = phone_calls.caller
JOIN passengers ON passengers.passport_number = people.passport_number
JOIN flights ON passengers.flight_id = flights.id
WHERE (bakery_security_logs.year = 2021) AND (bakery_security_logs.month = 7) AND (bakery_security_logs.day = 28) AND (bakery_security_logs.hour = 10) AND (bakery_security_logs.minute > 15) AND (bakery_security_logs.minute < 25) AND (activity = "exit")
AND (atm_location = "Leggett Street") AND (transaction_type = "withdraw")
AND (duration < 60)
ORDER BY flights.hour, flights.minute LIMIT 1)))
AND  (year = 2021) AND (month = 7) AND (day = 28) AND (duration < 60);

-- Check the description of our crime.It took place at 10.15am and we found out that all 3 witnesses mentioned bakery.
SELECT * FROM crime_scene_reports WHERE (year = 2021) AND (month = 7) AND (day = 28) AND (street = "Humphrey Street");
-- Check exactly what the witnesses said about the crime.
SELECT * FROM interviews WHERE (year = 2021) AND (month = 7) AND (day = 28) AND transcript LIKE "%bakery%";
-- The crime was done at 10.15am. Within 10 minutes the thief left the parking lot,
-- We found out license_plates of all people who left the scene within 10 minutes after the crime.
SELECT * FROM bakery_security_logs WHERE (year = 2021) AND (month = 7) AND (day = 28) AND (hour = 10) AND (minute > 15) AND (minute < 25) AND (activity = "exit");
-- We check all withdraw transactions that happend this day at mentioned ATM.
SELECT * FROM atm_transactions WHERE (year = 2021) AND (month = 7) AND (day = 28) AND (atm_location = "Leggett Street") AND (transaction_type = "withdraw");
-- We check phone numbers of all callers and recievers of the phone calls on our day and with duration < 60 seconds
SELECT * FROM phone_calls WHERE (year = 2021) AND (month = 7) AND (day = 28) AND (duration < 60);
-- We figured out the earliest flight tomorrow
SELECT * FROM flights WHERE (year = 2021) AND (month = 7) AND (day = 29) ORDER BY hour, minute LIMIT 1;
-- We check all passangers from our flight
SELECT * FROM passengers WHERE flight_id = (SELECT id FROM flights WHERE (year = 2021) AND (month = 7) AND (day = 29) ORDER BY hour, minute LIMIT 1);

