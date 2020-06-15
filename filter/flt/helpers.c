#include "helpers.h"
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{   
    
    
    for (int i = 0; i < height; i++)
    {
        for (int j =0; j < width; j++)
        {
            int avrg = ((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3);
            image[i][j].rgbtBlue = avrg;
            image[i][j].rgbtGreen = avrg;
            image[i][j].rgbtRed = avrg;
            
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*reflection)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            reflection[i][j].rgbtBlue = image[i][width-1-j].rgbtBlue;
            reflection[i][j].rgbtGreen = image[i][width-1-j].rgbtGreen;
            reflection[i][j].rgbtRed = image[i][width-1-j].rgbtRed;

        }
        for (int k = 0; k < width; k++)
        {
            image[i][k].rgbtBlue = reflection[i][k].rgbtBlue;
            image[i][k].rgbtGreen = reflection[i][k].rgbtGreen;
            image[i][k].rgbtRed = reflection[i][k].rgbtRed;

        }
        
        
    }
    free(reflection);
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*blur)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    for (int i = 1; i < height-1; i++)
    {
        for (int j = 1; j < width-1; j++)
        {
            int blue = 0;
            int red = 0;
            int green = 0;
            for (int l = i-1; l<i+2; l++)
            {
                for (int m = j-1; m<j+2; m++)
                {
                    
                        blue = blue + image[l][m].rgbtBlue;
                        red = red+ image[l][m].rgbtRed;
                        green = green + image[l][m].rgbtGreen;
                    
                }
            }
            blur[i][j].rgbtBlue = blue/9;
            blur[i][j].rgbtGreen = green/9;
            blur[i][j].rgbtRed = red/9;

        }
    }
    for (int m = 0; m < height; m++)
    {
        for (int o =0; o < width; o++)
        {
            image[m][o].rgbtBlue = blur[m][o].rgbtBlue;
            image[m][o].rgbtGreen = blur[m][o].rgbtGreen;
            image[m][o].rgbtRed = blur[m][o].rgbtRed;
        }
    }
    free(blur);
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 1; i < height-1; i++)
    {
        for (int j = 1; j < width-1; j++)
        {
            int blue = 0;
            int red = 0;
            int green = 0;
            
                    
            bluex = blue + image[l][m].rgbtBlue;
            redx = red+ image[l][m].rgbtRed;
            greenx = green + image[l][m].rgbtGreen;
            
            bluey = blue + image[l][m].rgbtBlue;
            redy = red+ image[l][m].rgbtRed;
            greeny = green + image[l][m].rgbtGreen;
                    
                }
            }
    return;
}
