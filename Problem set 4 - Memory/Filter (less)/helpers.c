#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //Find mean value and substitute original
            int mean = round(((float)image[h][w].rgbtBlue + (float)image[h][w].rgbtGreen + (float)image[h][w].rgbtRed) / (float)3);
            image[h][w].rgbtBlue = mean;
            image[h][w].rgbtGreen = mean;
            image[h][w].rgbtRed = mean;
        }
    }
    
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //Find sepia value for every RGB value
            int sepiaRed = round(.393 * image[h][w].rgbtRed + .769 * image[h][w].rgbtGreen + .189 * image[h][w].rgbtBlue);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            int sepiaGreen = round(.349 * image[h][w].rgbtRed + .686 * image[h][w].rgbtGreen + .168 * image[h][w].rgbtBlue);
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            int sepiaBlue = round(.272 * image[h][w].rgbtRed + .534 * image[h][w].rgbtGreen + .131 * image[h][w].rgbtBlue);
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            
            //Substitute sepia values to originals
            image[h][w].rgbtBlue = sepiaBlue;
            image[h][w].rgbtGreen = sepiaGreen;
            image[h][w].rgbtRed = sepiaRed;
        }
    }
    
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < round((float)width / 2); w++)
        {
            //Save left pixels in a temporary variable
            int tmp_rgbtBlue = image[h][w].rgbtBlue;
            int tmp_rgbtGreen = image[h][w].rgbtGreen;
            int tmp_rgbtRed = image[h][w].rgbtRed;
            
            //Substitute right pixels to left pixels
            image[h][w].rgbtBlue = image[h][width - 1 - w].rgbtBlue;
            image[h][w].rgbtGreen = image[h][width - 1 - w].rgbtGreen;
            image[h][w].rgbtRed = image[h][width - 1 - w].rgbtRed;
            
            //Save left pixels from temporary variable to right pixels
            image[h][width - 1 - w].rgbtBlue = tmp_rgbtBlue;
            image[h][width - 1 - w].rgbtGreen = tmp_rgbtGreen;
            image[h][width - 1 - w].rgbtRed = tmp_rgbtRed;
        }
    }
    
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Make a temporary image array
    RGBTRIPLE blurimage[height][width];
    
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //Declare mean variables for every color and pixel counter
            int meanBlue = 0;
            int meanGreen = 0;
            int meanRed = 0;
            int pixel = 0;
            
            //Consider pixels around the selected actual one, if they exist            
            for (int hm = h - 1; hm <= h + 1; hm++)
            {
                if (hm >= 0 && hm < height)
                {
                    for (int wm = w - 1; wm <= w + 1; wm++)
                    {
                        if (wm >= 0 && wm < width)
                        {
                            //Add 1 to pixel counter and add RGB values in the relatives variables
                            pixel++;
                            meanBlue += image[hm][wm].rgbtBlue;
                            meanGreen += image[hm][wm].rgbtGreen;
                            meanRed += image[hm][wm].rgbtRed;
                        }
                    }
                }
            }
            
            //Calculate mean for every color value
            meanBlue = round((float)meanBlue / (float)pixel);
            meanGreen = round((float)meanGreen / (float)pixel);
            meanRed = round((float)meanRed / (float)pixel);
            
            //Build blured temporary image with blured pixels
            blurimage[h][w].rgbtBlue = meanBlue;
            blurimage[h][w].rgbtGreen = meanGreen;
            blurimage[h][w].rgbtRed = meanRed;
        }
    }
    
    //Substitute blured pixels to original image
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w].rgbtBlue = blurimage[h][w].rgbtBlue;
            image[h][w].rgbtGreen = blurimage[h][w].rgbtGreen;
            image[h][w].rgbtRed = blurimage[h][w].rgbtRed;
        }
    }
    
    return;
}
