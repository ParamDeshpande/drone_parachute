#include <Arduino.h>
#line 1 "e:\\drone_parachute\\main\\main.ino"
#line 1 "e:\\drone_parachute\\main\\main.ino"
#define DEBUG
#ifdef DEBUG
//#include "port.h"
#line 4 "e:\\drone_parachute\\main\\main.ino"
void setup();
#line 5 "e:\\drone_parachute\\main\\main.ino"
void loop();
#line 4 "e:\\drone_parachute\\main\\main.ino"
void setup(){};
void loop(){};
#endif

#ifndef DEBUG
#include "include/commons.h"
#include "include/battery.h"
#include "include/parachute.h"
#include "include/imu.h"
#include "include/red_pencil.h"

//unsigned long long current_time = millis();

/* MOST IMPORTANT VARIABLE DO NOT F*CK AROUND*/
static bool MAYDAY = false;

/* Function prototypes */
void check_system(void);

 
void setup(){
    
    #ifdef DEBUG
    Serial.begin(115200);
    while(!Serial) {}
    #endif

    batteries_init();
    parachute_init();
    imu_init();

    while (true){
        check_system();
    }
    
    /*SHOULD NEVER REACH HERE*/
    while(1);
}

/* SHOULD NEVER REACH HERE*/
void loop(); 

void check_system(void){
//  current_time = millis();
  
    check_main_battery_volt();
    check_backup_battery_volt();
    check_state();
    if (MAYDAY == TRUE)    {   
        kill_rotors();
        deploy_chute();
        while (true){
          raise_error_signal();
        }

    }

}//*/
#endif
/*END OF FILE */

