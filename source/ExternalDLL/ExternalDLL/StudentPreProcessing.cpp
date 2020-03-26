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
	sobelEdgeDetector(*edgeDetectResultImage, *sobelOutput);

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
	constexpr int kernel[] = { 1, 2, 1,
							 2, 4, 2,
							 1, 2, 1 };

	convolution(image, output, kernel);
}

void StudentPreProcessing::sobelEdgeDetector(const IntensityImage& image, IntensityImage& output) const
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

	for (size_t i = 0; i < image.getWidth() * image.getHeight(); i++)
	{
		int sobelPixel = sqrt(pow(xFilterOutput->getPixel(i), 2) + pow(yFilterOutput->getPixel(i), 2));
		output.setPixel(i, std::min(sobelPixel, 255));
	}
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
