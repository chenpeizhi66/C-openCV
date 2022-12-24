#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/// <summary>
/// /////////////Basic Functions of opencv
/// </summary>

void main() {
	string path = "test.png";
	Mat img = imread(path); // Mat: matrix data type
	Mat imgGray;
	Mat imgBlur;
	Mat imgCanny;
	Mat imgDilate, imgErode;


	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(7, 7), 5, 0);// add blur
	Canny(imgBlur, imgCanny, 25, 75);// edge detection

	Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5)); 
	// for dilation, increase Size will enlarge dialate.
	// Only can use odd num here 3x3, 5x5 blablabla
	
	dilate(imgCanny, imgDilate, kernel);
	erode(imgDilate, imgErode, kernel);

	imshow("Image", img);
	//imshow("Image Gray", imgGray);
	//imshow("Image Blur", imgBlur);
	imshow("Image Canny", imgCanny);
	imshow("Image Dilation", imgDilate);
	imshow("Image Erode", imgErode);
	// Firstly canny, then dilate, then erode
	waitKey(0);
}