
#include <Servo.h>
#include "../include/commons.h"

#define RELAY_TRIGGER_SIGNAL HIGH

static Servo container_lid_servo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
static int pos = 0;    // variable to store the servo position

void parachute_init(void) {
  container_lid_servo.attach(SERVO_PIN);  // attaches the servo on pin 9 to the servo object
  pinMode(RELAY_PIN,OUTPUT);
}

void deploy_chute() {
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    container_lid_servo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    container_lid_servo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

void kill_rotors(void){
    digitalWrite(RELAY_PIN,RELAY_TRIGGER_SIGNAL);
}
