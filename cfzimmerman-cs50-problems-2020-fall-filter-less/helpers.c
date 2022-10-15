#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            // Convert colors to average or RGB values
            int average = round((float)(image[a][b].rgbtBlue + image[a][b].rgbtGreen + image[a][b].rgbtRed)/3);
            
            image[a][b].rgbtBlue = average;
            image[a][b].rgbtGreen = average;
            image[a][b].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{ 
    int sblue[height][width];
    int sgreen[height][width];
    int sred[height][width];
    
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            // Follow a basic formula to calculate the sepia values of RGB
            
            sblue[a][b] = round((float)((0.272 * image[a][b].rgbtRed) + (0.534 * image[a][b].rgbtGreen) + (0.131 * image[a][b].rgbtBlue))); 
            sgreen[a][b] = round((float)((0.349 * image[a][b].rgbtRed) + (0.686 * image[a][b].rgbtGreen) + (0.168 * image[a][b].rgbtBlue)));
            sred[a][b] = round((float)((0.393 * image[a][b].rgbtRed) + (0.769 * image[a][b].rgbtGreen) + (0.189 * image[a][b].rgbtBlue)));
            
            // If the result is greater than the maximum hex value for an RGB value, round that number down to 255
            if (sblue[a][b] > 255)
            {
                sblue[a][b] = 255;
            }
            
            if (sgreen[a][b] > 255)
            {
                sgreen[a][b] = 255;
            }
            
            if (sred[a][b] > 255)
            {
                sred[a][b] = 255;
            }
        }
    }
    
    // Repopulate the actual color grid with the calculated and rounded values
    for (int c = 0; c < height; c++)
    {
        for (int d = 0; d < height; d++)
        {
            image[c][d].rgbtBlue = sblue[c][d];
            image[c][d].rgbtGreen = sgreen[c][d];
            image[c][d].rgbtRed = sred[c][d];
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int tempb[width - 1];
    int tempg[width - 1];
    int tempr[width - 1];
    
    // Copy the original values of each row into a temporary array. Execute the array backwards to save reflected values
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            tempb[b] = image[a][b].rgbtBlue;
            tempg[b] = image[a][b].rgbtGreen;
            tempr[b] = image[a][b].rgbtRed;
        }

        for (int c = 0; c < width; c++)
        {
            image[a][c].rgbtBlue = tempb[width - 1 - c];
            image[a][c].rgbtGreen = tempg[width - 1 - c];
            image[a][c].rgbtRed = tempr[width - 1 - c];
        }
    }
    
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
        
    int blurb[height][width];
    int blurg[height][width];
    int blurr[height][width];

    // Assuming a box grid of values, calculate a two-dimensional array of blur value accounting for each edge, corner, or middle case, horizontally and vertically. Copy blur array into original values.
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            if (a == 0)
            {
                // If the array has one row, this calculates the color of the far left pixel
               if ((b == 0) && (height == 1))
                {
                    blurb[a][b] = round((float)(image[a][b].rgbtBlue + image[a][b + 1].rgbtBlue) / 2);
                    blurg[a][b] = round((float)(image[a][b].rgbtGreen + image[a][b + 1].rgbtGreen) / 2);
                    blurr[a][b] = round((float)(image[a][b].rgbtRed + image[a][b + 1].rgbtRed) / 2);                    
                }
                // If the array has one row, this calculates the color of the middle pixels
                else if ((b != 0) && (b != (width - 1)) && (height == 1))
                {
                    blurb[a][b] = round((float)(image[a][b - 1].rgbtBlue + image[a][b].rgbtBlue + image[a][b + 1].rgbtBlue) / 3);
                    blurg[a][b] = round((float)(image[a][b - 1].rgbtGreen + image[a][b].rgbtGreen + image[a][b + 1].rgbtGreen) / 3);
                    blurr[a][b] = round((float)(image[a][b - 1].rgbtRed + image[a][b].rgbtRed + image[a][b + 1].rgbtRed) / 3);                   
                }
                // If the array has one row, this calculates the color of the far right pixel
                else if ((b == (width - 1)) && (height == 1))
                {
                    blurb[a][b] = round((float)(image[a][b - 1].rgbtBlue + image[a][b].rgbtBlue) / 2);
                    blurg[a][b] = round((float)(image[a][b - 1].rgbtGreen + image[a][b].rgbtGreen) / 2);
                    blurr[a][b] = round((float)(image[a][b - 1].rgbtRed + image[a][b].rgbtRed) / 2);                   
                } 
                // If the array has more than one row, this calculates the color of the top far left pixel
                else if ((b == 0) && (height > 1))
                {
                    blurb[a][b] = round((float)(image[a][b].rgbtBlue + image[a][b + 1].rgbtBlue + image[a + 1][b].rgbtBlue + image[a + 1][b + 1].rgbtBlue) / 4);
                    blurg[a][b] = round((float)(image[a][b].rgbtGreen + image[a][b + 1].rgbtGreen + image[a + 1][b].rgbtGreen + image[a + 1][b + 1].rgbtGreen) / 4);
                    blurr[a][b] = round((float)(image[a][b].rgbtRed + image[a][b + 1].rgbtRed + image[a + 1][b].rgbtRed + image[a + 1][b + 1].rgbtRed) / 4);                 
                }
                // If the array has more than one row, this calculates the color of the top far right pixel
                else if (b == (width - 1))
                {
                    blurb[a][b] = round((float)(image[a][b].rgbtBlue + image[a][b - 1].rgbtBlue + image[a + 1][b].rgbtBlue + image[a + 1][b - 1].rgbtBlue) / 4);
                    blurg[a][b] = round((float)(image[a][b].rgbtGreen + image[a][b - 1].rgbtGreen + image[a + 1][b].rgbtGreen + image[a + 1][b - 1].rgbtGreen) / 4);
                    blurr[a][b] = round((float)(image[a][b].rgbtRed + image[a][b - 1].rgbtRed + image[a + 1][b].rgbtRed + image[a + 1][b - 1].rgbtRed) / 4);             
                }
                // If the array has more than one row, this calculates the colors of the middle top pixels
                else if ((a == 0) && (b != 0) && (b != (width - 1)))
                {
                    blurb[a][b] = round((float)(image[a][b - 1].rgbtBlue + image[a][b].rgbtBlue + image[a][b + 1].rgbtBlue + image[a + 1][b - 1].rgbtBlue + image[a + 1][b].rgbtBlue + image[a + 1][b + 1].rgbtBlue) / 6);
                    blurg[a][b] = round((float)(image[a][b - 1].rgbtGreen + image[a][b].rgbtGreen + image[a][b + 1].rgbtGreen + image[a + 1][b - 1].rgbtGreen + image[a + 1][b].rgbtGreen + image[a + 1][b + 1].rgbtGreen) / 6);                    
                    blurr[a][b] = round((float)(image[a][b - 1].rgbtRed + image[a][b].rgbtRed + image[a][b + 1].rgbtRed + image[a + 1][b - 1].rgbtRed + image[a + 1][b].rgbtRed + image[a + 1][b + 1].rgbtRed) / 6);
                }
            }
            else if (a == (height - 1))
            {
                // This calculates the color of the pixel in the bottom left corner
                if (b == 0)
                {
                    blurb[a][b] = round((float)(image[a - 1][b].rgbtBlue + image[a - 1][b + 1].rgbtBlue + image[a][b].rgbtBlue + image[a][b + 1].rgbtBlue) / 4);
                    blurg[a][b] = round((float)(image[a - 1][b].rgbtGreen + image[a - 1][b + 1].rgbtGreen + image[a][b].rgbtGreen + image[a][b + 1].rgbtGreen) / 4);
                    blurr[a][b] = round((float)(image[a - 1][b].rgbtRed + image[a - 1][b + 1].rgbtRed + image[a][b].rgbtRed + image[a][b + 1].rgbtRed) / 4);                  
                }
                // This calculates the color of the pixel in the bottom right corner
                else if (b == (width - 1))
                {
                    blurb[a][b] = round((float)(image[a - 1][b - 1].rgbtBlue + image[a - 1][b].rgbtBlue + image[a][b - 1].rgbtBlue + image[a][b].rgbtBlue) / 4);
                    blurg[a][b] = round((float)(image[a - 1][b - 1].rgbtGreen + image[a - 1][b].rgbtGreen + image[a][b - 1].rgbtGreen + image[a][b].rgbtGreen) / 4);
                    blurr[a][b] = round((float)(image[a - 1][b - 1].rgbtRed + image[a - 1][b].rgbtRed + image[a][b - 1].rgbtRed + image[a][b].rgbtRed) / 4);                  
                }
                else
                // This calculates the colors of the bottom pixels between the left and right corners
                {
                    blurb[a][b] = round((float)(image[a - 1][b - 1].rgbtBlue + image[a - 1][b].rgbtBlue + image[a - 1][b + 1].rgbtBlue + image[a][b - 1].rgbtBlue + image[a][b].rgbtBlue + image[a][b + 1].rgbtBlue) / 6);
                    blurg[a][b] = round((float)(image[a - 1][b - 1].rgbtGreen + image[a - 1][b].rgbtGreen + image[a - 1][b + 1].rgbtGreen + image[a][b - 1].rgbtGreen + image[a][b].rgbtGreen + image[a][b + 1].rgbtGreen) / 6);
                    blurr[a][b] = round((float)(image[a - 1][b - 1].rgbtRed + image[a - 1][b].rgbtRed + image[a - 1][b + 1].rgbtRed + image[a][b - 1].rgbtRed + image[a][b].rgbtRed + image[a][b + 1].rgbtRed) / 6);
                }
            }
            // This calculates the colors of pixels on the far left side excluding the top and bottom corners
            else if ((b == 0) && (a != 0) && (a != (height - 1)))
            {
                blurb[a][b] = round((float)(image[a - 1][b].rgbtBlue + image[a - 1][b + 1].rgbtBlue + image[a][b].rgbtBlue + image[a][b + 1].rgbtBlue + image[a + 1][b].rgbtBlue + image[a + 1][b + 1].rgbtBlue) / 6);
                blurg[a][b] = round((float)(image[a - 1][b].rgbtGreen + image[a - 1][b + 1].rgbtGreen + image[a][b].rgbtGreen + image[a][b + 1].rgbtGreen + image[a + 1][b].rgbtGreen + image[a + 1][b + 1].rgbtGreen) / 6);
                blurr[a][b] = round((float)(image[a - 1][b].rgbtRed + image[a - 1][b + 1].rgbtRed + image[a][b].rgbtRed + image[a][b + 1].rgbtRed + image[a + 1][b].rgbtRed + image[a + 1][b + 1].rgbtRed) / 6);
            }
            // This calculates the colors of pixels on the far right side excluding the top and bottom corners
            else if (b == (width - 1) && (a != 0) && (a != (height - 1)))
            {
                blurb[a][b] = round((float)(image[a - 1][b - 1].rgbtBlue + image[a - 1][b].rgbtBlue + image[a][b - 1].rgbtBlue + image[a][b].rgbtBlue + image[a + 1][b - 1].rgbtBlue + image[a + 1][b].rgbtBlue) / 6);
                blurg[a][b] = round((float)(image[a - 1][b - 1].rgbtGreen + image[a - 1][b].rgbtGreen + image[a][b - 1].rgbtGreen + image[a][b].rgbtGreen + image[a + 1][b - 1].rgbtGreen + image[a + 1][b].rgbtGreen) / 6);
                blurr[a][b] = round((float)(image[a - 1][b - 1].rgbtRed + image[a - 1][b].rgbtRed + image[a][b - 1].rgbtRed + image[a][b].rgbtRed + image[a + 1][b - 1].rgbtRed + image[a + 1][b].rgbtRed) / 6);
            }
            else if ((a != 0) && (a != (height - 1)) && (b != 0) && (b != (width - 1)))
            {
                blurb[a][b] = round((float)(image[a - 1][b - 1].rgbtBlue + image[a - 1][b].rgbtBlue + image[a - 1][b + 1].rgbtBlue + image[a][b - 1].rgbtBlue + image[a][b].rgbtBlue + image[a][b + 1].rgbtBlue + image[a + 1][b - 1].rgbtBlue + image[a + 1][b].rgbtBlue + image[a + 1][b + 1].rgbtBlue) / 9);
                blurg[a][b] = round((float)(image[a - 1][b - 1].rgbtGreen + image[a - 1][b].rgbtGreen + image[a - 1][b + 1].rgbtGreen + image[a][b - 1].rgbtGreen + image[a][b].rgbtGreen + image[a][b + 1].rgbtGreen + image[a + 1][b - 1].rgbtGreen + image[a + 1][b].rgbtGreen + image[a + 1][b + 1].rgbtGreen) / 9);
                blurr[a][b] = round((float)(image[a - 1][b - 1].rgbtRed + image[a - 1][b].rgbtRed + image[a - 1][b + 1].rgbtRed + image[a][b - 1].rgbtRed + image[a][b].rgbtRed + image[a][b + 1].rgbtRed + image[a + 1][b - 1].rgbtRed + image[a + 1][b].rgbtRed + image[a + 1][b + 1].rgbtRed) / 9);
            }
        }
        
        
    }
    
    for (int c = 0; c < height; c++)
    {
        for (int d = 0; d < width; d++)
        {
            image[c][d].rgbtBlue = blurb[c][d];
            image[c][d].rgbtGreen = blurg[c][d];
            image[c][d].rgbtRed = blurr[c][d];
        }
    }
    
    return;
}
