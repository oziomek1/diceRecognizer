#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/objdetect.hpp"

int main(int argc, char ** argv) {

    std::string windowName = "DiceRecognizer";
    cv::namedWindow(windowName, CV_WINDOW_AUTOSIZE);

    cv::VideoCapture cap(1);
    cv::Mat backgroundFrame;
    cap >> backgroundFrame;

    cvtColor(backgroundFrame, backgroundFrame, CV_BGR2GRAY);

    cv::Mat originalFrame;
    while (1) {
        cap >> originalFrame;
        std::ostringstream rectangleText;
        cv::Mat processedFrame;
        std::vector<std::vector<cv::Point>> contours;
        std::vector<cv::Vec4i> hierarchy;

        cvtColor(originalFrame,
                 processedFrame,
                 CV_BGR2GRAY);
        cv::absdiff(processedFrame,
                    backgroundFrame,
                    processedFrame);
        cv::threshold(processedFrame,
                      processedFrame,
                      140, 255,
                      cv::THRESH_OTSU || cv::THRESH_BINARY);
        cv::Canny(processedFrame,
                  processedFrame,
                  2,
                  4,
                  3,
                  false);
        cv::findContours(processedFrame,
                         contours,
                         hierarchy,
                         cv::RETR_EXTERNAL,
                         cv::CHAIN_APPROX_SIMPLE);

        for (int i = 0; i < contours.size(); i++) {
            std::vector<cv::Point> cnt = contours[i];
            double area = cv::contourArea(cnt);

            if (area > 10000) {
                cv::Rect boundRectangle = cv::boundingRect(cv::Mat(cnt));
                rectangleText << "val: " << abs(boundRectangle.height * boundRectangle.width);
                cv::putText(originalFrame, rectangleText.str(),
                            cv::Point(boundRectangle.x,
                                      boundRectangle.y + boundRectangle.height + 10),
                            cv::FONT_HERSHEY_SIMPLEX,
                            0.9,
                            cv::Scalar(255, 255, 255),
                            1,
                            8);
                cv::rectangle(originalFrame,
                              boundRectangle.tl(),
                              boundRectangle.br(),
                              cv::Scalar(255, 0, 0),
                              2,
                              8,
                              0);
            }
        }
        cv::imshow(windowName, originalFrame);
        if (!cv::waitKey(1)) {
            std::cerr << "Program interrupted" << std::endl;
            break;
        }
    }

//    cv::Mat image;
//    image = cv::imread("IMAG1442.jpg", 1);
//
//    if (image.empty()) {
//        std::cerr << "Cound not open image" << std::endl;
//        return -1;
//    }
//
//
//    cv::resize(image, image, cv::Size(), 0.25, 0.25, cv::INTER_AREA);
//    cv::cvtColor(image, img_gray, CV_BGR2GRAY);
//
//    cv::namedWindow(nameOfAWindow, CV_WINDOW_AUTOSIZE);
//
//    cv::createTrackbar("Threshold", nameOfAWindow, &threshold, max_threshold, cannyThreshold);
//
//    cannyThreshold(0, 0);
//
//    cv::namedWindow("Actual mask", CV_WINDOW_AUTOSIZE);
//    cv::Mat img_gray2 = img_gray;
//    cv::Mat img_canny2;
//    cv::blur(img_gray2, img_canny2, cv::Size(3, 3));
//    Canny(img_canny2, img_canny2, 18, 90, 3, false);
//    cv::imshow("mask", img_canny2);
//    cv::imwrite("output.jpg", img_canny2);

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

//    cv::waitKey(0);

    cap.release();
    cv::destroyAllWindows();
    return 0;
}