#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

using namespace cv;

int main(int argc, char **argv) {
    ros::init(argc, argv, "publish_video_node");
    ros::NodeHandle nh;

    ros::Publisher image_pub = nh.advertise<sensor_msgs::Image>("/image/ball_animation", 1);

    // VideoCapture cap("lemniscate_video.mp4");
    VideoCapture cap("lamniscate_ball.avi");
    if (!cap.isOpened()) {
        ROS_ERROR("Error opening video file");
        return -1;
    }

    ros::Rate loop_rate(1000); 

    while (ros::ok()) {
        Mat frame;
        cap >> frame;
        if (frame.empty()) {
            ROS_INFO("End of video file");
            break;
        }

        // Convert frame to ROS Image message
        sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();

        // Publish ROS Image message
        image_pub.publish(msg);

        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}
