#include "StudentPreProcessing.h"

IntensityImage* StudentPreProcessing::stepToIntensityImage(const RGBImage& image) const {
	return nullptr;
}

IntensityImage* StudentPreProcessing::stepScaleImage(const IntensityImage& image) const {
	return nullptr;
}

IntensityImage* StudentPreProcessing::stepEdgeDetection(const IntensityImage& image) const {
	// Step 1 - Gaussian Blur

	// Step 2 - Sobel Edge Detector

	// Step 3 - Non-Maximum Suppression

	return nullptr;
}

IntensityImage* StudentPreProcessing::stepThresholding(const IntensityImage& image) const {
	// Step 4 - Dobule Threshold

	// Step 5 - Hysteresis Thresholding

	return nullptr;
}
