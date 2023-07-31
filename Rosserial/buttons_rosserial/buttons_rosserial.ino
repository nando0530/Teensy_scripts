/* 
 * Button Example for Rosserial
 */

#include <ros.h>
#include <std_msgs/Byte.h>
#include <Bounce.h>
#define Start_button 9
#define Stop_button 10


ros::NodeHandle nh;

std_msgs::Byte buttons_msg;
ros::Publisher pub_buttons("buttons_cmd", &buttons_msg);


const int led1_pin = 1;
const int led2_pin = 2;

// Instantiate a Bounce object with a 5 millisecond debounce time
Bounce bouncer_start_button = Bounce( Start_button,5 ); 
Bounce bouncer_stop_button = Bounce( Stop_button,5 ); 

void setup()
{
  nh.initNode();
  nh.advertise(pub_buttons);
  
  pinMode(Start_button,INPUT_PULLUP);
  pinMode(Stop_button,INPUT_PULLUP);
  pinMode(led1_pin,OUTPUT);
  pinMode(led2_pin,OUTPUT);
 
}

void loop()
{
  uint8_t button_state = 0;

   // Update the debouncer
  bouncer_start_button.update ( );
  bouncer_stop_button.update ( );
 
 // Get the update value
 int value_Start = bouncer_start_button.read();
 int value_Stop = bouncer_stop_button.read();

  // Turn on or off the LED
 if ( value_Start == LOW ) {
    digitalWrite(led1_pin, HIGH );
    button_state |= 0x01;
    buttons_msg.data = button_state;
    pub_buttons.publish(&buttons_msg);
   
 } else if (value_Stop == LOW)  {
    digitalWrite(led2_pin, HIGH );
    button_state |= 0x02;
    buttons_msg.data = button_state;
    pub_buttons.publish(&buttons_msg);

 }

 else {
   digitalWrite(led1_pin, LOW );
   digitalWrite(led2_pin, LOW );
   button_state |= 0x00;
   buttons_msg.data = button_state;
   pub_buttons.publish(&buttons_msg);

 }
  
  nh.spinOnce();
  delay(700);
}
