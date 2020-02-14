#pragma once
#include "main.h"
#include <math.h>
void guidedBilateralFilter(Mat& GuideI, Mat& Src, Mat& Prev, int kernelSize, double sigSpatial, double sigGuideI);

double calculateSEF(double noiseScaleT, double noiseShapeAlpha)
{
	return 1 / (2 * noiseShapeAlpha) * (pow((1 + noiseScaleT), noiseShapeAlpha) - 1);
};

double length(int x, int y, int x2, int y2)
{
	return sqrt(pow((x - x2), 2) + pow((y - y2), 2));

}

double calculateGaussian(double val, double sig)
{
	return exp(-(pow(val, 2)) / (2 * pow(sig, 2))) / (2 * CV_PI * pow(sig, 2));
}

double photometricNoiseModel(int x, int y, int x2, int y2, Mat& GuideI, double sigSpatial, double sigGuideI)
{
	double spatial = calculateGaussian(length(x, y, x2, y2), sigSpatial);
	double guided = calculateGaussian(GuideI.at<uchar>(x, y) - GuideI.at<uchar>(x, y), sigGuideI);
	return spatial * guided;
}