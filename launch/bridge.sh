#!/bin/bash

source ~/ros2ws/install/setup.sh
source /opt/ros/noetic/setup.bash
source /opt/ros/foxy/setup.bash
ros2 run ros1_bridge dynamic_bridge
sleep
echo Hello World