#include "ros/ros.h"
#include "geometry_msgs/PoseStamped.h"
#include "turtlesim/TeleportAbsolute.h"
#include <cmath>

class FollowTurtle
{
public:
    FollowTurtle(ros::NodeHandle &nh) : nh_(nh)
    {
        move_turtle1_client_ = nh_.serviceClient<turtlesim::TeleportAbsolute>("/turtle1/teleport_absolute");

        // Initialize the pose of turtle
        x0_ = 5.5444;
        y0_ = 5.5444;

        // 
        sub_0_ = nh_.subscribe("/turtle/move_pose", 10, &FollowTurtle::moveTurtleCallback, this);
    }

private:
    void moveTurtleCallback(const geometry_msgs::PoseStamped::ConstPtr &data)
    {
        double x = std::round(data->pose.position.x * 10000) / 10000; // Round to 4 decimal places
        double y = std::round(data->pose.position.y * 10000) / 10000;
        double dist = std::sqrt(std::pow((x - x0_), 2) + std::pow((y - y0_), 2));

        double theta = std::atan2(y - y0_, x - x0_);
        
        turtlesim::TeleportAbsolute srv;
        srv.request.x = x;
        srv.request.y = y;
        srv.request.theta = theta;

        if (move_turtle1_client_.call(srv))
        {

            x0_ = x;
            y0_ = y;
        }
        else
        {
            ROS_ERROR("Failed to call service /turtle1/teleport_absolute");
        }
    }

    ros::NodeHandle nh_;
    ros::ServiceClient move_turtle1_client_;
    ros::Subscriber sub_0_;
    double x0_;
    double y0_;
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "turtle_controller");
    ros::NodeHandle nh;

    FollowTurtle follow_turtle(nh);
    ros::spin();

    return 0;
}
