/*
Advanced_I2C.ino
Brian R Taylor
brian.taylor@bolderflight.com
*/

#include "MPU9250.h"
#include "../include/imu.h"
#include "../include/commons.h"
#include "../include/red_pencil.h"

/*PRIVATE FUNCTION PROTYPES*/
void refresh_imu(void);

/*GLOBAL VARS*/
bool FREEFALL_MAYDAY = false; 

/*PRIVATE VARS*/
static MPU9250 IMU(Wire,0x68); /* an MPU9250 object with the MPU-9250 sensor on I2C bus 0 with address 0x68 */
static int status;

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
}


void check_state(void){
    refresh_imu();

}