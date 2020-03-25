/*
* Copyright (c) 2015 DottedEye Designs, Alexander Hustinx, NeoTech Software, Rolf Smit - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*/

#pragma once

#include "PreProcessing.h"
#include "ImageFactory.h"

constexpr int CANNY_GUASSIAN_BLUR_RADIUS = 0;
constexpr float CANNY_LOW_THRESHOLD = 0.0f;
constexpr float CANNY_HIGH_THRESHOLD = 0.0f;

class StudentPreProcessing : public PreProcessing {
public:
	IntensityImage* stepToIntensityImage(const RGBImage& image) const;
	IntensityImage* stepScaleImage(const IntensityImage& image) const;
	IntensityImage* stepEdgeDetection(const IntensityImage& image) const;
	IntensityImage* stepThresholding(const IntensityImage& image) const;
};
