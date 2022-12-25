#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/////////////////////// project 1 /////////////////

Mat img;

vector<vector<int>> myColors{ {73, 179, 0, 106, 78, 255}/*face mask*/};

vector<Scalar> myColorValues{ {0, 255, 0} };





/**
* @param imgDil Dilation img in
* @param img output img
*/
void getContours(Mat imgDil) {
	// for counters {{},{},{}}
	vector<vector<Point>> contours;

	// opencv has own detail for hierarchy
	vector<Vec4i> hierarchy;

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	// get conner of each shape
	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());


	// find and eliminate noise in the image
	for (int i = 0; i < contours.size(); i++) {

		double area = contourArea(contours[i]);
		cout << area << endl;

		string objType;

		// omit the noise
		if (area > 300) {
			double peri = arcLength(contours[i], true);
			// 轮廓近似
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

			// num of corners found
			cout << conPoly[i].size() << endl;

			// find bounding box around it
			boundRect[i] = boundingRect(conPoly[i]);

			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
		}
	}
}


/**
* @param img input img
*
* have an array of the color, contains max and min values
* of each colors. loop through and find img for that.
* Multiple mask (for different colors)
*
*/
void findColor(Mat img) {

	Mat imgHSV;

	// convert to HSV image
	cvtColor(img, imgHSV, COLOR_BGR2HSV);

	for (int i = 0; i < myColors.size(); i++) {
		Scalar lower(myColors[i][0], myColors[i][2], myColors[i][4]);
		Scalar upper(myColors[i][1], myColors[i][3], myColors[i][5]);

		Mat mask;

		// lower and upper is the range of color
		inRange(imgHSV, lower, upper, mask);

		// imshow(to_string(i), mask);

		// get contours and bounding box
		getContours(mask);

	}
}



/// <summary>
/// //////////////// webcam
/// </summary>

void main() {

	VideoCapture cap(0);
	Mat img;

	while (true) {

		cap.read(img);
		// find color
		findColor(img);

		imshow("Image", img);
		waitKey(1);
	}
}
