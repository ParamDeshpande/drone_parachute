

#include "include/commons.h"
#include "include/battery.h"
#include "include/parachute.h"
#include "include/imu.h"
#include "include/red_pencil.h"
#include "include/executioner.h"
 
#define TICK_DURATION (20e3)
//#define exec_tick_count (0)

void executioner_init(void){
//HardwareTimer timer(2);
//timer.pause();
//timer.setPeriod(TICK_DURATION); 
//timer.setChannel1Mode(TIMER_OUTPUT_COMPARE);
//timer.setCompare(TIMER_CH1, 1);  // Interrupt 1 count after each update
//timer.attachCompare1Interrupt(handler_tim2);
//// Refresh the timer's count, prescale, and overflow
//timer.refresh();
//// Start the timer counting
//timer.resume();

}
/*SPECIALLY CRAFTED FOR REFRESH IMU*/ 
void handler_tim2(void){
  refresh_imu();
}

void check_system(void){
     refresh_imu();
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

