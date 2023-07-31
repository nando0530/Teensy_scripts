/*
 * rosserial PubSub Example
 * Prints "hello world!" and toggles led
 */

#include <ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Byte.h>

ros::NodeHandle  nh;

void estop_cmd_callback( const std_msgs::Bool& estop_msg){
  //Bool msg from estop_cmd topic for relay to estop nachi manipulator
   digitalWrite(4, HIGH * estop_msg.data); 
  
}

void lights_cmd_callback( const std_msgs::Byte& lights_msg){
  //Byte decoder for lights_cmd topic 
  //0b00000001 = light red  red1 on
  //0b00000010 = light red Estop on
  //0b00000100 = light red Fault on 
  //0b00001000 = light green Motor on 
  //0b00010000 = light green Running
  unsigned char light_red1, light_Estop, light_Fault, light_Motor_on, light_Running;
  light_red1 = bitRead(lights_msg.data, 0);
  light_Estop = bitRead(lights_msg.data, 1);
  light_Fault = bitRead(lights_msg.data, 2);
  light_Motor_on = bitRead(lights_msg.data, 3);
  light_Running = bitRead(lights_msg.data, 4);

  digitalWrite(1, light_red1);  
  digitalWrite(2, light_Estop);
  digitalWrite(3, light_Fault);   
  //digitalWrite(4, light_Motor_on);
  digitalWrite(5, light_Running);  
  
}

void gripper_cmd_callback( const std_msgs::Byte& gripper_msg){
  //Byte decoder for gripper_cmd topic 
  //0b00000001 = light red  red1 on
  //0b00000010 = light red Estop on
  unsigned char Forward_gripper, Reverse_gripper;
  Forward_gripper = bitRead(gripper_msg.data, 0);
  Reverse_gripper = bitRead(gripper_msg.data, 1);
  digitalWrite(1, Forward_gripper);  
  digitalWrite(2, Reverse_gripper);
}

ros::Subscriber<std_msgs::Bool> estop_Subscriber("estop_cmd", estop_cmd_callback );
ros::Subscriber<std_msgs::Byte> lights_Subscriber("lights_cmd", lights_cmd_callback );
ros::Subscriber<std_msgs::Byte> gripper_Subscriber("gripper_cmd", gripper_cmd_callback );

void setup()
{
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  nh.initNode();
  nh.subscribe(estop_Subscriber);
  nh.subscribe(lights_Subscriber);
  nh.subscribe(gripper_Subscriber);
  
}

void loop()
{
  nh.spinOnce();
  delay(1);
}
