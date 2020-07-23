from cs50 import get_float

while True:
    change = get_float("Change owed: ")
    if change > 0:
        break

quarter = 25
dime = 10
nickel = 5
penny = 1

count = 0

change = int(change * 100)

while change != 0:
    if change >= quarter:
        change -= quarter
        count += 1
    elif change >= dime and change < quarter:
        change -= dime
        count += 1
    elif change >= nickel and change < dime:
        change -= nickel
        count += 1
    elif change >= penny and change < nickel:
        change -= penny
        count += 1

print(count)