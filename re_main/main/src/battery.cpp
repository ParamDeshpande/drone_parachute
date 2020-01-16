/*
*  @brief: monitors status of the 2 batteries. IE main and the backup battery.
*
*
*   @param: NULL
*
*/

#include "../include/battery.h"
#include "../include/commons.h"

float main_battery_volt_est = 0;
float backup_battery_volt_est = 0;

void batteries_init(void){
    pinMode(MAIN_BAT_VOLT_PIN,INPUT);
    pinMode(BACKUP_BAT_VOLT_PIN,INPUT);
}

void check_main_battery_volt(void){
    main_battery_volt_est = analogRead(MAIN_BAT_VOLT_PIN);
}

void check_backup_battery_volt(void){
    backup_battery_volt_est = analogRead(BACKUP_BAT_VOLT_PIN);
}
