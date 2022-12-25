#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/// <summary>
/// ///////////// color picker
/// </summary>

Mat imgHSV, mask;

// how to find these range, create a while loop to find them
int hmin = 0, smin = 0, vmin = 0;
int hmax = 179, smax = 255, vmax = 255;

VideoCapture cap(0);
Mat img;

void main() {

	namedWindow("TrackBars", (600, 400));
	createTrackbar("Hue Min", "TrackBars", &hmin, 179);
	createTrackbar("Hue Max", "TrackBars", &hmax, 179);
	createTrackbar("Sat Min", "TrackBars", &smin, 255);
	createTrackbar("Sat Max", "TrackBars", &smax, 255);
	createTrackbar("Val Min", "TrackBars", &vmin, 255);
	createTrackbar("Val Max", "TrackBars", &vmax, 255);

	while (true)
	{
		cap.read(img);

		// convert to HSV image
		cvtColor(img, imgHSV, COLOR_BGR2HSV);

		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);

		// lower and upper is the range of color
		inRange(imgHSV, lower, upper, mask);

		imshow("Image", img);
		//imshow("Image HSV", imgHSV);
		imshow("Image mask", mask);

		waitKey(1);
	}


}