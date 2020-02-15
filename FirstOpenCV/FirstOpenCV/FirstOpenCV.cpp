#include "main.h"

int main(int argc, char** argv) 
{
	
	Mat src;
	const int SpatialSamplingRate = 2;
	const int RangeSamplingRate = 2;


	system_clock::time_point start = system_clock::now();
	//initialize(grid, 1000, 1000, 256); //1242*375
	system_clock::time_point end = system_clock::now();
	duration<double, milli> sec = end - start;

	cout << sec.count() <<endl;
	src = cv::imread("grapefruit.jpg", IMREAD_COLOR);

	if (!src.data) 
	{
		src = cv::imread("testdata.png");
	}
	cv::imshow("showTest", src);
	//cout << src.at<double>(100, 100);

	
	waitKey(0);

	return 0;
}

