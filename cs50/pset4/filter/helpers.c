#include <math.h>
#include <string.h>

#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE r, g, b, avg;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            r = image[i][j].rgbtRed;
            g = image[i][j].rgbtGreen;
            b = image[i][j].rgbtBlue;

            avg = (BYTE) round((r + g + b) / 3.0);

            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
  
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE hold;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (int) floor(width / 2); j++)
        {
            hold = image[i][j];

            image[i][j] = image[i][width - 1 - j];

            image[i][width - 1 - j] = hold;
        }
    }
  
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE ref[height][width];
    memcpy(ref, image, sizeof(RGBTRIPLE) * height * width);

    float ravg, gavg, bavg;
    int npix;
  
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            ravg = 0;
            gavg = 0;
            bavg = 0;

            npix = 0;
      
            ravg += ref[i][j].rgbtRed;
            gavg += ref[i][j].rgbtGreen;
            bavg += ref[i][j].rgbtBlue;
            npix++;

            if (i != 0 && j != 0)
            {
                ravg += ref[i - 1][j - 1].rgbtRed;
                gavg += ref[i - 1][j - 1].rgbtGreen;
                bavg += ref[i - 1][j - 1].rgbtBlue;
                npix++;
            }
            if (i != 0 && j != width - 1)
            {
                ravg += ref[i - 1][j + 1].rgbtRed;
                gavg += ref[i - 1][j + 1].rgbtGreen;
                bavg += ref[i - 1][j + 1].rgbtBlue;
                npix++;
            }
            if (i != height - 1 && j != width - 1)
            {
                ravg += ref[i + 1][j + 1].rgbtRed;
                gavg += ref[i + 1][j + 1].rgbtGreen;
                bavg += ref[i + 1][j + 1].rgbtBlue;
                npix++;
            }
            if (i != height - 1 && j != 0)
            {
                ravg += ref[i + 1][j - 1].rgbtRed;
                gavg += ref[i + 1][j - 1].rgbtGreen;
                bavg += ref[i + 1][j - 1].rgbtBlue;
                npix++;
            }

            if (i != 0)
            {
                ravg += ref[i - 1][j].rgbtRed;
                gavg += ref[i - 1][j].rgbtGreen;
                bavg += ref[i - 1][j].rgbtBlue;
                npix++;
            }
            if (i != height - 1)
            {
                ravg += ref[i + 1][j].rgbtRed;
                gavg += ref[i + 1][j].rgbtGreen;
                bavg += ref[i + 1][j].rgbtBlue;
                npix++;
            }
            if (j != 0)
            {
                ravg += ref[i][j - 1].rgbtRed;
                gavg += ref[i][j - 1].rgbtGreen;
                bavg += ref[i][j - 1].rgbtBlue;
                npix++;
            }
            if (j != width - 1)
            {
                ravg += ref[i][j + 1].rgbtRed;
                gavg += ref[i][j + 1].rgbtGreen;
                bavg += ref[i][j + 1].rgbtBlue;
                npix++;
            }

            ravg /= npix;
            gavg /= npix;
            bavg /= npix;
      
            image[i][j].rgbtRed = (BYTE) round(ravg);
            image[i][j].rgbtGreen = (BYTE) round(gavg);
            image[i][j].rgbtBlue = (BYTE) round(bavg);
        }
    }
  
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE ref[height][width];
    memcpy(ref, image, sizeof(RGBTRIPLE) * height * width);

    float rGx, gGx, bGx;
    float rGy, gGy, bGy;

    int rfin, gfin, bfin;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            rGx = 0;
            gGx = 0;
            bGx = 0;

            rGy = 0;
            gGy = 0;
            bGy = 0;
      
            if (i != 0 && j != 0)
            {
                rGx += -ref[i - 1][j - 1].rgbtRed;
                gGx += -ref[i - 1][j - 1].rgbtGreen;
                bGx += -ref[i - 1][j - 1].rgbtBlue;

                rGy += -ref[i - 1][j - 1].rgbtRed;
                gGy += -ref[i - 1][j - 1].rgbtGreen;
                bGy += -ref[i - 1][j - 1].rgbtBlue;
            }
            if (i != 0 && j != width - 1)
            {
                rGx += ref[i - 1][j + 1].rgbtRed;
                gGx += ref[i - 1][j + 1].rgbtGreen;
                bGx += ref[i - 1][j + 1].rgbtBlue;
	
                rGy += -ref[i - 1][j + 1].rgbtRed;
                gGy += -ref[i - 1][j + 1].rgbtGreen;
                bGy += -ref[i - 1][j + 1].rgbtBlue;
            }
            if (i != height - 1 && j != width - 1)
            {
                rGx += ref[i + 1][j + 1].rgbtRed;
                gGx += ref[i + 1][j + 1].rgbtGreen;
                bGx += ref[i + 1][j + 1].rgbtBlue;
	
                rGy += ref[i + 1][j + 1].rgbtRed;
                gGy += ref[i + 1][j + 1].rgbtGreen;
                bGy += ref[i + 1][j + 1].rgbtBlue;
            }
            if (i != height - 1 && j != 0)
            {
                rGx += -ref[i + 1][j - 1].rgbtRed;
                gGx += -ref[i + 1][j - 1].rgbtGreen;
                bGx += -ref[i + 1][j - 1].rgbtBlue;
	
                rGy += ref[i + 1][j - 1].rgbtRed;
                gGy += ref[i + 1][j - 1].rgbtGreen;
                bGy += ref[i + 1][j - 1].rgbtBlue;
            }

            if (i != 0)
            {
                rGy += -2 * ref[i - 1][j].rgbtRed;
                gGy += -2 * ref[i - 1][j].rgbtGreen;
                bGy += -2 * ref[i - 1][j].rgbtBlue;
            }
            if (i != height - 1)
            {
                rGy += 2 * ref[i + 1][j].rgbtRed;
                gGy += 2 * ref[i + 1][j].rgbtGreen;
                bGy += 2 * ref[i + 1][j].rgbtBlue;
            }
            if (j != 0)
            {
                rGx += -2 * ref[i][j - 1].rgbtRed;
                gGx += -2 * ref[i][j - 1].rgbtGreen;
                bGx += -2 * ref[i][j - 1].rgbtBlue;
            }
            if (j != width - 1)
            {
                rGx += 2 * ref[i][j + 1].rgbtRed;
                gGx += 2 * ref[i][j + 1].rgbtGreen;
                bGx += 2 * ref[i][j + 1].rgbtBlue;
            }
      
            rfin = (int) round(sqrt(rGx * rGx + rGy * rGy));
            gfin = (int) round(sqrt(gGx * gGx + gGy * gGy));
            bfin = (int) round(sqrt(bGx * bGx + bGy * bGy));

            if (rfin > 255)
                rfin = 255;
            if (gfin > 255)
                gfin = 255;
            if (bfin > 255)
                bfin = 255;
      
            image[i][j].rgbtRed = (BYTE) rfin;
            image[i][j].rgbtGreen = (BYTE) gfin;
            image[i][j].rgbtBlue = (BYTE) bfin;
        }
    }
  
    return;
}
