#include "../include/global.h"
#include "../include/batteries.h"
#include "../include/parachute.h"


/* MOST IMPORTANT VARIABLE DO NOT PLAY AROUND*/
bool MAYDAY = false;

/* Function prototypes */
void check_system(void);


void setup(){

    battery_init();
    parachute_init();
    while (true){
        check_system();
    }
    return 0;

}

/* SHOULD NEVER REACH HERE*/
void loop(); 

void check_system(void){
    check_manual_ips();
    check_battery_volt();
    check_acc();
    if (MAYDAY == TRUE)    {   
        kill_rotors();
        deploy_chute();
    }

}//*/