#include <iostream>
#include "../include/global.h"
#include "../include/battery.h"
#include "../include/parachute.h"
#include "../include/accel.h"

void check_system(void);

int main(void) {
    battery_init();
    parachute_init();
    while (true){
        check_system();
    }
    return 0;
}

void check_system(void){
    check_manual_ips();
    check_battery_volt();
    check_Z_acc();
    if (MAYDAY == TRUE)    {   
        kill_rotors();
        deploy_chute();
    }
    

}