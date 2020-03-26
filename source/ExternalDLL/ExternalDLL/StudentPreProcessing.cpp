#include "StudentPreProcessing.h"
#include "ImageFactory.h"

IntensityImage* StudentPreProcessing::stepToIntensityImage(const RGBImage& image) const {
	return nullptr;
}

IntensityImage* StudentPreProcessing::stepScaleImage(const IntensityImage& image) const {
	return nullptr;
}

IntensityImage* StudentPreProcessing::stepEdgeDetection(const IntensityImage& image) const {
	//////	
	// Step 1 - Gaussian Blur (3x3)
	//////

	IntensityImage* gaussianResultImage = ImageFactory::newIntensityImage(image.getWidth(), image.getHeight());
	gaussianBlur(image, *gaussianResultImage);
	return gaussianResultImage;

	// Step 2 - Sobel Edge Detector

	// Step 3 - Non-Maximum Suppression
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
	constexpr int data[] = { 1,2,1, 2,4,2, 1,2,1 };
	convolution(image, output, data);
}

void StudentPreProcessing::convolution(const IntensityImage& image, IntensityImage& output, const int* kernel, int kernelSize) const
{
	int kernelTotal = 0;
	for (int i = 0; i < kernelSize; i++) {
		kernelTotal += kernel[i];
	}

	// TODO: Bounds checking
	for (int i = 0; i < image.getWidth() * image.getHeight(); i++)
	{
		int topLeftPixel = image.getPixel(i - image.getWidth() - 1) * kernel[0];
		int topCenterPixel = image.getPixel(i - image.getWidth()) * kernel[1];
		int topRightPixel = image.getPixel(i - image.getWidth() + 1) * kernel[2];

		int middleLeftPixel = image.getPixel(i - 1) * kernel[3];
		int middleCenterPixel = image.getPixel(i) * kernel[4];
		int middleRightPixel = image.getPixel(i + 1) * kernel[5];

		int bottomLeftPixel = image.getPixel(i + image.getWidth() - 1) * kernel[6];
		int bottomCenterPixel = image.getPixel(i + image.getWidth()) * kernel[7];
		int bottomRightPixel = image.getPixel(i + image.getWidth() + 1) * kernel[8];

		int newValue = topLeftPixel + topCenterPixel + topRightPixel + middleLeftPixel + middleCenterPixel + middleRightPixel + bottomLeftPixel + bottomCenterPixel + bottomRightPixel;
		output.setPixel(i, newValue / kernelTotal);
	}
}
