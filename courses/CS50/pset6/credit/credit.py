from cs50 import get_int

while True:
    card = get_int("Number: ")
    if card > 0:
        break

def get_digit(num):
    return num % 10

temp_num = card
temp_even = 0
temp_odd = 0
i = 0

while temp_num > 0:
    if temp_num > 9 and temp_num < 100:
        second_digit = get_digit(temp_num)
    elif temp_num > 0 and temp_num < 10:
        first_digit = get_digit(temp_num)

    if i % 2 == 1:
        temp_digit = get_digit(temp_num)
        temp_digit *= 2

        if temp_digit > 9:
            temp_odd = temp_odd + temp_digit % 10
            temp_odd = int(temp_odd + temp_digit / 10)
        else:
            temp_odd = temp_odd + temp_digit
    else:
        temp_digit = get_digit(temp_num)
        temp_even = temp_even + get_digit(temp_num)

    temp_num = int(temp_num / 10)
    i += 1

if (temp_odd + temp_even) % 10 == 0:
    if (i == 15 and first_digit == 3) and (second_digit == 4 or second_digit == 7):
        print("AMEX")
    elif (i == 16 and first_digit == 5) and second_digit in range(1, 6):
        print("MASTERCARD")
    elif (i == 13 or i == 16) and first_digit == 4:
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")
