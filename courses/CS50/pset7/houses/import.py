import cs50, csv
from sys import argv, exit

#check on command line arguments
if len(argv) != 2:
    print("Usage: python import.py data.csv")
    exit(1)


#open connection to students.db
db = cs50.SQL("sqlite:///students.db")


with open(argv[1], 'r') as inputFile:

    reader = csv.DictReader(inputFile)
    id = 1

    for row in reader:
        #print(row)
        #print(row["name"], row["house"], row["birth"])
        names = row["name"].split()
        #print(len(row["name"].split()))

        # split name into first/second/last names
        if len(names) == 3:
            firstName = names[0]
            middleName = names[1]
            lastName = names[2]
        else:
            firstName = names[0]
            middleName = None
            lastName = names[1]

        db.execute("insert into students (id, first, middle, last, house, birth) values (?, ?, ?, ?, ?, ?)", id, firstName, middleName, lastName, row["house"], int(row["birth"]))
        id += 1

        #print(f"firstName: {firstName}  middleName: {middleName} lastName: {lastName}")

