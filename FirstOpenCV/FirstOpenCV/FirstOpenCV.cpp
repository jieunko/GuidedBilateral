#include "main.h"

int main(int argc, char** argv) 
{
	
	Mat src;
	Mat Guide;
	Mat Prev;
	Mat result;

	system_clock::time_point start = system_clock::now();
	//initialize(grid, 1000, 1000, 256); //1242*375
	system_clock::time_point end = system_clock::now();
	duration<double, milli> sec = end - start;

	cout << sec.count() <<endl;
	src = cv::imread("grapefruit.jpg", IMREAD_GRAYSCALE);
	Guide = src.clone();
	Prev = src.clone();
	addSaltandPepper(src, 0.05);
	if (!src.data) 
	{
		src = cv::imread("testdata.png");
	}
	cv::imshow("showTest", src);
	//cout << src.at<double>(100, 100);
	for (int i = 0; i < 100; i++)
	{
		result = guidedBilateralFilter(Guide, src, Prev, 5, 1, 5);
		Prev = result.clone();
	}
	cv::imshow("Result", result);
	waitKey(0);

	return 0;
}

