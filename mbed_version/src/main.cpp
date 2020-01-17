#include "mbed.h"
#include "commons.h"
#include "imu.h"
#include "Servo.h"

Serial      pc(PA_2, PA_3); // TX, RX
//Servo lid_servo(PB_8);
DigitalOut myled3(PC_13);

int main() 
{  
    imu_setup();
    while(1) {
          myled3 = 0;      // turn the LED on
          for(int i=0; i<100; i++) {
//             lid_servo = i/100.0;
             wait(0.01);
         }
         for(int i=100; i>0; i--) {
//             lid_servo = i/100.0;
             wait(0.01);
         }

        //wait_ms(200);   // wait 200 millisecond
        myled3 = 1;      // turn the LED off
        pc.printf("Blink\r\n");
        refresh_imu();
    }
}
/*#include <iostream>
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
    

}*/