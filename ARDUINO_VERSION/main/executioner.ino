

#include "include/commons.h"
#include "include/battery.h"
#include "include/parachute.h"
#include "include/imu.h"
#include "include/red_pencil.h"
#include "include/executioner.h"
 

void check_system(void){
    check_main_battery_volt();
    check_state();
    if((BATTERY_MAYDAY == true) OR (FREEFALL_MAYDAY == true)){
       kill_rotors();
        deploy_chute();
        while (true){
          raise_error_signal();  
        } 
    }
}
//*/