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
    while(!Serial) {}
    #endif

    batteries_init();
    parachute_init();
    imu_init();
    executioner_init();
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
