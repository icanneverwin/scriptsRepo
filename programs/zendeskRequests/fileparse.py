import csv
import os



def filereader(filename: str, newfile: str):
    #rowDict = {}
    with open(filename, newline='') as csvfile:
        csvreader = csv.reader(csvfile, delimiter=',')
        next(csvreader, None)
        for row in csvreader:
            append_write = ifFileExists(newfile)
            with open(newfile, append_write, newline='') as csvfile:
                writer = csv.writer(csvfile)
                if append_write == 'w':
                    csvHeader = ['email', 'groupname']
                    writer.writerow(csvHeader)
                for i in range(len(row)):
                    if i == 0:
                        continue
                    else:
                        writer.writerow([row[0], row[i]])

def writeInFile(userGroups: dict, filename: str):
    with open(filename, 'w') as csvfile:
        writer = csv.writer(csvfile)
        csvHeader = ['email', 'groupname']
        writer.writerow(csvHeader)
        for key, value in userGroups.items():
            for i in range(len(value)):
                writer.writerow([key, value[i]])



def ifFileExists(filename: str) -> str:
    if os.path.exists(filename):
        append_write = 'a'
    else:
        append_write = 'w'
    return append_write

if __name__ == "__main__":
    file = 'G:/My Drive/Tasks/AMS_Strategy/usergroup_tmp.csv'

    #userGroups = filereader(file)
    #print(userGroups)

    newCsvfile = 'newUserGroups.csv'
    #writeInFile(userGroups, newCsvfile)

    #testStr = "['86_Windows_Server_CE', '86_Windows_Server_DotCom_UK', '86_Windows_Server_HSC', '86_Windows_Server_ISS_UK', '86_Windows_Server_MY', '86_Windows_Server_TH', '86_Windows_Server_UK_PLC']"
    #print(re.search("'.*'", testStr))

    filereader(file, newCsvfile)
