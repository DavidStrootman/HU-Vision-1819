#include "StudentPreProcessing.h"

#include <algorithm>
#include <math.h>
#include <stdlib.h>

#include "ImageFactory.h"

IntensityImage* StudentPreProcessing::stepToIntensityImage(const RGBImage& image) const {
	return nullptr;
}

IntensityImage* StudentPreProcessing::stepScaleImage(const IntensityImage& image) const {
	return nullptr;
}

IntensityImage* StudentPreProcessing::stepEdgeDetection(const IntensityImage& image) const {
	// Step 1 - Gaussian Blur (3x3)
	IntensityImage* edgeDetectResultImage = ImageFactory::newIntensityImage(image.getWidth(), image.getHeight());
	gaussianBlur(image, *edgeDetectResultImage);

	// Step 2 - Sobel Edge Detector
	IntensityImage* sobelOutput = ImageFactory::newIntensityImage(image.getWidth(), image.getHeight());
	int* sobelAngles{ new int[image.getWidth() * image.getHeight()]() };
	sobelEdgeDetector(*edgeDetectResultImage, *sobelOutput, sobelAngles);

	// Step 3 - Non-Maximum Suppression
	return sobelOutput;
}

IntensityImage* StudentPreProcessing::stepThresholding(const IntensityImage& image) const {
	// Step 4 - Double Threshold

	// Step 5 - Hysteresis Thresholding

	// Return copy of image, just for testing.

	IntensityImage* imgCopy = ImageFactory::newIntensityImage(image.getWidth(), image.getHeight());

	for (size_t i = 0; i < size_t(image.getWidth() * image.getHeight()); i++)
	{
		imgCopy->setPixel(i, image.getPixel(i));
	}
	
	return imgCopy;
}

void StudentPreProcessing::gaussianBlur(const IntensityImage& image, IntensityImage& output) const
{
	// Hard coded 3x3 gaussian
	constexpr int kernel[] = { 1, 2, 1,
							   2, 4, 2,
							   1, 2, 1 };

	convolution(image, output, kernel);
}

void StudentPreProcessing::sobelEdgeDetector(const IntensityImage& image, IntensityImage& output, int* angleOutput) const
{

	constexpr int xFilter[] = { -1, 0, 1,
							    -2, 0, 2,
							    -1, 0, 1 };

	constexpr int yFilter[] = { -1,-2,-1,
								 0, 0, 0,
								 1, 2, 1 };

	IntensityImage* xFilterOutput = ImageFactory::newIntensityImage(image.getWidth(), image.getHeight());
	IntensityImage* yFilterOutput = ImageFactory::newIntensityImage(image.getWidth(), image.getHeight());

	convolution(image, *xFilterOutput, xFilter);
	convolution(image, *yFilterOutput, yFilter);

	for (int i = 0; i < image.getWidth() * image.getHeight(); i++)
	{
		int xFilterPixel = xFilterOutput->getPixel(i);
		int yFilterPixel = yFilterOutput->getPixel(i);

		int sobelPixel = sqrt(pow(xFilterPixel, 2) + pow(yFilterPixel, 2));

		// Possibly TODO: try scaling instead of clamping
		output.setPixel(i, std::max(0, std::min(sobelPixel, 255)));

		int sobelDir = abs(int(atan2(yFilterPixel, xFilterPixel)) % 180);
		
		if (sobelDir > 157)
		{
			angleOutput[i] = 0;
		}
		else if (sobelDir > 112)
		{
			angleOutput[i] = 135;
		}
		else if (sobelDir > 67)
		{
			angleOutput[i] = 90;
		}
		else if (sobelDir > 22)
		{
			angleOutput[i] = 45;
		}
		else
		{
			angleOutput[i] = 0;
		}
	}
}

void StudentPreProcessing::nonMaximumSuppression(const IntensityImage& image, int* edgeAngles, IntensityImage& output) const
{
	// Edge strenght == Edge gradient value
	// 1. Compare the edge strength of the current pixel with the edge strength of the pixel in the positive and negative gradient directions.

	// 2. If the edge strength of the current pixel is the largest compared to the other pixels in the mask with the same direction
	// (e.g., a pixel that is pointing in the y - direction will be compared to the pixel above and below it in the vertical axis),
	// the value will be preserved.Otherwise, the value will be suppressed.
}

void StudentPreProcessing::convolution(const IntensityImage& image, IntensityImage& output, const int* kernel, int kernelSize) const
{
	int kernelTotal = 0;
	for (int i = 0; i < kernelSize; i++) {
		kernelTotal += abs(kernel[i]);
	}

	// TODO: Optimize this to only copy the outer edge.
	for (int i = 0; i < image.getWidth() * image.getHeight(); i++)
	{
		output.setPixel(i, image.getPixel(i));
	}

	for (int y = 1; y < image.getHeight(); y++)
	{
		for (int x = 1; x < image.getWidth(); x++)
		{
			int topLeftPixel = image.getPixel(x-1, y-1) * kernel[0];
			int topCenterPixel = image.getPixel(x, y-1) * kernel[1];
			int topRightPixel = image.getPixel(x+1,y-1) * kernel[2];

			int middleLeftPixel = image.getPixel(x-1, y) * kernel[3];
			int middleCenterPixel = image.getPixel(x, y) * kernel[4];
			int middleRightPixel = image.getPixel(x+1,y) * kernel[5];

			int bottomLeftPixel = image.getPixel(x- 1,y+1) * kernel[6];
			int bottomCenterPixel = image.getPixel(x, y+1) * kernel[7];
			int bottomRightPixel = image.getPixel(x+1, y+1) * kernel[8];

			int newValue = topLeftPixel + topCenterPixel + topRightPixel + middleLeftPixel + middleCenterPixel + middleRightPixel + bottomLeftPixel + bottomCenterPixel + bottomRightPixel;
			output.setPixel(x, y, newValue / kernelTotal);
		}
	}
}
