/*
*  @brief: monitors status of the 2 batteries. IE main and the backup battery.
*
*
*   @param: NULL
*
*/

#include "../include/commons.h"
#include "../include/batteries.h"

void batteries_init(void){
    pinMode(MAIN_BAT_VOLT_PIN,INPUT);
    pinMode(BACKUP_BAT_VOLT_PIN,INPUT);

}
