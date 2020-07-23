#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void) {

    float change;
    int quarter = 25;
    int dime = 10;
    int nickel = 5;
    int penny = 1;

    int coin_count = 0;

    do {
        change = get_float("Change owed: ");
    }
    while (change <= 0);

    change = round(change * 100);


    while (change != 0) {
        if (change >= 25) {
            change = change - quarter;
            coin_count++;
        }
        else if (change < 25 && change >= 10) {
            change = change - dime;
            coin_count++;
        }
        else if (change < 10 && change >= 5) {
            change = change - nickel;
            coin_count++;
        }
        else if (change < 5 && change >= 1) {
            change = change - penny;
            coin_count++;
        }
        //printf("%f\n", change);
    }
   printf("%i\n", coin_count);
}