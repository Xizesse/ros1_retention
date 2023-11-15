//tentativa de criar um nó que leia e republique noutro topico
//recebe de chatter e publica em resposta

#include "ros/ros.h"
#include "std_msgs/String.h"

ros::Publisher chatter_pub;
ros::Subscriber sub;

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
    ROS_INFO("I heard: [%s]", msg->data.c_str());
    std_msgs::String resposta_msg;
    resposta_msg.data = msg->data;
    chatter_pub.publish(resposta_msg);
}

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "listener");

  ros::NodeHandle n;

  sub = n.subscribe("chatter", 1000, chatterCallback);

  chatter_pub = n.advertise<std_msgs::String>("resposta", 1000);

  ros::spin();

  return 0;
}