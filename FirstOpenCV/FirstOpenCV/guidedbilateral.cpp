#include "guidedBilateral.h"

void guidedBilateralFilter(Mat& GuideI, Mat& Src, Mat& Prev, int kernelSize, double sigSpatial, double sigGuideI)
{
	SEFMap.copySize(Src);
	SEFMap.setTo(Scalar::all(0));
}

double calculateSEF(double noiseScaleT, double noiseShapeAlpha) //estimated noise model
{
	return 1 / (2 * noiseShapeAlpha) * (pow((1 + noiseScaleT), noiseShapeAlpha) - 1);
};

double length(int x, int y, int x2, int y2)
{
	return sqrt(pow((x - x2), 2) + pow((y - y2), 2));

}

double magnitude(double x, double y)
{
	return sqrt(pow(x, 2) + pow(y, 2));
}

double calculateGaussian(double val, double sig)
{
	return exp(-(pow(val, 2)) / (2 * pow(sig, 2))) / (2 * CV_PI * pow(sig, 2));
}

double ImgSimilarity(int x, int y, int x2, int y2, Mat& GuideI, double sigSpatial, double sigGuideI)
{
	double spatial = calculateGaussian(length(x, y, x2, y2), sigSpatial);
	double guided = calculateGaussian(GuideI.at<uchar>(y, x) - GuideI.at<uchar>(y, x), sigGuideI);
	return spatial * guided;
}

double firstOrderDeriv(int x, int y,  Mat& Img)//http://www.me.umn.edu/courses/me5286/vision/VisionNotes/2017/ME5286-Lecture7-2017-EdgeDetection2.pdf
{
	double a[8] = { 0.0, };
	a[0] = Img.at<uchar>(y - 1, x - 1);
	a[1] = Img.at<uchar>(y - 1, x);
    a[2] = Img.at<uchar>(y - 1, x + 1);
	a[3] = Img.at<uchar>(y, x + 1);
	a[4] = Img.at<uchar>(y+1, x + 1);
	a[5] = Img.at<uchar>(y +1, x );
	a[6] = Img.at<uchar>(y + 1, x - 1);
	a[7] = Img.at<uchar>(y , x-1);

	double derivX = a[2] + a[3] + a[4] - (a[0] + a[7] + a[6]);
	double derivY = a[6] + a[5] + a[4] - (a[0] + a[1] + a[2]);
	return 0.0;
}

double photometricNoiseModel(Mat& prev, Mat& src)
{
	return 0.0;
}

void ImgDiff(Mat& prev, Mat& src, int kernelSize, int x, int y)
{
	SEFMap.c
	int m = kernelSize / 2;
	int x2 = 0;
	int y2 = 0;
	double diff = 0;
	double E = 0;
	for (int i = 0; i < kernelSize; i++)
	{
		for (int j = 0; j < kernelSize; j++) 
		{
			x2 = x - m + i;
			y2 = y - m  + j;
			diff = prev.at<uchar>(y, x)- src.at<uchar>(y2, x2);
			SEFMap.at<double>(y,x) += diff* diff;
		}
	}


}

