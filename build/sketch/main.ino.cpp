#include <Arduino.h>
#line 1 "e:\\drone_parachute\\arduino_version\\main\\main.ino"
#line 1 "e:\\drone_parachute\\arduino_version\\main\\main.ino"
#define DEBUG
#ifdef DEBUG_TEST
//#include "port.h"
void setup(){};
void loop(){};
#endif

#ifndef DEBUG_TEST
#include "include/commons.h"
#include "include/battery.h"
#include "include/parachute.h"
#include "include/imu.h"
#include "include/red_pencil.h"
#include "include/executioner.h"
 
#line 16 "e:\\drone_parachute\\arduino_version\\main\\main.ino"
void setup();
#line 36 "e:\\drone_parachute\\arduino_version\\main\\main.ino"
void loop();
#line 42 "e:\\drone_parachute\\arduino_version\\main\\battery.ino"
void batteries_init(void);
#line 64 "e:\\drone_parachute\\arduino_version\\main\\battery.ino"
void check_main_battery_volt(void);
#line 13 "e:\\drone_parachute\\arduino_version\\main\\executioner.ino"
void executioner_init(void);
#line 27 "e:\\drone_parachute\\arduino_version\\main\\executioner.ino"
void handler_tim2(void);
#line 31 "e:\\drone_parachute\\arduino_version\\main\\executioner.ino"
void check_system(void);
#line 31 "e:\\drone_parachute\\arduino_version\\main\\imu.ino"
void imu_init(void);
#line 52 "e:\\drone_parachute\\arduino_version\\main\\imu.ino"
void refresh_imu(void);
#line 68 "e:\\drone_parachute\\arduino_version\\main\\imu.ino"
void check_state(void);
#line 12 "e:\\drone_parachute\\arduino_version\\main\\parachute.ino"
void parachute_init(void);
#line 17 "e:\\drone_parachute\\arduino_version\\main\\parachute.ino"
void deploy_chute();
#line 29 "e:\\drone_parachute\\arduino_version\\main\\parachute.ino"
void kill_rotors(void);
#line 12 "e:\\drone_parachute\\arduino_version\\main\\red_pencil.ino"
void error_signal_init(void);
#line 17 "e:\\drone_parachute\\arduino_version\\main\\red_pencil.ino"
void raise_error_signal(void);
#line 16 "e:\\drone_parachute\\arduino_version\\main\\main.ino"
void setup(){
    
    #ifdef DEBUG
    Serial.begin(115200);
    while(!Serial) {}
    #endif

    batteries_init();
    parachute_init();
    imu_init();
    executioner_init();
    while (true){
        check_system();
    }
    
    /*SHOULD NEVER REACH HERE*/
    while(1);
}

/* SHOULD NEVER REACH HERE*/
void loop(){}; 

#endif
/*END OF FILE */

#line 1 "e:\\drone_parachute\\arduino_version\\main\\battery.ino"
/*
*  @brief: monitors status of the 2 batteries. IE main and the backup battery.
*
*
*   @param: NULL
*
*/

#include "include/battery.h"
#include "include/commons.h"
#include "include/red_pencil.h"

/*GLOBAL VARS*/
bool BATTERY_MAYDAY = false;

/*PRIVATE VARS*/
static float main_battery_volt_est = 0;
static float backup_battery_volt_est = 0;

/*EDIT THESE PARAMETERS (If needed ...) 
 * NOTE the pins are 3.3v tolerant so make sure to keep the calculations in check for max pin voltage else it WILL BURN DOWN the mcu 
 *  ALL CALCULATIONS ARE FOR THE MAIN BATTERY
 */
static const float MAIN_max_cell_voltage = 4.2;
static const float MAIN_min_cell_voltage = 3.3;
static const float MAIN_no_of_cells = 4.0;
static const float step_down_factor = 6.0;
/*suggested not to modify beyond 3 to 4 percent*/
static const float percent_tolerance = 2.0; /*BOTH MAX AND MIN used accordingly*/
/*ie for 2 percent max 4.28v and 3.23v min*/


static const float BACKUP_max_cell_voltage = 4.2;
static const float BACKUP_min_cell_voltage = 3.5;   /*ALTHOUGH 3.3v using rhis for a safer option*/



/*DO NOT TOUCH THESE PARAMETERS*/
static const float max_pin_voltage = ((MAIN_no_of_cells*MAIN_max_cell_voltage)/(step_down_factor))*(1.0+percent_tolerance*0.01);
static const float min_pin_voltage = ((MAIN_no_of_cells*MAIN_min_cell_voltage)/(step_down_factor))*(1.0-percent_tolerance*0.01);

void batteries_init(void){
    /*cause 3.3v max voltage for pin*/
    if(max_pin_voltage > 3.2){
        raise_error_signal();
    }

    pinMode(MAIN_BAT_VOLT_PIN,INPUT_ANALOG);
    pinMode(BACKUP_BAT_VOLT_PIN,INPUT_ANALOG);
    
    /*SEE IF BACKUP BATTERY IS ALL RIGHT*/
    backup_battery_volt_est = analogRead(BACKUP_BAT_VOLT_PIN);
    if(backup_battery_volt_est < BACKUP_min_cell_voltage){
        raise_error_signal();
    }
    
    /*SEE IF MAIN BATTERY IS ALL RIGHT*/
    main_battery_volt_est = analogRead(MAIN_BAT_VOLT_PIN);
    if((main_battery_volt_est <= 3.2) AND (main_battery_volt_est > max_pin_voltage) ){
         raise_error_signal();
    }
}

void check_main_battery_volt(void){
    main_battery_volt_est = analogRead(MAIN_BAT_VOLT_PIN);
    if(main_battery_volt_est <= min_pin_voltage ){
        BATTERY_MAYDAY = true;
    }
    
}

#line 1 "e:\\drone_parachute\\arduino_version\\main\\executioner.ino"


#include "include/commons.h"
#include "include/battery.h"
#include "include/parachute.h"
#include "include/imu.h"
#include "include/red_pencil.h"
#include "include/executioner.h"
 
#define TICK_DURATION (20e3)
//#define exec_tick_count (0)

void executioner_init(void){
HardwareTimer timer(2);
timer.pause();
timer.setPeriod(TICK_DURATION); 
timer.setChannel1Mode(TIMER_OUTPUT_COMPARE);
timer.setCompare(TIMER_CH1, 1);  // Interrupt 1 count after each update
timer.attachCompare1Interrupt(handler_tim2);
// Refresh the timer's count, prescale, and overflow
timer.refresh();
// Start the timer counting
timer.resume();

}
/*SPECIALLY CRAFTED FOR REFRESH IMU*/ 
void handler_tim2(void){
  refresh_imu();
}

void check_system(void){
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


#line 1 "e:\\drone_parachute\\arduino_version\\main\\imu.ino"
/*
Advanced_I2C.ino
Brian R Taylor
brian.taylor@bolderflight.com
*/

#include <MPU9250.h>
#include "include/imu.h"
#include "include/commons.h"
#include "include/red_pencil.h"

#define DEBUG

/*GLOBAL VARS*/
bool FREEFALL_MAYDAY = false; 

/*PRIVATE VARS*/
static MPU9250 IMU(Wire,0x68); /* an MPU9250 object with the MPU-9250 sensor on I2C bus 0 with address 0x68 */
static int status;

static float ax_ffall = 0;
static float ay_ffall = 0;
static float az_ffall = 0;

static float ax_gnd = 0;
static float ay_gnd = 0;
static float az_gnd = 0;

static float a_net_gnd = 0 ;

void imu_init(void) { 
  status = IMU.begin();
  if (status < 0) {
    raise_error_signal();
    #ifdef DEBUG
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    #endif
  }
  // setting the accelerometer full scale range to +/-8G 
  IMU.setAccelRange(MPU9250::ACCEL_RANGE_8G);
  // setting the gyroscope full scale range to +/-500 deg/s
  IMU.setGyroRange(MPU9250::GYRO_RANGE_500DPS);
  // setting DLPF bandwidth to 20 Hz
  IMU.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_20HZ);
  // setting SRD to 19 for a 50 Hz update rate
  IMU.setSrd(19);
}

void refresh_imu(void) {
  // read the sensor
  IMU.readSensor();
  }



    /*CHECK FREE FALL CONDITION OR NOT
    *   A LOT OF CHECKS CAN BE DONE like orientation etc etc 
    * BUT THIS IS THE PROTOTYPE VERSION 
    *  SO ONLY few 
    *  will be adding time later on ...
    * 
    * 
    */

void check_state(void){
    //refresh_imu();
    #ifdef DEBUG
  // display the data
  Serial.print(IMU.getAccelX_mss(),6);
  Serial.print("\t");
  Serial.print(IMU.getAccelY_mss(),6);
  Serial.print("\t");
  Serial.print(IMU.getAccelZ_mss(),6);
  Serial.print("\t");
  Serial.print(IMU.getGyroX_rads(),6);
  Serial.print("\t");
  Serial.print(IMU.getGyroY_rads(),6);
  Serial.print("\t");
  Serial.print(IMU.getGyroZ_rads(),6);
  Serial.print("\t");
  Serial.print(IMU.getMagX_uT(),6);
  Serial.print("\t");
  Serial.print(IMU.getMagY_uT(),6);
  Serial.print("\t");
  Serial.print(IMU.getMagZ_uT(),6);
  Serial.print("\t");
  Serial.println(IMU.getTemperature_C(),6);
  delay(20);
  #endif

    ax_ffall = IMU.getAccelX_mss();
    ay_ffall = IMU.getAccelY_mss();
    az_ffall = IMU.getAccelZ_mss();    
    
    a_net_gnd = sqrt(sq(ax_ffall) + sq(ay_ffall) + sq(az_ffall));

    if(a_net_gnd >= 6.0){
      delay(350);
      if( ((ax_ffall>-3.0)AND(ax_ffall<3.0)) AND ((ay_ffall>-3.0)AND(ay_ffall<3.0)) AND ((az_ffall>-3.0)AND(az_ffall<3.0)) )
      FREEFALL_MAYDAY = true;
    }

}
#line 1 "e:\\drone_parachute\\arduino_version\\main\\parachute.ino"

#include <Servo.h>
#include "include/commons.h"
#include "include/parachute.h"

#define RELAY_TRIGGER_SIGNAL HIGH

static Servo container_lid_servo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
static int pos = 0;    // variable to store the servo position

void parachute_init(void) {
  container_lid_servo.attach(SERVO_PIN);  // attaches the servo on pin 9 to the servo object
  pinMode(RELAY_PIN,OUTPUT);
}

void deploy_chute() {
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    container_lid_servo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    container_lid_servo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

void kill_rotors(void){
    digitalWrite(RELAY_PIN,RELAY_TRIGGER_SIGNAL);
}

#line 1 "e:\\drone_parachute\\arduino_version\\main\\red_pencil.ino"
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
        delay(1000);
        digitalWrite(BUZZER_PIN, LOW);
        digitalWrite(LED_PIN, LOW);
        delay(1000);
    }
}

