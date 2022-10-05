
#include <opencv2/opencv.hpp>
#include <iostream>


int main( int argc, char** argv ) {

    cv::VideoCapture cap;
    if (argc==1) {
        cap.open(0);
    } else {
        cap.open(std::atoi(argv[1]));
    }
    if( !cap.isOpened() ) { // check if we succeeded
        std::cerr << "Couldn't open capture." << std::endl;
        return -1;
    }

    while (cap.isOpened()) {
        cv::Mat frame;
        cap >> frame;
        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_RGB2GRAY);

        cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE);// Create a window for display.
        cv::Mat blurred;
        cv::GaussianBlur(gray, blurred, cv::Size(5, 5), 0);
        cv::Mat canny;
        cv::Canny(blurred, canny, 50, 150, 3);
        cv::Mat dilated;
        cv::dilate(canny, dilated, cv::Mat(), cv::Point(1, 1), 1);
        std::vector<std::vector<cv::Point> > contours;
        cv::findContours(dilated, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
        std::vector<std::vector<cv::Point_<int>>> big_contours;
        unsigned counter = 0;
        for (auto &contour: contours) {
            if (cv::contourArea(contour) > 400) {
                big_contours.emplace_back(contour);
                counter++;
            }
        }
        std::cout << counter;
        cv::drawContours(frame, big_contours, -1, cv::Scalar::all(255));
        cv::imshow("Display window", frame);

        cv::waitKey(1);
    }





    return 0;

}