#!/bin/bash
# lanca o nó de ros 1 que lê o bag, o nó de bridge, e o nó de ros2 
# chmod +x readbag.sh


killall screen

# noetic


cd ~/ros1ws/src/noob/launch


# parallel ./ ::: converte.sh bridge.sh

# parallel echo ::: 1 2 A

parallel -j 3 ::: ./converte.sh ./bridge.sh 

echo fim

# ./converte.sh

# ./bridge.sh




#TMP="source /opt/ros/noetic/setup.bash; . ~/ros1ws/devel/setup.bash; source /opt/ros/foxy/setup.bash; source install/local_setup.bash; ros2 run ros1_bridge dynamic_bridge"

#screen -dm $(eval "$TMP")
# source /opt/ros/foxy/setup.bash
# source install/local_setup.bash

#screen ros2 run retention listener
#ros2 topic echo resposta

# # screen -dm noetic; rosrun ; 

# # screen -dm ros2

# # tmux 