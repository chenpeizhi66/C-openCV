#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/// <summary>
/// //////////////// Images
/// </summary>

//void main() {
//	string path = "test.png";
//	Mat img = imread(path); // Mat: matrix data type 
//	imshow("Image", img);
//	waitKey(0);
//}

/// <summary>
/// //////////////// video
/// </summary>

//void main() {
//	string path = "test_video.mp4";
//	VideoCapture cap(path);
//	Mat img;
//
//	while (true) {
//		
//		cap.read(img);
//		
//		imshow("Image", img);
//		waitKey(1);
//	}
//}

/// <summary>
/// //////////////// webcam
/// </summary>

void main() {
	
	VideoCapture cap(0); // camera id 0 if only has one camera
	Mat img;

	while (true) {

		cap.read(img);

		imshow("Image", img);
		waitKey(1);
	}
}
