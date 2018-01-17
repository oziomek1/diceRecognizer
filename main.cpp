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

    cap.release();
    cv::destroyAllWindows();
    return 0;
}