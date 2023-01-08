#include "helpers.h"
#include <stdio.h>
#include <math.h>
#include <cs50.h>

// data type for temporary rgb values
typedef struct
{
    int  rgbtBlue;
    int  rgbtGreen;
    int  rgbtRed;
}
RGBCOPY;

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Average value between blue green and red
            int average = round((float)(image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pixels from left and ride sides until they "meet" in the centre
            RGBTRIPLE tp = image[i][j];
            image[i][j] = image[i][(width - 1) - j];
            image[i][(width - 1) - j] = tp;
        }
    }
    return;
}
// Defines a multiplier for OX
int ratex(int a, int b, int i, int j)
{
    // Case with left top and bottom pixels
    if (((a == i - 1) || (a == i + 1)) && (b == j - 1))
    {
        return -1;
    }
    // Case with right top and bottom pixels
    if (((a == i - 1) || (a == i + 1)) && (b == j + 1))
    {
        return 1;
    }
    // Case with middle left pixel
    if ((a == i) && (b == j - 1))
    {
        return -2;
    }
    // Case with middle right pixel
    if ((a == i) && (b == j + 1))
    {
        return 2;
    }
    return 0;
}

// Defines a multiplier for OY
int ratey(int a, int b, int i, int j)
{
    // Case with top left and right pixels
    if (((b == j - 1) || (b == j + 1)) && (a == i - 1))
    {
        return -1;
    }
    // Case with bottom left and right pixels
    if (((b == j - 1) || (b == j + 1)) && (a == i + 1))
    {
        return 1;
    }
    // Case with top middle pixel
    if ((b == j) && (a == i - 1))
    {
        return -2;
    }
    // Case with bottom middle pixel
    if ((b == j) && (a == i + 1))
    {
        return 2;
    }
    return 0;
}

// Check if a pixel out of the image
bool limit(int a, int b, int height, int width)
{
    if ((a >= height) || (b >= width) || (a < 0) || (b < 0))
    {
        return true;
    }
    return false;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Array where to store an image at first
    RGBCOPY image_copy[height][width];
    // Set all values to 0
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_copy[i][j].rgbtBlue = 0;
            image_copy[i][j].rgbtGreen = 0;
            image_copy[i][j].rgbtRed = 0;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate adjacent pixels
            double sum = 0;
            // Go through all adjacent pixels
            for (int a = i - 1; a <= i + 1; a++)
            {
                for (int b = j - 1; b <= j + 1; b++)
                {
                    // Check if it goes out of the image
                    if (!limit(a, b, height, width))
                    {
                        // Add the values of colours of all adjacent pixels
                        image_copy[i][j].rgbtBlue =  image_copy[i][j].rgbtBlue + image[a][b].rgbtBlue;
                        image_copy[i][j].rgbtGreen =  image_copy[i][j].rgbtGreen + image[a][b].rgbtGreen;
                        image_copy[i][j].rgbtRed =  image_copy[i][j].rgbtRed + image[a][b].rgbtRed;
                        sum++;
                    }
                }
            }
            // Find an average for every colour
            image_copy[i][j].rgbtBlue = round((double)((image_copy[i][j].rgbtBlue) / sum));
            image_copy[i][j].rgbtGreen = round((double)((image_copy[i][j].rgbtGreen) / sum));
            image_copy[i][j].rgbtRed = round((double)((image_copy[i][j].rgbtRed) / sum));
        }
    }
    // Rewrite initial image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = image_copy[i][j].rgbtBlue;
            image[i][j].rgbtGreen = image_copy[i][j].rgbtGreen;
            image[i][j].rgbtRed = image_copy[i][j].rgbtRed;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Array for temporary image
    RGBCOPY image_copy[height][width];
    // Set all values to 0
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_copy[i][j].rgbtBlue = 0;
            image_copy[i][j].rgbtGreen = 0;
            image_copy[i][j].rgbtRed = 0;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int bluex = 0;
            int greenx = 0;
            int redx = 0;
            int bluey = 0;
            int greeny = 0;
            int redy = 0;
            // Go through all adjacent pixels
            for (int a = i - 1; a <= i + 1; a++)
            {
                for (int b = j - 1; b <= j + 1; b++)
                {
                    // Check if it goes out of image
                    if (!limit(a, b, height, width))
                    {
                        // Define ratios for particular case
                        int kx = ratex(a, b, i, j);
                        int ky = ratey(a, b, i, j);
                        {
                            // Add all values of colours of GX matrix
                            bluex = bluex + kx * image[a][b].rgbtBlue;
                            greenx =  greenx + kx * image[a][b].rgbtGreen;
                            redx =  redx + kx * image[a][b].rgbtRed;
                            // Add all values of colours of GY matrix
                            bluey =  bluey + ky * image[a][b].rgbtBlue;
                            greeny =  greeny + ky * image[a][b].rgbtGreen;
                            redy =  redy + ky * image[a][b].rgbtRed;
                        }
                    }
                }
            }
            // Calculate "average" for all colours
            int blue = round((double)sqrt(pow(bluex, 2) + pow(bluey, 2)));
            int green = round((double)sqrt(pow(greenx, 2) + pow(greeny, 2)));
            int red = round((double)sqrt(pow(redx, 2) + pow(redy, 2)));
            // Illuminate cases when colour exceed it's max value
            if (blue > 255)
            {
                blue = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (red > 255)
            {
                red = 255;
            }
            // Assign new values to the temporary image
            image_copy[i][j].rgbtBlue = blue;
            image_copy[i][j].rgbtGreen = green;
            image_copy[i][j].rgbtRed = red;
        }
    }
    // Rewtire initial image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = image_copy[i][j].rgbtBlue;
            image[i][j].rgbtGreen = image_copy[i][j].rgbtGreen;
            image[i][j].rgbtRed = image_copy[i][j].rgbtRed;
        }
    }

    return;
}
