//tentativa de criar um nó que leia e republique noutro topico
//recebe de chatter e publica em resposta

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Bool.h"
#include "std_msgs/Float32.h"
#include "sensor_msgs/Range.h"
#include <mavros_msgs/State.h>


ros::Publisher pub_state_armed;
ros::Publisher pub_state_mode;
ros::Publisher pub_range;

ros::Subscriber sub;


// void myCallback(const mavros_msgs::State::ConstPtr& state, const sensor_msgs::Range::ConstPtr& d, )
// {
//   // ROS_INFO("Entrou Callback");
//   std_msgs::String resposta_msg;
//   resposta_msg.data = state->mode;
//   ROS_INFO("Estado: [%s]", resposta_msg.data.c_str());
//   ROS_INFO("Distancia: [%f]", d->range);
  
//   //chatter_pub.publish(resposta_msg);
// }

void stateCallback(const mavros_msgs::State::ConstPtr& state)
{
  std_msgs::Bool state_armed_msg;
  state_armed_msg.data = state->armed;

  std_msgs::String state_mode_msg;
  state_mode_msg.data = state->mode;
  

  pub_state_armed.publish(state_armed_msg);
  pub_state_mode.publish(state_mode_msg);
  ROS_INFO("Estado: [%s], Armed: [%s]", state_mode_msg.data.c_str(), state_armed_msg.data ? "true" : "false");
}

void rangeCallback(const sensor_msgs::Range::ConstPtr& d)
{
  std_msgs::Float32 range_msg;
  range_msg.data = d->range;

  pub_range.publish(range_msg);
  ROS_INFO("Distancia: [%f]", range_msg.data);
}

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "converte");

  ros::NodeHandle n;

  ros::Subscriber sub_state = n.subscribe<mavros_msgs::State>("mavros/state", 1, stateCallback);
  ros::Subscriber sub_range = n.subscribe<sensor_msgs::Range>("mavros/rangefinder/rangefinder", 1, rangeCallback);

  pub_state_armed = n.advertise<std_msgs::Bool>("armed", 1);
  pub_state_mode = n.advertise<std_msgs::String>("mode", 1);
  pub_range = n.advertise<std_msgs::Float32>("distancia", 1);

  ros::Rate rate(100);

  while(ros::ok())
  {
    ros::spinOnce();
    rate.sleep();
  }

  return 0;
}

