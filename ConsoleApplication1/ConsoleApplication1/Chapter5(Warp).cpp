#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/// <summary>
/// ///////////// Warp image
/// </summary>

void main() {

	float w = 250, h = 350;
	Mat matrix, imgWarp;

	string path = "cards.jpg";
	Mat img = imread(path);

	// Points to warp
	Point2f src[4] = { {529, 142}, {771, 190}, {405, 395}, {674, 457} };
	// w and h is the size of the cards
	Point2f dst[4] = { {0.0f , 0.0f}, {w, 0.0f}, {0.0f, h}, {w, h} };

	// Transform matrix
	// warpPerspective method
	matrix = getPerspectiveTransform(src, dst);
	warpPerspective(img, imgWarp, matrix, Point(w, h));

	// draw circle around the boundary
	for (int i = 0; i < 4; i++) {
		circle(img, src[i], 10, Scalar(0, 0, 255), FILLED);
	}

	imshow("Image", img);
	imshow("Image Warp", imgWarp);

	waitKey(0);
}