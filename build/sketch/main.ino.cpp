#include <Arduino.h>
#line 1 "/mnt/Workspace/drone_parachute/arduino_version/main/main.ino"
#define DEBUG
#define BT_DEBUG
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

#line 18 "/mnt/Workspace/drone_parachute/arduino_version/main/main.ino"
void setup();
#line 60 "/mnt/Workspace/drone_parachute/arduino_version/main/main.ino"
void loop();
#line 59 "/mnt/Workspace/drone_parachute/arduino_version/main/battery.ino"
void batteries_init(void);
#line 99 "/mnt/Workspace/drone_parachute/arduino_version/main/battery.ino"
void check_main_battery_volt(void);
#line 13 "/mnt/Workspace/drone_parachute/arduino_version/main/executioner.ino"
void executioner_init(void);
#line 27 "/mnt/Workspace/drone_parachute/arduino_version/main/executioner.ino"
void handler_tim2(void);
#line 31 "/mnt/Workspace/drone_parachute/arduino_version/main/executioner.ino"
void check_system(void);
#line 32 "/mnt/Workspace/drone_parachute/arduino_version/main/imu.ino"
void imu_init(void);
#line 53 "/mnt/Workspace/drone_parachute/arduino_version/main/imu.ino"
void refresh_imu(void);
#line 69 "/mnt/Workspace/drone_parachute/arduino_version/main/imu.ino"
void check_state(void);
#line 13 "/mnt/Workspace/drone_parachute/arduino_version/main/parachute.ino"
void parachute_init(void);
#line 18 "/mnt/Workspace/drone_parachute/arduino_version/main/parachute.ino"
void deploy_chute();
#line 26 "/mnt/Workspace/drone_parachute/arduino_version/main/parachute.ino"
void kill_rotors(void);
#line 12 "/mnt/Workspace/drone_parachute/arduino_version/main/red_pencil.ino"
void error_signal_init(void);
#line 17 "/mnt/Workspace/drone_parachute/arduino_version/main/red_pencil.ino"
void raise_error_signal(void);
#line 18 "/mnt/Workspace/drone_parachute/arduino_version/main/main.ino"
void setup(){
    
    #ifdef DEBUG
    Serial.begin(115200);
    #ifdef BT_DEBUG
    Serial3.begin(9600);
    Serial3.println("can you see me ?");
    #endif
    pinMode(PC13,OUTPUT);
    digitalWrite(PC13,HIGH);
    while(!Serial) {}
    Serial.println("can you see me ?");
    #endif
    error_signal_init();
    #ifdef DEBUG
    Serial.println("err sig init");
    #endif
    batteries_init();
    #ifdef DEBUG
    Serial.println("batteries_init");
    #endif
    parachute_init();
    #ifdef DEBUG
    Serial.println("parachute_init");
    #endif
    imu_init();
    #ifdef DEBUG
    Serial.println("imu_init");
    #endif
    executioner_init();
    #ifdef DEBUG
    Serial.println("executioner init");
    #endif
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

#line 1 "/mnt/Workspace/drone_parachute/arduino_version/main/battery.ino"
/*
*  @brief: monitors status of the 2 batteries. IE main and the backup battery.
*
*
*   @param: NULL
*
*/
#define DEBUG

#include "include/battery.h"
#include "include/commons.h"
#include "include/red_pencil.h"

/*GLOBAL VARS*/
bool BATTERY_MAYDAY = false;

/*PRIVATE VARS*/
static const float ADC_resolution = 4096.0; 
static const float ADC_ref_voltage = 3.3; 

/*ESTIMATE OF ACTUAL BATTERY VOLTAGE*/
static float main_battery_volt_est = 0;
/*ESTIMATE OF ACTUAL BATTERY VOLTAGE*/
static float backup_battery_volt_est = 0;

/*EDIT THESE PARAMETERS (If needed ...) 
 * NOTE the pins are 3.3v tolerant so make sure to keep the calculations in check for max pin voltage else it WILL BURN DOWN THE MCU PERIOD.
 */
static const float MAIN_max_cell_voltage = 4.2;
static const float MAIN_min_cell_voltage = 3.3;

#ifdef DEBUG
static const float MAIN_no_of_cells = 3.0; /*SERIES */
#endif
#ifndef DEBUG
static const float MAIN_no_of_cells = 4.0; /*SERIES */
#endif

static const float MAIN_step_down_factor = 6.0;

static const float BACKUP_max_cell_voltage = 4.2;
static const float BACKUP_min_cell_voltage = 3.5;   /*ALTHOUGH 3.3v using rhis for a safer option*/
static const float BACKUP_no_of_cells = 4.0; /*SERIES */
static const float BACKUP_step_down_factor = 2.0;

/*suggested not to modify beyond 3 to 4 percent*/
static const float percent_tolerance = 2.0; /*BOTH MAX AND MIN used accordingly*/
/*ie for 2 percent max 4.28v and 3.23v min per cell*/


/*DO NOT TOUCH THESE PARAMETERS edit other parameters to change these*/
static const float MAIN_max_pin_voltage = ((MAIN_no_of_cells*MAIN_max_cell_voltage)/(MAIN_step_down_factor))*(1.0+percent_tolerance*0.01);
static const float MAIN_min_pin_voltage = ((MAIN_no_of_cells*MAIN_min_cell_voltage)/(MAIN_step_down_factor))*(1.0-percent_tolerance*0.01);

static const float BACKUP_max_pin_voltage = ((BACKUP_no_of_cells*BACKUP_max_cell_voltage)/(BACKUP_step_down_factor))*(1.0+percent_tolerance*0.01);
static const float BACKUP_min_pin_voltage = ((BACKUP_no_of_cells*BACKUP_min_cell_voltage)/(BACKUP_step_down_factor))*(1.0-percent_tolerance*0.01);


void batteries_init(void){
    /*cause 3.3v max voltage for pin*/
    if(MAIN_max_pin_voltage > 3.2){
        #ifdef DEBUG
        Serial.println("Calculations for max Main battery pin voltage exceed 3.2v");
        #endif  
        
        raise_error_signal();
        
    }
 
    pinMode(MAIN_BAT_VOLT_PIN,INPUT_ANALOG);
    pinMode(BACKUP_BAT_VOLT_PIN,INPUT_ANALOG);
    /*SEE IF BACKUP BATTERY IS ALL RIGHT ESTIMATE OF ACTUAL BATTERY VOLTAGE*/
    backup_battery_volt_est = (analogRead(BACKUP_BAT_VOLT_PIN)*ADC_ref_voltage*BACKUP_step_down_factor)/(ADC_resolution);
    if(backup_battery_volt_est < BACKUP_min_cell_voltage){
        
        #ifdef DEBUG
        Serial.println("Struck at backup battery init backup est");
        Serial.println(backup_battery_volt_est);
        
        #endif
    
        raise_error_signal();
        
    }
    
    /*SEE IF MAIN BATTERY IS ALL RIGHT ie within range*/
    main_battery_volt_est = (analogRead(MAIN_BAT_VOLT_PIN)*ADC_ref_voltage*MAIN_step_down_factor)/(ADC_resolution);
    if((main_battery_volt_est <= 3.2*MAIN_step_down_factor) AND (main_battery_volt_est > MAIN_max_pin_voltage*MAIN_step_down_factor) ){
        
        #ifdef DEBUG
        Serial.println("Struck at main battery init");
        #endif
        
        raise_error_signal();
        
    }
}

void check_main_battery_volt(void){
    main_battery_volt_est = (analogRead(MAIN_BAT_VOLT_PIN)*ADC_ref_voltage*MAIN_step_down_factor)/(ADC_resolution);
    #ifdef DEBUG 
    Serial.print("Current main battery voltage");
    Serial.println(main_battery_volt_est);
    #endif
    if(main_battery_volt_est <= MAIN_min_pin_voltage*MAIN_step_down_factor ){
        BATTERY_MAYDAY = true;
    }
    
}

#line 1 "/mnt/Workspace/drone_parachute/arduino_version/main/bluetooth.ino"

#line 1 "/mnt/Workspace/drone_parachute/arduino_version/main/executioner.ino"


#include "include/commons.h"
#include "include/battery.h"
#include "include/parachute.h"
#include "include/imu.h"
#include "include/red_pencil.h"
#include "include/executioner.h"
 
#define TICK_DURATION (20e3)
//#define exec_tick_count (0)

void executioner_init(void){
//HardwareTimer timer(2);
//timer.pause();
//timer.setPeriod(TICK_DURATION); 
//timer.setChannel1Mode(TIMER_OUTPUT_COMPARE);
//timer.setCompare(TIMER_CH1, 1);  // Interrupt 1 count after each update
//timer.attachCompare1Interrupt(handler_tim2);
//// Refresh the timer's count, prescale, and overflow
//timer.refresh();
//// Start the timer counting
//timer.resume();

}
/*SPECIALLY CRAFTED FOR REFRESH IMU*/ 
void handler_tim2(void){
  refresh_imu();
}

void check_system(void){
     refresh_imu();
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


#line 1 "/mnt/Workspace/drone_parachute/arduino_version/main/imu.ino"
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
#define acc_gravity 9.82

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
    
    a_net_gnd = abs(sqrt(sq(ax_ffall) + sq(ay_ffall) + sq(az_ffall)) - acc_gravity);

    if(a_net_gnd >= 6.0){
      //delay(10);
      if( ((ax_ffall>-3.0)AND(ax_ffall<3.0)) AND ((ay_ffall>-3.0)AND(ay_ffall<3.0)) AND ((az_ffall>-3.0)AND(az_ffall<3.0)) )
      FREEFALL_MAYDAY = true;
    }

}
#line 1 "/mnt/Workspace/drone_parachute/arduino_version/main/parachute.ino"

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
}

void kill_rotors(void){
    digitalWrite(RELAY_PIN,RELAY_TRIGGER_SIGNAL);
}

#line 1 "/mnt/Workspace/drone_parachute/arduino_version/main/red_pencil.ino"
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

