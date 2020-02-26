#pragma once
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <omp.h>
#include <chrono>
#include <math.h>
#include <random>
using namespace std;
using namespace cv;
using namespace chrono;

void addSaltandPepper(Mat& tgt, double ratio);

Mat guidedBilateralFilter(Mat& GuideI, Mat& Src, Mat& Prev, int kernelSize, double sigSpatial, double sigGuideI, double noiseShapeAlpha = 1.0);

double calculateSEFderiv(double noiseScaleT, double noiseShapeAlpha);
double calculateSEF(double noiseScaleT, double noiseShapeAlpha);

double length(int x, int y, int x2, int y2);
double magnitude(double x, double y);

double calculateGaussian(double val, double sig, double div = 1);

double ImgSimilarity(int x, int y, int x2, int y2, Mat& GuideI, double sigSpatial, double sigGuideI);

double photometricNoiseModel(Mat& prev, Mat& src,  int x, int y, int x2, int y2, double Alpha);

double insideWindow(Mat& GuideI, Mat& Src, Mat& Prev,int x, int y, int kernelSize, double sigSpatial, double sigGuideI, double noiseShapeAlpha);

