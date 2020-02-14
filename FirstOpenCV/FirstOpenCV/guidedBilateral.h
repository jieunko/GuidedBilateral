#pragma once
#include "main.h"
#include <math.h>
void guidedBilateralFilter(Mat& src, int kernelSize, double sigSpatial, double sigGuideI);

double calculateSEF(double noiseScaleT, double noiseShapeAlpha)
{
	return 1 / (2 * noiseShapeAlpha) * (pow((1 + noiseScaleT), noiseShapeAlpha) - 1);
};
