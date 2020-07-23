#include <stdio.h>
#include <cs50.h>

int extract_digit(long num);

int main(void) {
    long card, temp_num;

    int card_no, temp_even, temp_odd, temp_digit;
    int i = 0;

    int first_digit, second_digit;

    do {
        card = get_long("Number: ");
    }
    while (card < 0);

    temp_num = card;
    temp_even = 0;
    temp_odd = 0;

    while (temp_num > 0) {
        //check on first and second digits
        if (temp_num > 9 && temp_num < 100) {
            second_digit = extract_digit(temp_num);
        }
        else if (temp_num > 0 && temp_num < 10) {
            first_digit = extract_digit(temp_num);
        }

        //extract each digit from provided number and perform calculations for even and odd numbers
        if (i % 2 == 1) {
            // get digit and multiply by 2
            temp_digit = extract_digit(temp_num);
            temp_digit = temp_digit * 2;

            if (temp_digit > 9) {
                temp_odd = temp_odd + temp_digit % 10;
                temp_odd = temp_odd + temp_digit / 10;
            }
            else {
                temp_odd = temp_odd + temp_digit;
            }
        }
        else {
            temp_digit = extract_digit(temp_num);
            temp_even = temp_even + extract_digit(temp_num);
        }

        temp_num = temp_num / 10;
        i++;
    }
    //once end is reached - lets add sum_odd and sum_even
    if ((temp_odd + temp_even) % 10 == 0) {
        if (i == 15 && first_digit == 3 && (second_digit == 4 || second_digit == 7)) {
            printf("AMEX\n");
        }
        else if (i == 16 && first_digit == 5 && (second_digit == 1 || second_digit == 2 || second_digit == 3 ||second_digit == 4 || second_digit == 5)) {
            printf("MASTERCARD\n");
        }
        else if ((i == 13 || i == 16) && first_digit == 4) {
            printf("VISA\n");
        }
        else {
            printf("INVALID\n");
        }
    }
    else {
        printf("INVALID\n");
    }

}


int extract_digit(long num) {
    long temp;
    int digit;

    temp = num;
    digit = temp % 10;

    return digit;
}