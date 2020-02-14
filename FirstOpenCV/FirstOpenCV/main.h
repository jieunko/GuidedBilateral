
#pragma once
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <omp.h>
#include <chrono>
#include "guidedBilateral.h"
using namespace std;
using namespace cv;
using namespace chrono;


void guidedBilateralFilter(Mat& src, int kernelSize, double sigSpatial, double sigGuideI);