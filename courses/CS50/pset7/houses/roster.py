import cs50, csv
from sys import argv, exit

#check on command line arguments
if len(argv) != 2:
    print("Usage: python import.py housename")
    exit(1)


#open connection to students.db
db = cs50.SQL("sqlite:///students.db")

rows = db.execute("select first, middle, last, birth from students where house = ? order by last, first", argv[1])

for row in rows:
    #print(f"{row[0]} {row[1]} {row[2]}, born {row[3]}")
    #print(row)
    if row["middle"] == None:
        print(f"{row['first']} {row['last']}, born {row['birth']}")
    else:
        print(f"{row['first']} {row['middle']} {row['last']}, born {row['birth']}")