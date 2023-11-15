cmake_minimum_required(VERSION 2.8.3)
project(noob)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS 
roscpp 
std_msgs 
sensor_msgs 
message_filters 
mavros_msgs
sensor_msgs)

## Declare ROS messages and services


## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs)

## Declare a catkin package
catkin_package()

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(talker src/talker.cpp)
target_link_libraries(talker ${catkin_LIBRARIES})


add_executable(listener src/listener.cpp)
target_link_libraries(listener ${catkin_LIBRARIES})


add_executable(meio src/listener_talker.cpp)
target_link_libraries(meio ${catkin_LIBRARIES})


add_executable(listen_string src/listen_string.cpp)
target_link_libraries(listen_string ${catkin_LIBRARIES})


add_executable(converte src/list_talk.cpp)
target_link_libraries(converte ${catkin_LIBRARIES})
add_dependencies(converte sensor_msgs)
