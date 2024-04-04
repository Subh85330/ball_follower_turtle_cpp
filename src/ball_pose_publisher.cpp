#include "ros/ros.h"
#include "sensor_msgs/Image.h"
#include "geometry_msgs/PoseStamped.h"
#include "cv_bridge/cv_bridge.h"
#include "opencv2/opencv.hpp"

class PosePublisher {
public:
    PosePublisher() : nh_() {
        pub_ = nh_.advertise<geometry_msgs::PoseStamped>("/turtle/move_pose", 10);
        sub_ = nh_.subscribe("/image/ball_animation", 1, &PosePublisher::frameCallback, this);
    }

    void frameCallback(const sensor_msgs::ImageConstPtr& msg) {
        try {
            cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
            frame_ = cv_ptr->image;
            showImage();
        } catch (cv_bridge::Exception& e) {
            ROS_ERROR("cv_bridge exception: %s", e.what());
            return;
        }
    }

    void showImage() {
        cv::Mat new_frame;
        cv::cvtColor(frame_, new_frame, cv::COLOR_BGR2RGB);
        cv::Mat gray;
        cv::cvtColor(new_frame, gray, cv::COLOR_BGR2GRAY);
        cv::Mat edged;
        cv::Canny(gray, edged, 30, 200);
        
        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(edged, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
        cv::drawContours(new_frame, contours, 1, cv::Scalar(255, 0, 0), 3);
        
        cv::Moments M = cv::moments(contours[1]);
        double cx = M.m10 / M.m00;
        double cy = M.m01 / M.m00;
        
        cx = (cx * 11) / 500;
        cy = (cy * 11) / 500;
        cy = 11 - cy;
        
        if (cx >= 11 || cy >= 11) {
            ROS_ERROR("Oops error happened");
            return;
        }
        
        geometry_msgs::PoseStamped p;
        p.pose.position.x = cx;
        p.pose.position.y = cy;
        pub_.publish(p);
    }

private:
    ros::NodeHandle nh_;
    ros::Publisher pub_;
    ros::Subscriber sub_;
    cv::Mat frame_;
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "pose_publisher");
    PosePublisher pose_publisher;
    ros::spin();
    return 0;
}
