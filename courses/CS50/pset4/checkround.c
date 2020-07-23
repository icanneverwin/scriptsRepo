#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    int red, green, blue;
    float sepiaRed, sepiaGreen, sepiaBlue;
    //float avg;
    red = get_int("red value: ");
    green = get_int("green value: ");
    blue = get_int("blue value: ");
//
    //avg = ((float) red + (float) green + (float) blue) / 3;
//
    //avg = round(avg);
    //printf("red = %i, green = %i, blue = %i, avg = %f, rounded avg = %i\n", red, green, blue, avg, (int) avg);


    sepiaRed = round(0.393 * (float) red + 0.769 * green + 0.189 * (float) blue);
    sepiaGreen = round(0.349 * (float) red + 0.686 * (float) green + 0.168 * (float) blue);
    sepiaBlue = round(0.272 * (float) red + 0.534 * (float) green + 0.131 * (float) blue);


    printf("sepiaRed = %f, sepiaGreen = %f, sepiaBlue = %f\n", sepiaRed, sepiaGreen, sepiaBlue);

}