#ifndef PORT_H
#define PORT_H

//enum PIN_Nos{PA2,PA3,PB0,PB1,PB6,PB7,PB9,PB13,PB15,PC13};


const int RX = (PA3) ;
const int TX = (PA2) ;
const int SCL = (PB6) ;
const int SDA = (PB7) ;
const int LED_PIN = (PC13);
const int SERVO_PIN = (PB9);
const int RELAY_PIN = (PB15);
const int BUZZER_PIN = (PB13);
const int MAIN_BAT_VOLT_PIN = (PB1);
const int BACKUP_BAT_VOLT_PIN = (PB0);

#endif // !PORT_H
