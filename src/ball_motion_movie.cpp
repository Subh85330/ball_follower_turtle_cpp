#include <opencv2/opencv.hpp>
#include <cmath>

double interpolate(double x, double x_min, double x_max, double y_min, double y_max)
{
    return y_min + (x - x_min) * (y_max - y_min) / (x_max - x_min);
}

int main()
{
    cv::VideoWriter vid("lamniscate_ball.avi", cv::VideoWriter::fourcc('M', 'P', '4', '2'), 30.0, cv::Size(500, 500));
    int a = 150;
    int f_no = 30 * 40;
    double theta_step = 2 * M_PI / f_no;

    for (int i = 0; i < 3 * f_no; ++i)
    {
        cv::Mat img(500, 500, CV_8UC3, cv::Scalar(255, 255, 255));

        double t = i * theta_step;

        // parametric equation for generating lemniscate
        double x = a * (cos(t) / (pow(sin(t), 2) + 1));
        double y = a * (cos(t) * sin(t) / (pow(sin(t), 2) + 1));

        x = interpolate(x, -150.0, 150.0, 37.0, 463.0);
        y = interpolate(y, -75.0, 75.0, 175.0, 325.0);

        cv::circle(img, cv::Point(static_cast<int>(x), static_cast<int>(y)), 10, cv::Scalar(0, 255, 0), -1);

        vid.write(img);
    }

    vid.release();

    return 0;
}
