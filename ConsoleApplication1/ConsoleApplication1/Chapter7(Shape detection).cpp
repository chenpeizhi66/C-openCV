#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/// <summary>
/// ///////////// shape detection
/// </summary>

Mat imgGray, imgBlur, imgCanny, imgDil;



/**
* @param imgDil Dilation img in
* @param img output img
*/
void getContours(Mat imgDil, Mat img) {
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
		// find area, we find the noise's area is 185.5
		double area = contourArea(contours[i]);
		cout << area << endl;

		string objType;
		
		// omit the noise
		if (area > 1000) {
			double peri = arcLength(contours[i], true);
			// 轮廓近似
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			// drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
		 
			// num of corners found
			cout << conPoly[i].size() << endl;

			// find bounding box around it
			boundRect[i] = boundingRect(conPoly[i]);
			//rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
		
			//putText(img, objType, { boundRect[i].x, boundRect[i].y - 5 }, FONT_HERSHEY_DUPLEX, 0.8, Scalar(0, 69, 255), 2);

			int objColor = (int)conPoly[i].size();

			if (objColor == 3) {
				objType = "Triangle";
			}
			if (objColor == 4) {

				// if square
				float aspRation = (float)boundRect[i].width / (float)boundRect[i].height;

				if (aspRation > 1.1 || aspRation < 0.9) {
					objType = "Rectangle";
				}
				else {
					objType = "Square";
				}
			}
			if (objColor > 4) {
				objType = "Circle";
			}
			
			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
			putText(img, objType, { boundRect[i].x, boundRect[i].y - 5 }, FONT_HERSHEY_PLAIN, 1, Scalar(0, 69, 255), 1);
		}
	}

}


void main() {
	// Firstly use canny find the edges then find countour points
	string path = "shapes.png";
	Mat img = imread(path);
	
	// Preprocessing image
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernel);

	getContours(imgDil, img);

	imshow("Image", img);
	/*imshow("Image Gray", imgGray);
	imshow("Image Blur", imgBlur);
	imshow("Image Canny", imgCanny);
	imshow("Image Dilation", imgDil);*/
	waitKey(0);
}