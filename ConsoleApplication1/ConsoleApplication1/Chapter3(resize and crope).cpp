#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/// <summary>
/// ///////////// Resize & Crop
/// </summary>

void main() {
	string path = "test.png";
	Mat img = imread(path); // Mat: matrix data type
	Mat imgResize, imgCrop;

	//cout << img.size() << endl; //size is 768x559

	resize(img, imgResize, Size(600, 600), 0.5, 0.5);

	Rect roi(100, 100, 300, 250);
	imgCrop = img(roi);

	imshow("Image", img);
	imshow("Image Resize", imgResize);
	imshow("Image Crope", imgCrop);
	
	waitKey(0);
}