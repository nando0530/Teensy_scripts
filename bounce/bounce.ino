#include <Bounce.h>

// This code turns a led on/off through a debounced Start
// Build the circuit indicated here: http://arduino.cc/en/Tutorial/Start

#define Start_button 9
#define Stop_button 10
#define LED1 1
#define LED2 2

byte button_state = 0;

// Instantiate a Bounce object with a 5 millisecond debounce time
Bounce bouncer_start_button = Bounce( Start_button,5 ); 
Bounce bouncer_stop_button = Bounce( Stop_button,5 ); 


void setup() {
  pinMode(Start_button,INPUT_PULLUP);
  pinMode(Stop_button,INPUT_PULLUP);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  Serial.begin(38400);
}

void loop() {
 // Update the debouncer
  bouncer_start_button.update ( );
  bouncer_stop_button.update ( );
 
 // Get the update value
 int value_Start = bouncer_start_button.read();
 int value_Stop = bouncer_stop_button.read();
 
 // Turn on or off the LED
 if ( value_Start == LOW ) {
    digitalWrite(LED1, HIGH );
    button_state = 0b00000001;
    Serial.println("Start Button Press");
    Serial.println(button_state,BIN);
  

   
 } else if (value_Stop == LOW)  {
    digitalWrite(LED2, HIGH );
    button_state = 0b00000010;
    Serial.println("Stop Button Press");
    Serial.println(button_state,BIN);
 }

 else {
   digitalWrite(LED1, LOW );
   digitalWrite(LED2, LOW );
   button_state = 0b00000000;
   Serial.println("Buttons Release");
   Serial.println(button_state,BIN);
 }
 
 
}
