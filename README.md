# covid-hashtable-db
A C++ project in my Data Structures class that implements a hash table
to store COVID case/death data by country, using a CSV file.

## What it does
- Hashes country names into a 17 bucket table using separate chaining
- Loads WHO COVID CSV file into the table
- Handles duplicate entries by comparing dates; only updates the record if new entry is more recent
- Supports users adding/removing/displaying information from table

This was built for class and is rough around the edges. Some future improvements:
- Build a more robust system for parsing (currently crashes on invalid rows)
- Add unit tests
- Swap in a more updated dataset

## To build and run
g++ main.cpp classes.cpp -o coviddb

./coviddb
