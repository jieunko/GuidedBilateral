#pragma once
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <omp.h>
#include <chrono>
#include <math.h>
using namespace std;
using namespace cv;
using namespace chrono;

void guidedBilateralFilter(Mat& GuideI, Mat& Src, Mat& Prev, int kernelSize, double sigSpatial, double sigGuideI);

double calculateSEF(double noiseScaleT, double noiseShapeAlpha);


double magnitude(int x, int y, int x2, int y2);

double calculateGaussian(double val, double sig);

double photometricNoiseModel(int x, int y, int x2, int y2, Mat& GuideI, double sigSpatial, double sigGuideI);
double firstOrderDeriv(int x, int y, int x2, int y2, Mat& Img);
