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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //Make a temporary image array
    RGBTRIPLE imageSobel[height][width];
    
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            double blueGx = 0;
            double greenGx = 0;
            double redGx = 0;
            
            double blueGy = 0;
            double greenGy = 0;
            double redGy = 0;
            
            for (int hG = h - 1; hG <= h + 1; hG++)
            {
                for (int wG = w - 1; wG <= w + 1; wG++)
                {
                    if (hG == h - 1 && wG == w - 1) //high left
                    {
                        if (hG >= 0 && hG < height && wG >= 0 && wG < width)
                        {
                            blueGx -= image[hG][wG].rgbtBlue;
                            greenGx -= image[hG][wG].rgbtGreen;
                            redGx -= image[hG][wG].rgbtRed;
                            
                            blueGy -= image[hG][wG].rgbtBlue;
                            greenGy -= image[hG][wG].rgbtGreen;
                            redGy -= image[hG][wG].rgbtRed;
                        }
                    }
                    else if (hG == h - 1 && wG == w) //high
                    {
                        if (hG >= 0 && hG < height && wG >= 0 && wG < width)
                        {
                            blueGy += image[hG][wG].rgbtBlue * -2;
                            greenGy += image[hG][wG].rgbtGreen * -2;
                            redGy += image[hG][wG].rgbtRed * -2;
                        }
                    }
                    else if (hG == h - 1 && wG == w + 1) //high right
                    {
                        if (hG >= 0 && hG < height && wG >= 0 && wG < width)
                        {
                            blueGx += image[hG][wG].rgbtBlue;
                            greenGx += image[hG][wG].rgbtGreen;
                            redGx += image[hG][wG].rgbtRed;
                            
                            blueGy -= image[hG][wG].rgbtBlue;
                            greenGy -= image[hG][wG].rgbtGreen;
                            redGy -= image[hG][wG].rgbtRed;
                        }
                    }
                    else if (hG == h && wG == w - 1) //left
                    {
                        if (hG >= 0 && hG < height && wG >= 0 && wG < width)
                        {
                            blueGx += image[hG][wG].rgbtBlue * -2;
                            greenGx += image[hG][wG].rgbtGreen * -2;
                            redGx += image[hG][wG].rgbtRed * -2;
                        }
                    }
                    else if (hG == h && wG == w + 1) //right
                    {
                        if (hG >= 0 && hG < height && wG >= 0 && wG < width)
                        {
                            blueGx += image[hG][wG].rgbtBlue * 2;
                            greenGx += image[hG][wG].rgbtGreen * 2;
                            redGx += image[hG][wG].rgbtRed * 2;
                        }
                    }
                    else if (hG == h + 1 && wG == w - 1) //down left
                    {
                        if (hG >= 0 && hG < height && wG >= 0 && wG < width)
                        {
                            blueGx -= image[hG][wG].rgbtBlue;
                            greenGx -= image[hG][wG].rgbtGreen;
                            redGx -= image[hG][wG].rgbtRed;
                            
                            blueGy += image[hG][wG].rgbtBlue;
                            greenGy += image[hG][wG].rgbtGreen;
                            redGy += image[hG][wG].rgbtRed;
                        }
                    }
                    else if (hG == h + 1 && wG == w) //down
                    {
                        if (hG >= 0 && hG < height && wG >= 0 && wG < width)
                        {
                            blueGy += image[hG][wG].rgbtBlue * 2;
                            greenGy += image[hG][wG].rgbtGreen * 2;
                            redGy += image[hG][wG].rgbtRed * 2;
                        }
                    }
                    else if (hG == h + 1 && wG == w + 1) //down right
                    {
                        if (hG >= 0 && hG < height && wG >= 0 && wG < width)
                        {
                            blueGx += image[hG][wG].rgbtBlue;
                            greenGx += image[hG][wG].rgbtGreen;
                            redGx += image[hG][wG].rgbtRed;
                            
                            blueGy += image[hG][wG].rgbtBlue;
                            greenGy += image[hG][wG].rgbtGreen;
                            redGy += image[hG][wG].rgbtRed;
                        }
                    }
                }
            }
            
            double blueSobel = pow(blueGx, 2) + pow(blueGy, 2);
            blueSobel = round(sqrt(blueSobel));
            if (blueSobel > 255)
            {
                blueSobel = 255;
            }
            
            double greenSobel = pow(greenGx, 2) + pow(greenGy, 2);
            greenSobel = round(sqrt(greenSobel));
            if (greenSobel > 255)
            {
                greenSobel = 255;
            }
            
            double redSobel = pow(redGx, 2) + pow(redGy, 2);
            redSobel = round(sqrt(redSobel));
            if (redSobel > 255)
            {
                redSobel = 255;
            }
            
            imageSobel[h][w].rgbtBlue = blueSobel;
            imageSobel[h][w].rgbtGreen = greenSobel;
            imageSobel[h][w].rgbtRed = redSobel;
        }
    }
    
    //Substitute Sobel pixels to original image
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w].rgbtBlue = imageSobel[h][w].rgbtBlue;
            image[h][w].rgbtGreen = imageSobel[h][w].rgbtGreen;
            image[h][w].rgbtRed = imageSobel[h][w].rgbtRed;
        }
    }
    
    return;
}
