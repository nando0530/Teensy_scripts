/*
 * rosserial Publisher Example
 * Prints "hello world!"
 */

#include <ros.h>
#include <std_msgs/Byte.h>

ros::NodeHandle  nh;

std_msgs::Byte bt_msg;
ros::Publisher chatter("chatter", &bt_msg);

//char hello[13] = "hello world!";

void setup()
{
  nh.initNode();
  nh.advertise(chatter);
}

void loop()
{
  //str_msg.data = hello;
  uint8_t val =0;
  val |= 0b01100001;
  bt_msg.data = val;
  chatter.publish( &bt_msg );
  nh.spinOnce();
  delay(1000);
}
