#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <opencv2/objdetect.hpp>

#include <iostream>

using namespace cv;
using namespace std;

/// <summary>
/// //////////////// face detection
/// </summary>

void main() {

	string path = "test.png";
	Mat img = imread(path);

	CascadeClassifier faceCascade;
	faceCascade.load("haarcascade_frontalface_default.xml");

	if (faceCascade.empty()) {
		cout << "XML file not loaded" << endl;
	}

	// detect faces and store, using bounding box
	vector<Rect>  faces;
	faceCascade.detectMultiScale(img, faces, 1.1, 10);

	for (int i = 0; i < faces.size(); i++) {
		rectangle(img, faces[i].tl(), faces[i].br(), Scalar(0, 255, 0), 3);
	}


	imshow("Image", img);
	waitKey(0);
}
