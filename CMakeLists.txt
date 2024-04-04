cmake_minimum_required(VERSION 3.0.2)
project(ball_follower_turtle_cpp)

find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  roscpp
  rospy
  sensor_msgs
)

find_package(OpenCV REQUIRED)

catkin_package(

)

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)


add_executable(lemniscate_video_node src/ball_motion_movie.cpp)

target_link_libraries(lemniscate_video_node
    ${catkin_LIBRARIES}
    ${OpenCV_LIBS}

    )

add_executable(publish_video_feed src/publish_video_feed.cpp)
target_link_libraries(publish_video_feed
    ${catkin_LIBRARIES}
    ${OpenCV_LIBS}
    )

    add_executable(ball_pose_publisher src/ball_pose_publisher.cpp)
    target_link_libraries(ball_pose_publisher
        ${catkin_LIBRARIES}
        ${OpenCV_LIBS}
        )

add_executable(turtle_controller src/turtle_controller.cpp)
target_link_libraries(turtle_controller
        ${catkin_LIBRARIES}
        ${OpenCV_LIBS}
      )