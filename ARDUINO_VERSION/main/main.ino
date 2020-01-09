#define DEBUG
#ifdef DEBUG_TEST
//#include "port.h"
void setup(){};
void loop(){};
#endif

#ifndef DEBUG_TEST
#include "include/commons.h"
#include "include/battery.h"
#include "include/parachute.h"
#include "include/imu.h"
#include "include/red_pencil.h"
#include "include/executioner.h"
 
void setup(){
    
    #ifdef DEBUG
    Serial.begin(115200);
    pinMode(PC13,OUTPUT);
    digitalWrite(PC13,HIGH);
    while(!Serial) {}
    Serial.println("can you see me ?");
    #endif
    error_signal_init();
    #ifdef DEBUG
    Serial.println("err sig init");
    #endif
    batteries_init();
    #ifdef DEBUG
    Serial.println("batteries_init");
    #endif
    parachute_init();
    #ifdef DEBUG
    Serial.println("parachute_init");
    #endif
    imu_init();
    #ifdef DEBUG
    Serial.println("imu_init");
    #endif
    executioner_init();
    #ifdef DEBUG
    Serial.println("executioner init");
    #endif
    while (true){
        check_system();
    }
    
    /*SHOULD NEVER REACH HERE*/
    while(1);
}

/* SHOULD NEVER REACH HERE*/
void loop(){}; 

#endif
/*END OF FILE */
