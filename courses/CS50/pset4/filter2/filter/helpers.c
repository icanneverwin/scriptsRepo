#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float avg_value;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // calculate average value for G/R/B
            avg_value = round(((float) image[i][j].rgbtBlue + (float) image[i][j].rgbtGreen + (float) image[i][j].rgbtRed) / 3);
            image[i][j].rgbtBlue = (int) avg_value;
            image[i][j].rgbtGreen = (int) avg_value;
            image[i][j].rgbtRed = (int) avg_value;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int temp_red, temp_green, temp_blue;

    for (int i = 0; i < height; i++)
    {
        int k = width - 1;
        int j = 0;

        while (j < k)
        {
            temp_red = image[i][j].rgbtRed;
            temp_green = image[i][j].rgbtGreen;
            temp_blue = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = image[i][k].rgbtRed;
            image[i][j].rgbtGreen = image[i][k].rgbtGreen;
            image[i][j].rgbtBlue = image[i][k].rgbtBlue;

            image[i][k].rgbtRed = temp_red;
            image[i][k].rgbtGreen = temp_green;
            image[i][k].rgbtBlue = temp_blue;

            j++;
            k--;

        }
    }

}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    typedef struct
    {
        int rgbtRed;
        int rgbtGreen;
        int rgbtBlue;
    }
    temp_array;

    temp_array temp_arr[height][width];
    float avg_red, avg_green, avg_blue;

    // copying into temp array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp_arr[i][j].rgbtRed = image[i][j].rgbtRed;
            temp_arr[i][j].rgbtGreen = image[i][j].rgbtGreen;
            temp_arr[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0) // top line
            {
                if (j == 0)
                {
                    image[i][j].rgbtRed     = (int) round(((float) temp_arr[i][j].rgbtRed   + (float) temp_arr[i][j + 1].rgbtRed    + (float) temp_arr[i + 1][j].rgbtRed    + (float) temp_arr[i + 1][j + 1].rgbtRed)   / 4);
                    image[i][j].rgbtGreen   = (int) round(((float) temp_arr[i][j].rgbtGreen + (float) temp_arr[i][j + 1].rgbtGreen  + (float) temp_arr[i + 1][j].rgbtGreen  + (float) temp_arr[i + 1][j + 1].rgbtGreen) / 4);
                    image[i][j].rgbtBlue    = (int) round(((float) temp_arr[i][j].rgbtBlue  + (float) temp_arr[i][j + 1].rgbtBlue   + (float) temp_arr[i + 1][j].rgbtBlue   + (float) temp_arr[i + 1][j + 1].rgbtBlue)  / 4);
                }
                else if (j == width - 1)
                {
                    image[i][j].rgbtRed     = (int) round(((float) temp_arr[i][j].rgbtRed   + (float) temp_arr[i][j - 1].rgbtRed    + (float) temp_arr[i + 1][j].rgbtRed    + (float) temp_arr[i + 1][j - 1].rgbtRed)   / 4);
                    image[i][j].rgbtGreen   = (int) round(((float) temp_arr[i][j].rgbtGreen + (float) temp_arr[i][j - 1].rgbtGreen  + (float) temp_arr[i + 1][j].rgbtGreen  + (float) temp_arr[i + 1][j - 1].rgbtGreen) / 4);
                    image[i][j].rgbtBlue    = (int) round(((float) temp_arr[i][j].rgbtBlue  + (float) temp_arr[i][j - 1].rgbtBlue   + (float) temp_arr[i + 1][j].rgbtBlue   + (float) temp_arr[i + 1][j - 1].rgbtBlue)  / 4);
                }
                else
                {
                    image[i][j].rgbtRed     = (int) round(( (float) temp_arr[i][j].rgbtRed              + (float) temp_arr[i][j - 1].rgbtRed        + (float) temp_arr[i][j + 1].rgbtRed        +
                                                            (float) temp_arr[i + 1][j - 1].rgbtRed      + (float) temp_arr[i + 1][j].rgbtRed        + (float) temp_arr[i + 1][j + 1].rgbtRed)       / 6);
                    image[i][j].rgbtGreen   = (int) round(( (float) temp_arr[i][j].rgbtGreen            + (float) temp_arr[i][j - 1].rgbtGreen      + (float) temp_arr[i][j + 1].rgbtGreen      +
                                                            (float) temp_arr[i + 1][j - 1].rgbtGreen    + (float) temp_arr[i + 1][j].rgbtGreen      + (float) temp_arr[i + 1][j + 1].rgbtGreen)     / 6);
                    image[i][j].rgbtBlue    = (int) round(( (float) temp_arr[i][j].rgbtBlue             + (float) temp_arr[i][j - 1].rgbtBlue       + (float) temp_arr[i][j + 1].rgbtBlue       +
                                                            (float) temp_arr[i + 1][j - 1].rgbtBlue     + (float) temp_arr[i + 1][j].rgbtBlue       + (float) temp_arr[i + 1][j + 1].rgbtBlue)      / 6);
                }
            }

            else if (i == height - 1) // bottom line
            {
                if (j == 0)
                {
                    image[i][j].rgbtRed     = (int) round(((float) temp_arr[i][j].rgbtRed   + (float) temp_arr[i][j + 1].rgbtRed    + (float) temp_arr[i - 1][j].rgbtRed    + (float) temp_arr[i - 1][j + 1].rgbtRed)   / 4);
                    image[i][j].rgbtGreen   = (int) round(((float) temp_arr[i][j].rgbtGreen + (float) temp_arr[i][j + 1].rgbtGreen  + (float) temp_arr[i - 1][j].rgbtGreen  + (float) temp_arr[i - 1][j + 1].rgbtGreen) / 4);
                    image[i][j].rgbtBlue    = (int) round(((float) temp_arr[i][j].rgbtBlue  + (float) temp_arr[i][j + 1].rgbtBlue   + (float) temp_arr[i - 1][j].rgbtBlue   + (float) temp_arr[i - 1][j + 1].rgbtBlue)  / 4);
                }
                else if (j == width - 1)
                {
                    image[i][j].rgbtRed     = (int) round(((float) temp_arr[i][j].rgbtRed   + (float) temp_arr[i][j - 1].rgbtRed    + (float) temp_arr[i - 1][j].rgbtRed    + (float) temp_arr[i - 1][j - 1].rgbtRed)   / 4);
                    image[i][j].rgbtGreen   = (int) round(((float) temp_arr[i][j].rgbtGreen + (float) temp_arr[i][j - 1].rgbtGreen  + (float) temp_arr[i - 1][j].rgbtGreen  + (float) temp_arr[i - 1][j - 1].rgbtGreen) / 4);
                    image[i][j].rgbtBlue    = (int) round(((float) temp_arr[i][j].rgbtBlue  + (float) temp_arr[i][j - 1].rgbtBlue   + (float) temp_arr[i - 1][j].rgbtBlue   + (float) temp_arr[i - 1][j - 1].rgbtBlue)  / 4);
                }
                else
                {
                    image[i][j].rgbtRed     = (int) round(( (float) temp_arr[i][j].rgbtRed              + (float) temp_arr[i][j - 1].rgbtRed    + (float) temp_arr[i][j + 1].rgbtRed        +
                                                            (float) temp_arr[i - 1][j - 1].rgbtRed      + (float) temp_arr[i - 1][j].rgbtRed    + (float) temp_arr[i - 1][j + 1].rgbtRed)       / 6);
                    image[i][j].rgbtGreen   = (int) round(( (float) temp_arr[i][j].rgbtGreen            + (float) temp_arr[i][j - 1].rgbtGreen  + (float) temp_arr[i][j + 1].rgbtGreen      +
                                                            (float) temp_arr[i - 1][j - 1].rgbtGreen    + (float) temp_arr[i - 1][j].rgbtGreen  + (float) temp_arr[i - 1][j + 1].rgbtGreen)   / 6);
                    image[i][j].rgbtBlue    = (int) round(( (float) temp_arr[i][j].rgbtBlue             + (float) temp_arr[i][j - 1].rgbtBlue   + (float) temp_arr[i][j + 1].rgbtBlue       +
                                                            (float) temp_arr[i - 1][j - 1].rgbtBlue     + (float) temp_arr[i - 1][j].rgbtBlue   + (float) temp_arr[i - 1][j + 1].rgbtBlue)   / 6);
                }
            }

            else //other lines
            {
                if (j ==0)
                {
                    image[i][j].rgbtRed     = (int) round(( (float) temp_arr[i - 1][j].rgbtRed      + (float) temp_arr[i - 1][j + 1].rgbtRed        +
                                                            (float) temp_arr[i][j].rgbtRed          + (float) temp_arr[i][j + 1].rgbtRed            +
                                                            (float) temp_arr[i + 1][j].rgbtRed      + (float) temp_arr[i + 1][j + 1].rgbtRed)           / 6);

                    image[i][j].rgbtGreen   = (int) round(( (float) temp_arr[i - 1][j].rgbtGreen    + (float) temp_arr[i - 1][j + 1].rgbtGreen      +
                                                            (float) temp_arr[i][j].rgbtGreen        + (float) temp_arr[i][j + 1].rgbtGreen          +
                                                            (float) temp_arr[i + 1][j].rgbtGreen    + (float) temp_arr[i + 1][j + 1].rgbtGreen)         / 6);

                    image[i][j].rgbtBlue    = (int) round(( (float) temp_arr[i - 1][j].rgbtBlue     + (float) temp_arr[i - 1][j + 1].rgbtBlue       +
                                                            (float) temp_arr[i][j].rgbtBlue         + (float) temp_arr[i][j + 1].rgbtBlue           +
                                                            (float) temp_arr[i + 1][j].rgbtBlue     + (float) temp_arr[i + 1][j + 1].rgbtBlue)          / 6);
                }
                else if (j == width - 1)
                {
                    image[i][j].rgbtRed     = (int) round(( (float) temp_arr[i - 1][j].rgbtRed      + (float) temp_arr[i - 1][j - 1].rgbtRed        +
                                                            (float) temp_arr[i][j].rgbtRed          + (float) temp_arr[i][j - 1].rgbtRed            +
                                                            (float) temp_arr[i + 1][j].rgbtRed      + (float) temp_arr[i + 1][j - 1].rgbtRed)           / 6);

                    image[i][j].rgbtGreen     = (int) round(( (float) temp_arr[i - 1][j].rgbtGreen      + (float) temp_arr[i - 1][j - 1].rgbtGreen  +
                                                            (float) temp_arr[i][j].rgbtGreen          + (float) temp_arr[i][j - 1].rgbtGreen        +
                                                            (float) temp_arr[i + 1][j].rgbtGreen      + (float) temp_arr[i + 1][j - 1].rgbtGreen)       / 6);

                    image[i][j].rgbtBlue     = (int) round(( (float) temp_arr[i - 1][j].rgbtBlue      + (float) temp_arr[i - 1][j - 1].rgbtBlue     +
                                                            (float) temp_arr[i][j].rgbtBlue          + (float) temp_arr[i][j - 1].rgbtBlue          +
                                                            (float) temp_arr[i + 1][j].rgbtBlue      + (float) temp_arr[i + 1][j - 1].rgbtBlue)         / 6);
                }
                else
                {
                    image[i][j].rgbtRed     = (int) round(( (float) temp_arr[i - 1][j - 1].rgbtRed      + (float) temp_arr[i - 1][j].rgbtRed    + (float) temp_arr[i - 1][j + 1].rgbtRed        +
                                                            (float) temp_arr[i][j - 1].rgbtRed          + (float) temp_arr[i][j].rgbtRed            + (float) temp_arr[i][j + 1].rgbtRed        +
                                                            (float) temp_arr[i + 1][j - 1].rgbtRed      + (float) temp_arr[i + 1][j].rgbtRed        + (float) temp_arr[i + 1][j + 1].rgbtRed)       / 9);

                    image[i][j].rgbtGreen   = (int) round(( (float) temp_arr[i - 1][j - 1].rgbtGreen  + (float) temp_arr[i - 1][j].rgbtGreen  + (float) temp_arr[i - 1][j + 1].rgbtGreen        +
                                                            (float) temp_arr[i][j - 1].rgbtGreen        + (float) temp_arr[i][j].rgbtGreen      + (float) temp_arr[i][j + 1].rgbtGreen          +
                                                            (float) temp_arr[i + 1][j - 1].rgbtGreen    + (float) temp_arr[i + 1][j].rgbtGreen  + (float) temp_arr[i + 1][j + 1].rgbtGreen)         / 9);

                    image[i][j].rgbtBlue    = (int) round(( (float) temp_arr[i - 1][j - 1].rgbtBlue    + (float) temp_arr[i - 1][j].rgbtBlue   + (float) temp_arr[i - 1][j + 1].rgbtBlue        +
                                                            (float) temp_arr[i][j - 1].rgbtBlue         + (float) temp_arr[i][j].rgbtBlue       + (float) temp_arr[i][j + 1].rgbtBlue           +
                                                            (float) temp_arr[i + 1][j - 1].rgbtBlue     + (float) temp_arr[i + 1][j].rgbtBlue   + (float) temp_arr[i + 1][j + 1].rgbtBlue)       / 9);
                }
            }
        }
    }


    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    typedef struct
    {
        int rgbtRed;
        int rgbtGreen;
        int rgbtBlue;
    }
    temp_array;

    temp_array temp_arr[height][width];

    int gxRed, gyRed, gxGreen, gyGreen, gxBlue, gyBlue;
    int tempRed, tempGreen, tempBlue;

    // copying into temp array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp_arr[i][j].rgbtRed = image[i][j].rgbtRed;
            temp_arr[i][j].rgbtGreen = image[i][j].rgbtGreen;
            temp_arr[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0) // top line
            {
                if (j == 0) // left corner
                {

                    gxRed   = -1 * 0    + 0 * 0                                 + 1 * 0
                              -2 * 0    + 0 * temp_arr[i][j].rgbtRed            + 2 * temp_arr[i][j + 1].rgbtRed
                              -1 * 0    + 0 * temp_arr[i + 1][j].rgbtRed        + 1 * temp_arr[i + 1][j + 1].rgbtRed;

                    gyRed   = -1 * 0    - 2 * 0                                 - 1 * 0                                     +
                               0 * 0    + 0 * temp_arr[i][j].rgbtRed            + 0 * temp_arr[i][j + 1].rgbtRed            +
                               1 * 0    + 2 * temp_arr[i + 1][j].rgbtRed        + 1 * temp_arr[i + 1][j + 1].rgbtRed;

                    gxGreen = -1 * 0    + 0 * 0                                 + 1 * 0
                              -2 * 0    + 0 * temp_arr[i][j].rgbtGreen          + 2 * temp_arr[i][j + 1].rgbtGreen
                              -1 * 0    + 0 * temp_arr[i + 1][j].rgbtGreen      + 1 * temp_arr[i + 1][j + 1].rgbtGreen;

                    gyGreen = -1 * 0    - 2 * 0                                 - 1 * 0                                     +
                               0 * 0    + 0 * temp_arr[i][j].rgbtGreen          + 0 * temp_arr[i][j + 1].rgbtGreen          +
                               1 * 0    + 2 * temp_arr[i + 1][j].rgbtGreen      + 1 * temp_arr[i + 1][j + 1].rgbtGreen;

                    gxBlue  = -1 * 0    + 0 * 0                                 + 1 * 0
                              -2 * 0    + 0 * temp_arr[i][j].rgbtBlue           + 2 * temp_arr[i][j + 1].rgbtBlue
                              -1 * 0    + 0 * temp_arr[i + 1][j].rgbtBlue       + 1 * temp_arr[i + 1][j + 1].rgbtBlue;

                    gyBlue  = -1 * 0    - 2 * 0                                 - 1 * 0                                     +
                               0 * 0    + 0 * temp_arr[i][j].rgbtBlue           + 0 * temp_arr[i][j + 1].rgbtBlue           +
                               1 * 0    + 2 * temp_arr[i + 1][j].rgbtBlue       + 1 * temp_arr[i + 1][j + 1].rgbtBlue;

                    tempRed     = (int) round(sqrt(pow(gxRed, 2.0) + pow(gyRed, 2.0)));
                    tempGreen   = (int) round(sqrt(pow(gxGreen, 2.0) + pow(gyGreen, 2.0)));
                    tempBlue    = (int) round(sqrt(pow(gxBlue, 2.0) + pow(gyBlue, 2.0)));

                    if (tempRed > 255)
                    {
                        tempRed = 255;
                    }
                    if (tempGreen > 255)
                    {
                        tempGreen = 255;
                    }
                    if (tempBlue > 255)
                    {
                        tempBlue = 255;
                    }

                    image[i][j].rgbtRed = tempRed;
                    image[i][j].rgbtGreen = tempGreen;
                    image[i][j].rgbtBlue = tempBlue;

                }
                else if (j == width - 1) //top line right corner
                {
                    gxRed   = -1 * 0                                    + 0 * 0                                 + 1 * 0
                              -2 * temp_arr[i][j - 1].rgbtRed           + 0 * temp_arr[i][j].rgbtRed            + 2 * 0
                              -1 * temp_arr[i + 1][j - 1].rgbtRed       + 0 * temp_arr[i + 1][j].rgbtRed        + 1 * 0;

                    gyRed   = -1 * 0                                    - 2 * 0                                 - 1 * 0     +
                               0 * temp_arr[i][j - 1].rgbtRed           + 0 * temp_arr[i][j].rgbtRed            + 0 * 0     +
                               1 * temp_arr[i + 1][j - 1].rgbtRed       + 2 * temp_arr[i + 1][j].rgbtRed        + 1 * 0;

                    gxGreen = -1 * 0                                    + 0 * 0                                 + 1 * 0
                              -2 * temp_arr[i][j - 1].rgbtGreen         + 0 * temp_arr[i][j].rgbtGreen          + 2 * 0
                              -1 * temp_arr[i + 1][j - 1].rgbtGreen     + 0 * temp_arr[i + 1][j].rgbtGreen      + 1 * 0;

                    gyGreen = -1 * 0                                    - 2 * 0                                 - 1 * 0     +
                               0 * temp_arr[i][j - 1].rgbtGreen         + 0 * temp_arr[i][j].rgbtGreen          + 0 * 0     +
                               1 * temp_arr[i + 1][j - 1].rgbtGreen     + 2 * temp_arr[i + 1][j].rgbtGreen      + 1 * 0;

                    gxBlue  = -1 * 0                                    + 0 * 0                                 + 1 * 0
                              -2 * temp_arr[i][j - 1].rgbtBlue          + 0 * temp_arr[i][j].rgbtBlue           + 2 * 0
                              -1 * temp_arr[i + 1][j - 1].rgbtBlue      + 0 * temp_arr[i + 1][j].rgbtBlue       + 1 * 0;

                    gyBlue  = -1 * 0                                    - 2 * 0                                 - 1 * 0     +
                               0 * temp_arr[i][j - 1].rgbtBlue          + 0 * temp_arr[i][j].rgbtBlue           + 0 * 0     +
                               1 * temp_arr[i + 1][j - 1].rgbtBlue      + 2 * temp_arr[i + 1][j].rgbtBlue       + 1 * 0;


                    tempRed     = (int) round(sqrt(pow(gxRed, 2.0) + pow(gyRed, 2.0)));
                    tempGreen   = (int) round(sqrt(pow(gxGreen, 2.0) + pow(gyGreen, 2.0)));
                    tempBlue    = (int) round(sqrt(pow(gxBlue, 2.0) + pow(gyBlue, 2.0)));

                    if (tempRed > 255)
                    {
                        tempRed = 255;
                    }
                    if (tempGreen > 255)
                    {
                        tempGreen = 255;
                    }
                    if (tempBlue > 255)
                    {
                        tempBlue = 255;
                    }

                    image[i][j].rgbtRed = tempRed;
                    image[i][j].rgbtGreen = tempGreen;
                    image[i][j].rgbtBlue = tempBlue;
                }
                else //top line between corners
                {
                    gxRed   = -1 * 0                                    + 0 * 0                                 + 1 * 0
                              -2 * temp_arr[i][j - 1].rgbtRed           + 0 * temp_arr[i][j].rgbtRed            + 2 * temp_arr[i][j + 1].rgbtRed
                              -1 * temp_arr[i + 1][j - 1].rgbtRed       + 0 * temp_arr[i + 1][j].rgbtRed        + 1 * temp_arr[i + 1][j + 1].rgbtRed;

                    gyRed   = -1 * 0                                    - 2 * 0                                 - 1 * 0                                     +
                               0 * temp_arr[i][j - 1].rgbtRed           + 0 * temp_arr[i][j].rgbtRed            + 0 * temp_arr[i][j + 1].rgbtRed            +
                               1 * temp_arr[i + 1][j - 1].rgbtRed       + 2 * temp_arr[i + 1][j].rgbtRed        + 1 * temp_arr[i + 1][j + 1].rgbtRed;

                    gxGreen = -1 * 0                                    + 0 * 0                                 + 1 * 0
                              -2 * temp_arr[i][j - 1].rgbtGreen         + 0 * temp_arr[i][j].rgbtGreen          + 2 * temp_arr[i][j + 1].rgbtGreen
                              -1 * temp_arr[i + 1][j - 1].rgbtGreen     + 0 * temp_arr[i + 1][j].rgbtGreen      + 1 * temp_arr[i + 1][j + 1].rgbtGreen;

                    gyGreen = -1 * 0                                    - 2 * 0                                 - 1 * 0                                     +
                               0 * temp_arr[i][j - 1].rgbtGreen         + 0 * temp_arr[i][j].rgbtGreen          + 0 * temp_arr[i][j + 1].rgbtGreen          +
                               1 * temp_arr[i + 1][j - 1].rgbtGreen     + 2 * temp_arr[i + 1][j].rgbtGreen      + 1 * temp_arr[i + 1][j + 1].rgbtGreen;

                    gxBlue  = -1 * 0                                    + 0 * 0                                 + 1 * 0
                              -2 * temp_arr[i][j - 1].rgbtBlue          + 0 * temp_arr[i][j].rgbtBlue           + 2 * temp_arr[i][j + 1].rgbtBlue
                              -1 * temp_arr[i + 1][j - 1].rgbtBlue      + 0 * temp_arr[i + 1][j].rgbtBlue       + 1 * temp_arr[i + 1][j + 1].rgbtBlue;

                    gyBlue  = -1 * 0                                    - 2 * 0                                 - 1 * 0       +
                               0 * temp_arr[i][j - 1].rgbtBlue          + 0 * temp_arr[i][j].rgbtBlue           + 0 * temp_arr[i][j + 1].rgbtBlue           +
                               1 * temp_arr[i + 1][j - 1].rgbtBlue      + 2 * temp_arr[i + 1][j].rgbtBlue       + 1 * temp_arr[i + 1][j + 1].rgbtBlue;

                    tempRed     = (int) round(sqrt(pow(gxRed, 2.0) + pow(gyRed, 2.0)));
                    tempGreen   = (int) round(sqrt(pow(gxGreen, 2.0) + pow(gyGreen, 2.0)));
                    tempBlue    = (int) round(sqrt(pow(gxBlue, 2.0) + pow(gyBlue, 2.0)));

                    if (tempRed > 255)
                    {
                        tempRed = 255;
                    }
                    if (tempGreen > 255)
                    {
                        tempGreen = 255;
                    }
                    if (tempBlue > 255)
                    {
                        tempBlue = 255;
                    }

                    image[i][j].rgbtRed = tempRed;
                    image[i][j].rgbtGreen = tempGreen;
                    image[i][j].rgbtBlue = tempBlue;
                }
            }

            else if (i == height - 1) // bottom line
            {
                if (j == 0) // left corner
                {
                    gxRed   = -1 * 0    + 0 * temp_arr[i - 1][j].rgbtRed        + 1 * temp_arr[i - 1][j + 1].rgbtRed
                              -2 * 0    + 0 * temp_arr[i][j].rgbtRed            + 2 * temp_arr[i][j + 1].rgbtRed
                              -1 * 0    + 0 * 0                                 + 1 * 0;

                    gyRed   = -1 * 0    - 2 * temp_arr[i - 1][j].rgbtRed        - 1 * temp_arr[i - 1][j + 1].rgbtRed        +
                               0 * 0    + 0 * temp_arr[i][j].rgbtRed            + 0 * temp_arr[i][j + 1].rgbtRed            +
                               1 * 0    + 2 * 0                                 + 1 * 0;

                    gxGreen = -1 * 0    + 0 * temp_arr[i - 1][j].rgbtGreen      + 1 * temp_arr[i - 1][j + 1].rgbtGreen
                              -2 * 0    + 0 * temp_arr[i][j].rgbtGreen          + 2 * temp_arr[i][j + 1].rgbtGreen
                              -1 * 0    + 0 * 0                                 + 1 * 0;

                    gyGreen = -1 * 0    - 2 * temp_arr[i - 1][j].rgbtGreen      - 1 * temp_arr[i - 1][j + 1].rgbtGreen        +
                               0 * 0    + 0 * temp_arr[i][j].rgbtGreen          + 0 * temp_arr[i][j + 1].rgbtGreen            +
                               1 * 0    + 2 * 0                                 + 1 * 0;

                    gxBlue  = -1 * 0    + 0 * temp_arr[i - 1][j].rgbtBlue       + 1 * temp_arr[i - 1][j + 1].rgbtBlue
                              -2 * 0    + 0 * temp_arr[i][j].rgbtBlue           + 2 * temp_arr[i][j + 1].rgbtBlue
                              -1 * 0    + 0 * 0                                 + 1 * 0;

                    gyBlue  = -1 * 0    - 2 * temp_arr[i - 1][j].rgbtBlue       - 1 * temp_arr[i - 1][j + 1].rgbtBlue        +
                               0 * 0    + 0 * temp_arr[i][j].rgbtBlue           + 0 * temp_arr[i][j + 1].rgbtBlue            +
                               1 * 0    + 2 * 0                                 + 1 * 0;

                    tempRed     = (int) round(sqrt(pow(gxRed, 2.0) + pow(gyRed, 2.0)));
                    tempGreen   = (int) round(sqrt(pow(gxGreen, 2.0) + pow(gyGreen, 2.0)));
                    tempBlue    = (int) round(sqrt(pow(gxBlue, 2.0) + pow(gyBlue, 2.0)));

                    if (tempRed > 255)
                    {
                        tempRed = 255;
                    }
                    if (tempGreen > 255)
                    {
                        tempGreen = 255;
                    }
                    if (tempBlue > 255)
                    {
                        tempBlue = 255;
                    }

                    image[i][j].rgbtRed = tempRed;
                    image[i][j].rgbtGreen = tempGreen;
                    image[i][j].rgbtBlue = tempBlue;
                }
                else if (j == width - 1) //right corner
                {
                    gxRed   = -1 * temp_arr[i - 1][j - 1].rgbtRed       + 0 * temp_arr[i - 1][j].rgbtRed        + 1 * 0
                              -2 * temp_arr[i][j - 1].rgbtRed           + 0 * temp_arr[i][j].rgbtRed            + 2 * 0
                              -1 * 0                                    + 0 * 0                                 + 1 * 0;

                    gyRed   = -1 * temp_arr[i - 1][j - 1].rgbtRed       - 2 * temp_arr[i - 1][j].rgbtRed        - 1 * 0     +
                               0 * temp_arr[i][j - 1].rgbtRed           + 0 * temp_arr[i][j].rgbtRed            + 0 * 0     +
                               1 * 0                                    + 2 * 0                                 + 1 * 0;

                    gxGreen = -1 * temp_arr[i - 1][j - 1].rgbtGreen     + 0 * temp_arr[i - 1][j].rgbtGreen      + 1 * 0
                              -2 * temp_arr[i][j - 1].rgbtGreen         + 0 * temp_arr[i][j].rgbtGreen          + 2 * 0
                              -1 * 0                                    + 0 * 0                                 + 1 * 0;

                    gyGreen = -1 * temp_arr[i - 1][j - 1].rgbtGreen     - 2 * temp_arr[i - 1][j].rgbtGreen      - 1 * 0     +
                               0 * temp_arr[i][j - 1].rgbtGreen         + 0 * temp_arr[i][j].rgbtGreen          + 0 * 0     +
                               1 * 0                                    + 2 * 0                                 + 1 * 0;

                    gxBlue  = -1 * temp_arr[i - 1][j - 1].rgbtBlue      + 0 * temp_arr[i - 1][j].rgbtBlue       + 1 * 0
                              -2 * temp_arr[i][j - 1].rgbtBlue          + 0 * temp_arr[i][j].rgbtBlue           + 2 * 0
                              -1 * 0                                    + 0 * 0                                 + 1 * 0;

                    gyBlue  = -1 * temp_arr[i - 1][j - 1].rgbtBlue      - 2 * temp_arr[i - 1][j].rgbtBlue       - 1 * 0     +
                               0 * temp_arr[i][j - 1].rgbtBlue          + 0 * temp_arr[i][j].rgbtBlue           + 0 * 0     +
                               1 * 0                                    + 2 * 0                                 + 1 * 0;

                    tempRed     = (int) round(sqrt(pow(gxRed, 2.0) + pow(gyRed, 2.0)));
                    tempGreen   = (int) round(sqrt(pow(gxGreen, 2.0) + pow(gyGreen, 2.0)));
                    tempBlue    = (int) round(sqrt(pow(gxBlue, 2.0) + pow(gyBlue, 2.0)));

                    if (tempRed > 255)
                    {
                        tempRed = 255;
                    }
                    if (tempGreen > 255)
                    {
                        tempGreen = 255;
                    }
                    if (tempBlue > 255)
                    {
                        tempBlue = 255;
                    }

                    image[i][j].rgbtRed = tempRed;
                    image[i][j].rgbtGreen = tempGreen;
                    image[i][j].rgbtBlue = tempBlue;
                }
                else //bottom line between corners
                {
                    gxRed   = -1 * temp_arr[i - 1][j - 1].rgbtRed       + 0 * temp_arr[i - 1][j].rgbtRed        + 1 * temp_arr[i - 1][j + 1].rgbtRed
                              -2 * temp_arr[i][j - 1].rgbtRed           + 0 * temp_arr[i][j].rgbtRed            + 2 * temp_arr[i][j + 1].rgbtRed
                              -1 * 0                                    + 0 * 0                                 + 1 * 0;

                    gyRed   = -1 * temp_arr[i - 1][j - 1].rgbtRed       - 2 * temp_arr[i - 1][j].rgbtRed        - 1 * temp_arr[i - 1][j + 1].rgbtRed        +
                               0 * temp_arr[i][j - 1].rgbtRed           + 0 * temp_arr[i][j].rgbtRed            + 0 * temp_arr[i][j + 1].rgbtRed            +
                               1 * 0                                    + 2 * 0                                 + 1 * 0;

                    gxGreen = -1 * temp_arr[i - 1][j - 1].rgbtGreen     + 0 * temp_arr[i - 1][j].rgbtGreen      + 1 * temp_arr[i - 1][j + 1].rgbtGreen
                              -2 * temp_arr[i][j - 1].rgbtGreen         + 0 * temp_arr[i][j].rgbtGreen          + 2 * temp_arr[i][j + 1].rgbtGreen
                              -1 * 0                                    + 0 * 0                                 + 1 * 0;

                    gyGreen = -1 * temp_arr[i - 1][j - 1].rgbtGreen     - 2 * temp_arr[i - 1][j].rgbtGreen      - 1 * temp_arr[i - 1][j + 1].rgbtGreen        +
                               0 * temp_arr[i][j - 1].rgbtGreen         + 0 * temp_arr[i][j].rgbtGreen          + 0 * temp_arr[i][j + 1].rgbtGreen            +
                               1 * 0                                    + 2 * 0                                 + 1 * 0;

                    gxBlue  = -1 * temp_arr[i - 1][j - 1].rgbtBlue      + 0 * temp_arr[i - 1][j].rgbtBlue       + 1 * temp_arr[i - 1][j + 1].rgbtBlue
                              -2 * temp_arr[i][j - 1].rgbtBlue          + 0 * temp_arr[i][j].rgbtBlue           + 2 * temp_arr[i][j + 1].rgbtBlue
                              -1 * 0                                    + 0 * 0                                 + 1 * 0;

                    gyBlue  = -1 * temp_arr[i - 1][j - 1].rgbtBlue      - 2 * temp_arr[i - 1][j].rgbtBlue       - 1 * temp_arr[i - 1][j + 1].rgbtBlue        +
                               0 * temp_arr[i][j - 1].rgbtBlue          + 0 * temp_arr[i][j].rgbtBlue           + 0 * temp_arr[i][j + 1].rgbtBlue            +
                               1 * 0                                    + 2 * 0                                 + 1 * 0;

                    tempRed     = (int) round(sqrt(pow(gxRed, 2.0) + pow(gyRed, 2.0)));
                    tempGreen   = (int) round(sqrt(pow(gxGreen, 2.0) + pow(gyGreen, 2.0)));
                    tempBlue    = (int) round(sqrt(pow(gxBlue, 2.0) + pow(gyBlue, 2.0)));

                    if (tempRed > 255)
                    {
                        tempRed = 255;
                    }
                    if (tempGreen > 255)
                    {
                        tempGreen = 255;
                    }
                    if (tempBlue > 255)
                    {
                        tempBlue = 255;
                    }

                    image[i][j].rgbtRed = tempRed;
                    image[i][j].rgbtGreen = tempGreen;
                    image[i][j].rgbtBlue = tempBlue;
                }
            }

            else //other lines
            {
                if (j ==0) //left line between virtical corners
                {
                    gxRed   = -1 * 0    + 0 * temp_arr[i - 1][j].rgbtRed        + 1 * temp_arr[i - 1][j + 1].rgbtRed
                              -2 * 0    + 0 * temp_arr[i][j].rgbtRed            + 2 * temp_arr[i][j + 1].rgbtRed
                              -1 * 0    + 0 * temp_arr[i + 1][j].rgbtRed        + 1 * temp_arr[i + 1][j + 1].rgbtRed;

                    gyRed   = -1 * 0    - 2 * temp_arr[i - 1][j].rgbtRed        - 1 * temp_arr[i - 1][j + 1].rgbtRed        +
                               0 * 0    + 0 * temp_arr[i][j].rgbtRed            + 0 * temp_arr[i][j + 1].rgbtRed            +
                               1 * 0    + 2 * temp_arr[i + 1][j].rgbtRed        + 1 * temp_arr[i + 1][j + 1].rgbtRed;

                    gxGreen = -1 * 0    + 0 * temp_arr[i - 1][j].rgbtGreen      + 1 * temp_arr[i - 1][j + 1].rgbtGreen
                              -2 * 0    + 0 * temp_arr[i][j].rgbtGreen          + 2 * temp_arr[i][j + 1].rgbtGreen
                              -1 * 0    + 0 * temp_arr[i + 1][j].rgbtGreen      + 1 * temp_arr[i + 1][j + 1].rgbtGreen;

                    gyGreen = -1 * 0    - 2 * temp_arr[i - 1][j].rgbtGreen      - 1 * temp_arr[i - 1][j + 1].rgbtGreen        +
                               0 * 0    + 0 * temp_arr[i][j].rgbtGreen          + 0 * temp_arr[i][j + 1].rgbtGreen            +
                               1 * 0    + 2 * temp_arr[i + 1][j].rgbtGreen      + 1 * temp_arr[i + 1][j + 1].rgbtGreen;

                    gxBlue  = -1 * 0    + 0 * temp_arr[i - 1][j].rgbtBlue       + 1 * temp_arr[i - 1][j + 1].rgbtBlue
                              -2 * 0    + 0 * temp_arr[i][j].rgbtBlue           + 2 * temp_arr[i][j + 1].rgbtBlue
                              -1 * 0    + 0 * temp_arr[i + 1][j].rgbtBlue       + 1 * temp_arr[i + 1][j + 1].rgbtBlue;

                    gyBlue  = -1 * 0    - 2 * temp_arr[i - 1][j].rgbtBlue       - 1 * temp_arr[i - 1][j + 1].rgbtBlue        +
                               0 * 0    + 0 * temp_arr[i][j].rgbtBlue           + 0 * temp_arr[i][j + 1].rgbtBlue            +
                               1 * 0    + 2 * temp_arr[i + 1][j].rgbtBlue       + 1 * temp_arr[i + 1][j + 1].rgbtBlue;

                    tempRed     = (int) round(sqrt(pow(gxRed, 2.0) + pow(gyRed, 2.0)));
                    tempGreen   = (int) round(sqrt(pow(gxGreen, 2.0) + pow(gyGreen, 2.0)));
                    tempBlue    = (int) round(sqrt(pow(gxBlue, 2.0) + pow(gyBlue, 2.0)));

                    if (tempRed > 255)
                    {
                        tempRed = 255;
                    }
                    if (tempGreen > 255)
                    {
                        tempGreen = 255;
                    }
                    if (tempBlue > 255)
                    {
                        tempBlue = 255;
                    }

                    image[i][j].rgbtRed = tempRed;
                    image[i][j].rgbtGreen = tempGreen;
                    image[i][j].rgbtBlue = tempBlue;
                }
                else if (j == width - 1) // right line between corners
                {
                    gxRed   = -1 * temp_arr[i - 1][j - 1].rgbtRed       + 0 * temp_arr[i - 1][j].rgbtRed        + 1 * 0
                              -2 * temp_arr[i][j - 1].rgbtRed           + 0 * temp_arr[i][j].rgbtRed            + 2 * 0
                              -1 * temp_arr[i + 1][j - 1].rgbtRed       + 0 * temp_arr[i + 1][j].rgbtRed        + 1 * 0;

                    gyRed   = -1 * temp_arr[i - 1][j - 1].rgbtRed       - 2 * temp_arr[i - 1][j].rgbtRed        - 1 * 0      +
                               0 * temp_arr[i][j - 1].rgbtRed           + 0 * temp_arr[i][j].rgbtRed            + 0 * 0      +
                               1 * temp_arr[i + 1][j - 1].rgbtRed       + 2 * temp_arr[i + 1][j].rgbtRed        + 1 * 0;

                    gxGreen = -1 * temp_arr[i - 1][j - 1].rgbtGreen     + 0 * temp_arr[i - 1][j].rgbtGreen      + 1 * 0
                              -2 * temp_arr[i][j - 1].rgbtGreen         + 0 * temp_arr[i][j].rgbtGreen          + 2 * 0
                              -1 * temp_arr[i + 1][j - 1].rgbtGreen     + 0 * temp_arr[i + 1][j].rgbtGreen      + 1 * 0;

                    gyGreen = -1 * temp_arr[i - 1][j - 1].rgbtGreen     - 2 * temp_arr[i - 1][j].rgbtGreen      - 1 * 0      +
                               0 * temp_arr[i][j - 1].rgbtGreen         + 0 * temp_arr[i][j].rgbtGreen          + 0 * 0      +
                               1 * temp_arr[i + 1][j - 1].rgbtGreen     + 2 * temp_arr[i + 1][j].rgbtGreen      + 1 * 0;

                    gxBlue  = -1 * temp_arr[i - 1][j - 1].rgbtBlue      + 0 * temp_arr[i - 1][j].rgbtBlue       + 1 * 0
                              -2 * temp_arr[i][j - 1].rgbtBlue          + 0 * temp_arr[i][j].rgbtBlue           + 2 * 0
                              -1 * temp_arr[i + 1][j - 1].rgbtBlue      + 0 * temp_arr[i + 1][j].rgbtBlue       + 1 * 0;

                    gyBlue  = -1 * temp_arr[i - 1][j - 1].rgbtBlue      - 2 * temp_arr[i - 1][j].rgbtBlue       - 1 * 0      +
                               0 * temp_arr[i][j - 1].rgbtBlue          + 0 * temp_arr[i][j].rgbtBlue           + 0 * 0      +
                               1 * temp_arr[i + 1][j - 1].rgbtBlue      + 2 * temp_arr[i + 1][j].rgbtBlue       + 1 * 0;

                    tempRed     = (int) round(sqrt(pow(gxRed, 2.0) + pow(gyRed, 2.0)));
                    tempGreen   = (int) round(sqrt(pow(gxGreen, 2.0) + pow(gyGreen, 2.0)));
                    tempBlue    = (int) round(sqrt(pow(gxBlue, 2.0) + pow(gyBlue, 2.0)));

                    if (tempRed > 255)
                    {
                        tempRed = 255;
                    }
                    if (tempGreen > 255)
                    {
                        tempGreen = 255;
                    }
                    if (tempBlue > 255)
                    {
                        tempBlue = 255;
                    }

                    image[i][j].rgbtRed = tempRed;
                    image[i][j].rgbtGreen = tempGreen;
                    image[i][j].rgbtBlue = tempBlue;
                }
                else // 3x3
                {
                    gxRed   = -1 * temp_arr[i - 1][j - 1].rgbtRed      + 0 * temp_arr[i - 1][j].rgbtRed        + 1 * temp_arr[i - 1][j + 1].rgbtRed
                              -2 * temp_arr[i][j - 1].rgbtRed          + 0 * temp_arr[i][j].rgbtRed            + 2 * temp_arr[i][j + 1].rgbtRed
                              -1 * temp_arr[i + 1][j - 1].rgbtRed      + 0 * temp_arr[i + 1][j].rgbtRed        + 1 * temp_arr[i + 1][j + 1].rgbtRed;

                    gyRed   = -1 * temp_arr[i - 1][j - 1].rgbtRed      - 2 * temp_arr[i - 1][j].rgbtRed        - 1 * temp_arr[i - 1][j + 1].rgbtRed        +
                               0 * temp_arr[i][j - 1].rgbtRed          + 0 * temp_arr[i][j].rgbtRed            + 0 * temp_arr[i][j + 1].rgbtRed            +
                               1 * temp_arr[i + 1][j - 1].rgbtRed      + 2 * temp_arr[i + 1][j].rgbtRed        + 1 * temp_arr[i + 1][j + 1].rgbtRed;

                    gxGreen = -1 * temp_arr[i - 1][j - 1].rgbtGreen    + 0 * temp_arr[i - 1][j].rgbtGreen      + 1 * temp_arr[i - 1][j + 1].rgbtGreen
                              -2 * temp_arr[i][j - 1].rgbtGreen        + 0 * temp_arr[i][j].rgbtGreen          + 2 * temp_arr[i][j + 1].rgbtGreen
                              -1 * temp_arr[i + 1][j - 1].rgbtGreen    + 0 * temp_arr[i + 1][j].rgbtGreen      + 1 * temp_arr[i + 1][j + 1].rgbtGreen;

                    gyGreen = -1 * temp_arr[i - 1][j - 1].rgbtGreen    - 2 * temp_arr[i - 1][j].rgbtGreen      - 1 * temp_arr[i - 1][j + 1].rgbtGreen        +
                               0 * temp_arr[i][j - 1].rgbtGreen        + 0 * temp_arr[i][j].rgbtGreen          + 0 * temp_arr[i][j + 1].rgbtGreen            +
                               1 * temp_arr[i + 1][j - 1].rgbtGreen    + 2 * temp_arr[i + 1][j].rgbtGreen      + 1 * temp_arr[i + 1][j + 1].rgbtGreen;

                    gxBlue  = -1 * temp_arr[i - 1][j - 1].rgbtBlue     + 0 * temp_arr[i - 1][j].rgbtBlue       + 1 * temp_arr[i - 1][j + 1].rgbtBlue
                              -2 * temp_arr[i][j - 1].rgbtBlue         + 0 * temp_arr[i][j].rgbtBlue           + 2 * temp_arr[i][j + 1].rgbtBlue
                              -1 * temp_arr[i + 1][j - 1].rgbtBlue     + 0 * temp_arr[i + 1][j].rgbtBlue       + 1 * temp_arr[i + 1][j + 1].rgbtBlue;

                    gyBlue  = -1 * temp_arr[i - 1][j - 1].rgbtBlue     - 2 * temp_arr[i - 1][j].rgbtBlue       - 1 * temp_arr[i - 1][j + 1].rgbtBlue        +
                               0 * temp_arr[i][j - 1].rgbtBlue         + 0 * temp_arr[i][j].rgbtBlue           + 0 * temp_arr[i][j + 1].rgbtBlue            +
                               1 * temp_arr[i + 1][j - 1].rgbtBlue     + 2 * temp_arr[i + 1][j].rgbtBlue       + 1 * temp_arr[i + 1][j + 1].rgbtBlue;

                    tempRed     = (int) round(sqrt(pow(gxRed, 2.0) + pow(gyRed, 2.0)));
                    tempGreen   = (int) round(sqrt(pow(gxGreen, 2.0) + pow(gyGreen, 2.0)));
                    tempBlue    = (int) round(sqrt(pow(gxBlue, 2.0) + pow(gyBlue, 2.0)));

                    if (tempRed > 255)
                    {
                        tempRed = 255;
                    }
                    if (tempGreen > 255)
                    {
                        tempGreen = 255;
                    }
                    if (tempBlue > 255)
                    {
                        tempBlue = 255;
                    }

                    image[i][j].rgbtRed = tempRed;
                    image[i][j].rgbtGreen = tempGreen;
                    image[i][j].rgbtBlue = tempBlue;
                }
            }
        }
    }


    return;
}
