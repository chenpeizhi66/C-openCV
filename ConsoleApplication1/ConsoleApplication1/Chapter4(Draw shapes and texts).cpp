#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/// <summary>
/// ///////////// Draw shapes and text
/// </summary>

void main() {
	// create a blank img
	Mat img(512, 512, CV_8UC3, Scalar(255, 0 ,0));// blue because BGR

	// Scalar() is for color
	// Draw circle
	circle(img, Point(256, 256), 155, Scalar(255, 0, 255), FILLED);
	
	// Draw rectangular
	rectangle(img, Point(100, 100), Point(300, 300), Scalar(0, 255, 0), FILLED);

	// Draw line
	line(img, Point(500, 100), Point(500, 400), Scalar(255, 255, 255));

	// put text
	putText(img, "Basic Shape from scratch", Point(100, 300), FONT_HERSHEY_DUPLEX, 0.8, Scalar(255, 255, 255), 0.5);


	imshow("Image", img);

	waitKey(0);
}