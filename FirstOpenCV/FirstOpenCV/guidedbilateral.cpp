#include "guidedBilateral.h"

void addSaltandPepper(Mat& tgt, double ratio)
{
	int rows = tgt.rows;
	int cols = tgt.cols;
	int numPix = (int)((double)rows * cols) * ratio;
	for (int i = 0; i < numPix; i++)
	{
		int r = rand() % rows;
		int c = rand() % cols;
		uchar* pixel = tgt.ptr<uchar>(r) + c;
		*pixel = (rand() % 2 == 1) ? 255 : 0;
	}
}

Mat guidedBilateralFilter(Mat& GuideI, Mat& Src, Mat& Prev, int kernelSize, double sigSpatial, double sigGuideI, double noiseShapeAlpha)
{
	Mat ret = Src.clone();
	ret.setTo(Scalar::all(0));
	int m = kernelSize / 2;
	for (int i = m; i < Src.rows- m; i++)
	{
		for (int j = m; j < Src.cols - m; j++)
		{
			ret.at<uchar>(j, i) = (uchar)insideWindow(GuideI, Src, Prev, i, j, kernelSize, sigSpatial, sigGuideI, noiseShapeAlpha);
		}
	}
	return ret;
}

double calculateSEFderiv(double noiseScaleT, double noiseShapeAlpha) //estimated noise model
{
	return 1 / (2 * noiseShapeAlpha* noiseShapeAlpha) * (pow((1 + noiseScaleT), noiseShapeAlpha-1));
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
	double guided = calculateGaussian(GuideI.at<uchar>(y, x) - GuideI.at<uchar>(y2, x2), sigGuideI);
	return spatial * guided;
}

double insideWindow(Mat& GuideI, Mat& Src, Mat& Prev, int x, int y, int kernelSize, double sigSpatial, double sigGuideI, double noiseShapeAlpha)
{
	int m = kernelSize / 2;
	int x2 = 0;
	int y2 = 0;
	double sim = 0;
	double noiseModel = 0;
	double pix = 0;
	double divisor = 0;
	double dividend = 0;
	for (int i = 0; i < kernelSize; i++)
	{
		for (int j = 0; j < kernelSize; j++)
		{
			x2 = x - m + i;
			y2 = y - m + j;
			sim = ImgSimilarity(x, y, x2, y2, GuideI, sigSpatial, sigGuideI);
			noiseModel = photometricNoiseModel(Prev, Src, x, y, x2, y2, noiseShapeAlpha);
			pix = Src.at<uchar>(y2, x2);
			dividend += sim * noiseModel * pix;
			divisor += sim * noiseModel;
		}
	}
	return dividend / divisor;
}


double photometricNoiseModel(Mat& prev, Mat& src, int x, int y, int x2, int y2, double Alpha)
{
	
	double diff = prev.at<uchar>(y, x) - src.at<uchar>(y2, x2);
	return calculateSEFderiv(diff * diff, Alpha);

}



