#ifndef PORT_H
#define PORT_H

enum PIN_Nos{PA2,PA3,PB0,PB1};


#define RX (PA3)
#define TX (PA2)

#define SCL (PB6)
#define SDA (PB7)

#define LED_PIN (PC13)
#define SERVO_PIN (PB9)
#define RELAY_PIN (PB15)
#define BUZZER_PIN (PB13)

#define MAIN_BAT_VOLT_PIN (PB1)
#define BACKUP_BAT_VOLT_PIN (PB0)

#endif // !PORT_H
