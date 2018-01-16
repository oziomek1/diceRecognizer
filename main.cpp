#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

cv::Mat img_gray;
cv::Mat img_canny;
int threshold;
int max_threshold = 200;
std::string nameOfAWindow = "Canny";

void cannyThreshold(int, void*) {

    cv::blur(img_gray, img_canny, cv::Size(3, 3));
    Canny(img_canny, img_canny, threshold, threshold*5, 3, false);

    cv::imshow(nameOfAWindow, img_canny);
}

int main(int argc, char ** argv) {

    cv::Mat image;
    image = cv::imread("IMAG1442.jpg", 1);

    if (image.empty()) {
        std::cerr << "Cound not open image" << std::endl;
        return -1;
    }


    cv::resize(image, image, cv::Size(), 0.25, 0.25, cv::INTER_AREA);
    cv::cvtColor(image, img_gray, CV_BGR2GRAY);

    cv::namedWindow(nameOfAWindow, CV_WINDOW_AUTOSIZE);

    cv::createTrackbar("Threshold", nameOfAWindow, &threshold, max_threshold, cannyThreshold);

    cannyThreshold(0, 0);

    cv::namedWindow("Actual mask", CV_WINDOW_AUTOSIZE);
    cv::Mat img_gray2 = img_gray;
    cv::Mat img_canny2;
    cv::blur(img_gray2, img_canny2, cv::Size(3, 3));
    Canny(img_canny2, img_canny2, 18, 90, 3, false);
    cv::imshow("mask", img_canny2);
    cv::imwrite("output.jpg", img_canny2);

//    cv::Mat ocv = image;
//    cv::Mat image_gray_3;
//    cv::cvtColor(image, image_gray_3, cv::COLOR_BGR2GRAY);
//    cv::threshold(image_gray_3, image_gray_3, 20, 255, 1);
//
//    std::vector<std::vector<cv::Point>> contours;
//    cv::findContours(image_gray_3, contours, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);
//
//    std::vector<cv::Rect> rects;
//    for (int i = 0; i < contours.size(); i++) {
//        double area = cv::contourArea(contours[i]);
//        if (area < 50000) {
//            cv::drawContours(image, contours, i, cv::Scalar(200,0,0));
//            cv::Rect rect = cv::boundingRect(contours[i]);
//            rects.push_back(rect);
//        }
//    }
//    cv::namedWindow("Rects", CV_WINDOW_AUTOSIZE);
//    cv::imshow("rect", rects);

    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
}