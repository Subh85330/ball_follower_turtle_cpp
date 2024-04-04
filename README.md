# Orangewood Assignment - Ball Follower Turtle

## Submitted By: Subham
## gmail : subhamk356@gmail.com

## Usage
Clone the repo in src folder of your ros workspace (catkin_ws). Build the package, source the package,


```bash
catkin_make
```

```bash
source /opt/ros/noetic/setup.bash
source ~/catkin_ws/devel/setup.bash
```
Firstly run the below node this will generate a video of a ball moving on a lemniscate. 

```bash
rosrun ball_follower_turtle_cpp lemniscate_video_node
```

Video should be saved in the home directory of your ubuntu system./

Now open new terminal and run the following command

```bash
source /opt/ros/noetic/setup.bash
source ~/catkin_ws/devel/setup.bash
```
Now run the below launch file
```bash
roslaunch ball_follower_turtle_cpp start_controller.launch 
```

Now run the node to publish the video feed;
```bash
rosrun ball_follower_turtle_cpp publish_video_feed
```
