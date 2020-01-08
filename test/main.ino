
#include <Arduino.h>
#include "../lib/SPI.h"
#include "../lib/Wire.h"
#include "../lib/MPU9250.h"

void setup() {
  // serial to display data
  Serial.begin(9600);
  while(!Serial) {

  digitalWrite(PC13,HIGH);

  delay(10000);

  digitalWrite(PC13,LOW);
  
  delay(10000);
  
  } 

  void loop(){

  digitalWrite(PC13,HIGH);

  }