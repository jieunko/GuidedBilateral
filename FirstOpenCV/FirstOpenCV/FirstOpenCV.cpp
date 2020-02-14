#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <omp.h>
#include <chrono>
using namespace std;
using namespace cv;
using namespace chrono;

class GridNode {
public:
	GridNode(int inten = 0, int c = 0) { intensity = inten; count = c; }

public:
	int intensity;
	int count;
};
class BilateralGrid 
{
public:
	int Intensity(int x, int y) { return SavedImage.at<uchar>(y, x); };
	void SetImage(Mat Image) { cvtColor(Image, SavedImage, COLOR_BGR2GRAY); };
	void FillGrid(int Spatial, int Range)
	{
		for (int i = 0; i < SavedImage.rows; i++) 
		{
			for (int j = 0; j < SavedImage.cols; j++)
			{
				int z = (int)(Intensity(i, j)/Range);
				Grid[i / Spatial][j / Spatial][z].intensity += Intensity(i, j);
				Grid[i / Spatial][j / Spatial][z].count += 1;
			}
		}
	};

	void GaussianConv(double SpatialSig, double RangeSig)
	{
	
	}
	
private:
	Mat SavedImage;
	GridNode Grid[332][332][256];

};

//void initialize(GridNode arr[][1000][256], int block_x, int block_y=0, int block_z=0)
//{
//
//   //#pragma omp parallel for 
//	for (int i = 0; i < block_x; i++)
//	{
//		
// 		for (int j = 0; j < block_y; j++) 
//		{ 
//		
//			for (int k = 0; k < block_z; k++) 
//			{
//				
//				arr[i][j][k].count = 0;
//				arr[i][j][k].intensity = 0;
//				
//			}
//		}
//	}
//
//}
//void filling(int grid[][1000][256], int Spatial, int Range)
//{
//
//   
//}

GridNode grid[332][332][256];
int main(int argc, char** argv) 
{
	
	Mat src;
	const int SpatialSamplingRate = 2;
	const int RangeSamplingRate = 2;
	BilateralGrid Bilateral;

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

	printf("%d", grid[0][12][12].count);
	
	waitKey(0);

	return 0;
}

