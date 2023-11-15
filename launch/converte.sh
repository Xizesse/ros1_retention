#!/bin/bash

echo Source Noetic
source /opt/ros/noetic/setup.bash
. ~/ros1ws/devel/setup.bash

cd ~/ros1ws

echo Launch Master e Converte

roslaunch noob readbag.launch