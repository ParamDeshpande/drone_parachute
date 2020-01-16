#include "mbed.h"
 
Serial      pc(PA_2, PA_3); // TX, RX
DigitalOut  myled(PC_13);   // on-board LED
  
int main() 
{  
    while(1) {
        // The on-board LED is connected via a resistor to +3.3V (not to GND). 
        // So the LED is active on 0
        myled = 0;      // turn the LED on
        wait_ms(200);   // wait 200 millisecond
        myled = 1;      // turn the LED off
        pc.printf("Blink\r\n");
        wait_ms(1000);  // wait 1000 millisecond
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