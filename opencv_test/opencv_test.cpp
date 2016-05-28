// opencv_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <opencv2/opencv.hpp>
#include <opencv\highgui.h>

using namespace cv;

void trackbarHandler(int pos, void* slider_value) {
	*((int*)slider_value) = pos;
}

void initVideoStream(cv::VideoCapture &cap) {
	if (cap.isOpened())
		cap.release();
	cap.open(0);//open the default camera
		if (cap.isOpened() == false) {
			std::cout << "No webcam is found, using a video file" << std::endl;
			cap.open("MarkerMovie.mpg");
			if (cap.isOpened() == false) {
				std::cout << "No video file found.Exiting" << std::endl;
				exit(0);
			}

		}
}

void exercise1() {
	cv::VideoCapture cap;
	const std::string KWinName1 = "Exercise1 -Original Image";
	const std::string KWinName2 = "Exercise1-Threshold Image";

	std::cout << "startup (Press ESC to quit)" << std::endl;
	cv::namedWindow(KWinName1, CV_WINDOW_AUTOSIZE);
	cv::namedWindow(KWinName2, CV_WINDOW_NORMAL);
	initVideoStream(cap);

	int slider_value = 100;
	cv::createTrackbar("Threshold", "Exercise 1=Threshold Image", &slider_value, 255, trackbarHandler, &slider_value);
	cv::Mat img_bgr;
	cv::Mat img_gray;
	cv::Mat img_filtered;

	while (1) {
		cap >> img_bgr;
		if (img_bgr.empty()) {
			printf("Could not query frame. Trying to initialize. \n");
			initVideoStream(cap);
			cv::waitKey(1000);
			continue;
		}
		cv::cvtColor(img_bgr, img_gray, CV_BGR2GRAY);
		cv::threshold(img_gray, img_filtered, slider_value, 255, CV_THRESH_BINARY);
		//cvAdaptiveThreshold(iplConverted, iplThreshold, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 33, 5);

		cv::imshow(KWinName1, img_bgr);
		cv::imshow(KWinName2, img_filtered);

		int key = cv::waitKey(10);
		if (key == 27) break;
	}
	cv::destroyWindow(KWinName1);
	cv::destroyWindow(KWinName2);
	std::cout << "Finished \n";

}
void exercise2() {
	cv::VideoCapture cap;
	std::cout << "Startup \n";
	const std::string kWinName1 = "Exercise 2 - Original Image";
	const std::string kWinname2 = "Exercise 2 - Converted Image";
	cv::namedWindow(kWinName1, CV_WINDOW_AUTOSIZE);
	cv::namedWindow(kWinname2, CV_WINDOW_NORMAL);
	initVideoStream(cap);

	int slider_value = 100;
	cv::createTrackbar("Threshold", "Exercise 2 - Converted Image", &slider_value, 255, trackbarHandler, &slider_value);
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Point> rect;
	CvMemStorage* memStorage = cvCreateMemStorage();

	cv::Mat img_bgr;
	cv::Mat img_gray;
	cv::Mat img_mono;

	while (1) {
		cap >> img_bgr;
		if (img_bgr.empty()) {
			std::cout << "Could not query frame. Trying to reinitialize." << std::endl;
			initVideoStream(cap);
			cv::waitKey(1000); //wait for one sec
			continue;
		}
	}
}

int main(int ac, char** av) {
	exercise1();
}


