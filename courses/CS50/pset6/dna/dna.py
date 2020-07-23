import csv
from sys import argv, exit

#check on command line arguments
if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)

#print all input arguments
#for cmd in range(1, len(argv)):
#    print(argv[cmd])


#####################################################
# function get_occurrences takes string and substring
# calculates max amount of consecutive occurrences
# of substring in string
#################################################
def get_occurrences(substr, str):
    count = 0
    max_count = 0
    str_len = len(str)
    substr_len = len(substr)

    #check on first occurrence
    if str.find(substr) == -1:
        return 0
    else:
        tmp = str[str.find(substr) + len(substr):]
        count += 1

    #print(f"str: {str} \n tmp: {tmp}")
    while len(tmp) >= len(substr):
        if tmp[:len(substr)] == substr:
            tmp = tmp[len(substr):]
            count += 1
        else:
            if count > max_count:
                max_count = count
            count = 0
            if tmp.find(substr) != -1:
                tmp = tmp[tmp.find(substr) + len(substr):]
                count += 1
            else:
                return max_count
    return max_count

#input sequence file
seqFile = open(argv[2], 'r')
sequence = seqFile.read()
#print("Seq: ", sequence)

#open db input file
with open(argv[1], mode='r') as db_data:
    db_reader = csv.DictReader(db_data)

    #read through all csv lines and insert into dict db_row
    for db_row in db_reader:
        #print(db_row)
        #print(len(db_row.keys()) - 1)

        #setting up match count value
        match_count = 0

        #go through each STR element in dict (except for name)
        for dna_name, dna_times in db_row.items():
            if dna_name == "name": #excluding name
                continue
            ##print(dna_name, dna_times)
            #dna_seq = dna_name * int(dna_times) #compute each person's STR sequence
            ##print(f"Name {db_row['name']}: dna_seq {dna_seq}")
            ##if (re.search(dna_seq, sequence) == dna_seq):
            #if dna_seq in sequence: #check if person's STR in input txt file
            #    match_count += 1

            if get_occurrences(dna_name, sequence) == int(dna_times):
                match_count += 1



        #print(f"match_count = {match_count}")
        if match_count == len(db_row.keys()) - 1: #check if all person's STRs exist in inout txt file
            print(db_row["name"])
            exit(0)
    print("No match")
