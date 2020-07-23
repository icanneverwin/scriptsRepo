#include "helpers.h"
#include "math.h"

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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    int max_value = 255;
    float sepiaRed, sepiaGreen, sepiaBlue;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //calculate RGB values according to sepie formula
            sepiaRed = round(0.393 * (float) image[i][j].rgbtRed + 0.769 * (float) image[i][j].rgbtGreen + 0.189 * (float) image[i][j].rgbtBlue);
            sepiaGreen = round(0.349 * (float) image[i][j].rgbtRed + 0.686 * (float) image[i][j].rgbtGreen + 0.168 * (float) image[i][j].rgbtBlue);
            sepiaBlue = round(0.272 * (float) image[i][j].rgbtRed + 0.534 * (float) image[i][j].rgbtGreen + 0.131 * (float) image[i][j].rgbtBlue);

            // check if each value is higher then 255
            if (sepiaRed > 255)
            {
                sepiaRed = max_value;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = max_value;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = max_value;
            }

            image[i][j].rgbtBlue = (int) sepiaBlue;
            image[i][j].rgbtGreen = (int) sepiaGreen;
            image[i][j].rgbtRed = (int) sepiaRed;
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
