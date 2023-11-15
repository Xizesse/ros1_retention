//tentativa de criar um nó que leia e republique noutro topico
//recebe de chatter e publica em resposta

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/Range.h"

#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <mavros_msgs/State.h>


ros::Publisher chatter_pub;
ros::Subscriber sub;


void myCallback(const mavros_msgs::State::ConstPtr& state, const sensor_msgs::Range::ConstPtr& d)
{
  // ROS_INFO("Entrou Callback");
  std_msgs::String resposta_msg;
  resposta_msg.data = state->mode;
  ROS_INFO("Estado: [%s]", resposta_msg.data.c_str());
  ROS_INFO("Distancia: [%f]", d->range);
  
  chatter_pub.publish(resposta_msg);

}

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "converte");

  ros::NodeHandle n;

  // sub = n.subscribe("chatter", 1000, chatterCallback);
  message_filters::Subscriber<mavros_msgs::State> sub_state(n, "mavros/state", 1);
  message_filters::Subscriber<sensor_msgs::Range> sub_range(n, "mavros/rangefinder/rangefinder", 1);

  // Aproximate time
  typedef message_filters::sync_policies::ApproximateTime<mavros_msgs::State, sensor_msgs::Range>MySyncPolicy;
  
  //state -> 1hz, rangefinder -> 5hz
  message_filters::Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), sub_state, sub_range);

  //method of the syncronizer to call the callback
  sync.registerCallback(boost::bind(&myCallback, _1, _2));

  chatter_pub = n.advertise<std_msgs::String>("resposta", 1000);

  ros::Rate rate(100);

  while(ros::ok())
  {
    ros::spinOnce();
    rate.sleep();
  }

  return 0;
}