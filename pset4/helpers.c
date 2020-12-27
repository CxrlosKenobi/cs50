#include "helpers.h"
#include <math.h>
#include <cs50.h>


// Convert image to grayscale
												//Height = Altura
												//Width = Anchura
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
	float AvPV; //Average Pixel Value
	for(int i = 0; i < width; i++) //Iterate one row at a time
	{
		for(int j = 0; j < height; j++) //Iterate one pixel at a time
		{
		//Calculate the average pixel value (through RGB) for each pixel
			AvPV = round((image[j][i].rgbtBlue + image[j][i].rgbtGreen + image[j][i].rgbtRed) / 3.000);						//Set each color value to the average value (round it to the nearest integer)
		//Set each color value to the average value (round it to the nearest integer)
			image[j][i].rgbtRed = AvPV;
			image[j][i].rgbtGreen = AvPV;
			image[j][i].rgbtBlue = AvPV;
		}
	}
}


// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
	int GlOW[3]; //Temp variable that gonna help for the swap "Glass Of Water"
	for(int j = 0; j < height; j++)
	{
		for(int i = 0; i < width / 2; i++)
		{//Swap pixels on horizontally opposite ideas
				GlOW[0] = image[j][i].rgbtRed;
				GlOW[1] = image[j][i].rgbtGreen;
				GlOW[2] = image[j][i].rgbtBlue;

				image[j][i].rgbtRed = image[j][width - i - 1].rgbtRed;
				image[j][i].rgbtGreen = image[j][width - i - 1].rgbtGreen;
				image[j][i].rgbtBlue = image[j][width - i - 1].rgbtBlue;

				image[j][width - i - 1].rgbtRed = GlOW[0];
				image[j][width - i - 1].rgbtGreen = GlOW[1];
				image[j][width - i - 1].rgbtBlue = GlOW[2];
		}
	}
	return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
	int AverageR;
	int AverageG;
	int AverageB;
	float counter;
//Create a temporary table of colors to not alter the calculations
	RGBTRIPLE GlOW[height][width];

	for(int i = 0; i < width; i++)
	{
		for(int j = 0; j < height; j++)
		{
			AverageR = 0;
			AverageG = 0;
			AverageB = 0;
			counter = 0.00;

    //Sums values of the pixel and neighboring ones, skips iteration if it goes outside the pic
			for(int k = -1; k < 2; k++)
			{
				if(j + k < 0 || j + k > height - 1)
				{
					continue;
				}

				for(int h = -1; h < 2; h++)
				{
					if(i + h < 0 || i + h > width - 1)
					{
						continue;
					}
					AverageR += image[j + k][i + h].rgbtRed;
					AverageG += image[j + k][i + h].rgbtGreen;
					AverageB += image[j + k][i + h].rgbtBlue;
					counter++;
				}
			}
	//Averages the sum to make picture look blurrier
		GlOW[j][i].rgbtRed = round(AverageR / counter);
		GlOW[j][i].rgbtGreen = round(AverageG / counter);
		GlOW[j][i].rgbtBlue = round(AverageB / counter);
		}
	}
//Copies values from temporary table
	for(int i = 0; i < width; i++)
	{
		for(int j = 0; j < height; j++)
		{
			image[j][i].rgbtRed = GlOW[j][i].rgbtRed;
			image[j][i].rgbtGreen = GlOW[j][i].rgbtGreen;
			image[j][i].rgbtBlue = GlOW[j][i].rgbtBlue;
		}
	}
    return;
}

bool isValidPixel(int i, int j, int height, int width)
{
	return i >= 0 && i < height && j >= 0 && j < width;
}

int cap(int value)
{
	return value < 255 ? value : 255;
}

RGBTRIPLE getEdgedPixel(int i, int j, int height, int width, RGBTRIPLE image[height][width])
{
	int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
	int GxRed = 0; 		int GyRed = 0;
	int GxGreen = 0;	int GyGreen = 0;
	int GxBlue = 0; 	int GyBlue = 0;
	for(int k = -1; k <= 1; k++)
	{
		for(int l = -1; l <= 1; l++)
		{
			if(isValidPixel(i + k, j + l, height, width))
			{
		    //Calculating Gx and Gy
		    	int weightx = Gx[k+1][l+1];
				GxRed += weightx * image[i+k][j+l].rgbtRed;
				GxGreen += weightx * image[i+k][j+l].rgbtGreen;
				GxBlue += weightx* image[i+k][j+l].rgbtBlue;

		    	int weighty = Gx[l+1][k+1];
				GyRed += weighty * image[i+k][j+l].rgbtRed;
				GyGreen += weighty * image[i+k][j+l].rgbtGreen;
				GyBlue += weighty * image[i+k][j+l].rgbtBlue;
			}
		}
	}
	RGBTRIPLE pixel;
	pixel.rgbtRed = cap(round(sqrt(GxRed*GxRed + GyRed*GyRed)));
	pixel.rgbtGreen = cap(round(sqrt(GxGreen*GxGreen + GyGreen*GyGreen)));
	pixel.rgbtBlue = cap(round(sqrt(GxBlue*GxBlue + GyBlue*GyBlue)));
	return pixel;
}

//Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
	RGBTRIPLE GlOW[height][width];
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			GlOW[i][j] = getEdgedPixel(i, j, height, width, image);
		}
	}
	for(int i = 0; i < height; i++)
		for(int j = 0; j < width; j++)
			image[i][j] = GlOW[i][j];
    return;
}
