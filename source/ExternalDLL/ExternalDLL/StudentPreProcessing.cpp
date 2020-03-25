#include "StudentPreProcessing.h"
#include "ImageFactory.h"
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

	for (size_t i = 0; i < size_t(image.getWidth() * image.getHeight()); i++)
	{
		Intensity targetPixel = image.getPixel(i);

		Intensity topLeftPixel = image.getPixel(i - image.getWidth() - 1);
		Intensity topCenterPixel = image.getPixel(i - image.getWidth());
		Intensity topRightPixel = image.getPixel(i - image.getWidth() + 1);

		Intensity middleLeftPixel = image.getPixel(i - 1);
		Intensity middleRightPixel = image.getPixel(i + 1);

		Intensity bottomLeftPixel = image.getPixel(i + image.getWidth() - 1);
		Intensity bottomCenterPixel = image.getPixel(i + image.getWidth());
		Intensity bottomRightPixel = image.getPixel(i + image.getWidth() + 1);

		gaussianResultImage->setPixel(i, (topLeftPixel	  * 2 + topCenterPixel    * 4 + topRightPixel	  * 2
										+ middleLeftPixel * 4 + targetPixel		  * 1  + middleRightPixel * 4
										+ bottomLeftPixel * 2 + bottomCenterPixel * 4  + bottomRightPixel * 2
										) / 25);
	}

	return gaussianResultImage;

	// Step 2 - Sobel Edge Detector

	// Step 3 - Non-Maximum Suppression
}

IntensityImage* StudentPreProcessing::stepThresholding(const IntensityImage& image) const {
	// Step 4 - Double Threshold
	IntensityImage* ResultImage = ImageFactory::newIntensityImage(image.getWidth(), image.getHeight());

	for (size_t i = 0; i < size_t(image.getWidth() * image.getHeight()); i++)
	{
		// Just copy image
		ResultImage->setPixel(i, image.getPixel(i));
	}
	// Step 5 - Hysteresis Thresholding

	return ResultImage;
}
