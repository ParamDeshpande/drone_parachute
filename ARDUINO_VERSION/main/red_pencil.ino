/*
* THIS FILE HELPS IN DEBUGGING
*/


#include "include/commons.h"
#include "include/red_pencil.h"


/*PRIVATE VARS*/

void error_signal_init(void){
    pinMode(BUZZER_PIN,OUTPUT);
    pinMode(LED_PIN,OUTPUT);
}

void raise_error_signal(void){
    while(true){
        digitalWrite(BUZZER_PIN, HIGH);
        digitalWrite(LED_PIN, HIGH);
        delay(200);
        digitalWrite(BUZZER_PIN, LOW);
        digitalWrite(LED_PIN, LOW);
        delay(1000);
    }
}
