/**
* preprocess the image, convert to gray, canny, and use edge detectors to 
* find edge. Find corners and warp them.
* 
*/

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/// //////////////// Images ///////////////////////

Mat img, imgGray, imgBlur, imgCanny, imgDilate, imgErode, imgThreshold, imgWarp, imgCrop;
vector<Point> initialPoint, docPoints;

float w = 420, h = 596;

Mat preprocessing (Mat img) 
{
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);// add blur
	Canny(imgBlur, imgCanny, 25, 75);// edge detection

	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));

	dilate(imgCanny, imgDilate, kernel);
	//erode(imgDilate, imgErode, kernel);

	return imgDilate;
}

/**
* find contours, area, approximation of poly
*
*/
vector<Point> getContours(Mat imgDil) {
	// for counters {{},{},{}}
	vector<vector<Point>> contours;

	// opencv has own detail for hierarchy
	vector<Vec4i> hierarchy;

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	// get conner of each shape
	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());

	vector<Point> biggest;
	int maxArea = 0;

	// find and eliminate noise in the image
	for (int i = 0; i < contours.size(); i++) {

		double area = contourArea(contours[i]);
		cout << area << endl;

		string objType;

		// omit the noise
		if (area > 1000) {
			double peri = arcLength(contours[i], true);
			// 轮廓近似
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

			if (area > maxArea && conPoly[i].size() == 4) {
				//drawContours(img, conPoly, i, Scalar(255, 0, 255), 5);
				biggest = { conPoly[i][0],conPoly[i][1],conPoly[i][2],conPoly[i][3] };
				maxArea = area;
			}

			//drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
			//rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
		}
	}

	return biggest;
}

void drawPoints(vector<Point> points, Scalar color)
{
	for (int i = 0; i < points.size(); i++) {
		circle(img, points[i], 10, color, FILLED);
		putText(img, to_string(i), points[i], FONT_HERSHEY_PLAIN, 2, color, 2);
	}
}

vector<Point> reorder(vector<Point> points) 
{
	vector<Point> newPoints;
	vector<int> sumPoints, subPoints;

	for (int i = 0; i < points.size(); i++) {
		sumPoints.push_back(points[i].x + points[i].y);
		subPoints.push_back(points[i].x - points[i].y);
	}

	newPoints.push_back(points[min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); // 0
	newPoints.push_back(points[max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]); // 1 sub min
	newPoints.push_back(points[min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]); // 2 sum max
	newPoints.push_back(points[max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); // 3 sub max

	return newPoints;

}

Mat getWarp(Mat img, vector<Point> points, float width, float height) 
{
	// Points to warp
	Point2f src[4] = { points[0], points[1], points[2], points[3]};
	// w and h is the size of the cards
	Point2f dst[4] = { {0.0f , 0.0f}, {w, 0.0f}, {0.0f, h}, {w, h} };

	// Transform matrix
	// warpPerspective method
	Mat matrix = getPerspectiveTransform(src, dst);
	warpPerspective(img, imgWarp, matrix, Point(w, h));

	return imgWarp;
}


void main() {
	string path = "paper.jpg";
	img = imread(path);

	resize(img, img, Size(), 0.5, 0.5);

	// preprocess
	imgThreshold = preprocessing(img);


	// get contours -- Biggest
	initialPoint = getContours(imgThreshold);
	//drawPoints(initialPoint, Scalar(0, 0, 255));
	docPoints = reorder(initialPoint);
	//drawPoints(docPoints, Scalar(255, 255, 0));

	//warp
	imgWarp = getWarp(img, docPoints, w, h);

	// Crop
	Rect roi(5, 5, w - (2 * 5), h - (2 * 5));
	imgCrop = imgWarp(roi);

	imshow("Image", img);
	//imshow("Image imgThreshold", imgThreshold);
	imshow("Image Warp", imgWarp);
	imshow("Image Crop", imgCrop);
	waitKey(0);
}
