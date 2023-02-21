#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#include "logging.h"

int main(int argc, char **argv)
{
    logi("Starting");

    cv::namedWindow("Output", 1);

    cv::Mat output = cv::Mat::zeros(120, 350, CV_8UC3);

    putText(output,
        "Hello Sailor",
        cv::Point(15,70),
        cv::FONT_HERSHEY_PLAIN, 3,
        cv::Scalar(0,255,0), 4
    );

    cv::imshow("Output", output);

    cv::waitKey(0);

    return 0;
}
