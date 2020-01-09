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