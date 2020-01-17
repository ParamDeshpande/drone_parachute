
#include "mbed.h"
#include "MPU9250.h"
#include "commons.h"
#include "imu.h"

float sum = 0;
uint32_t sumCount = 0;
uint32_t imu_run_count = 0;
MPU9250 mpu9250;
Timer t;
     
void imu_setup(void){
  //Set up I2C
  i2c.frequency(400000);  // use fast (400 kHz) I2C  
  
  t.start();        
  
  // Read the WHO_AM_I register, this is a good test of communication
  uint8_t whoami = mpu9250.readByte(MPU9250_ADDRESS, WHO_AM_I_MPU9250);  // Read WHO_AM_I register for MPU-9250
  pc.printf("I AM 0x%x\n\r", whoami); pc.printf("I SHOULD BE 0x71\n\r");
  
  if (whoami == 0x71)
  {  
    pc.printf("MPU9250 is online...\n\r");
    wait(1);
    
    mpu9250.resetMPU9250(); // Reset registers to default in preparation for device calibration
    mpu9250.calibrateMPU9250(gyroBias, accelBias); // Calibrate gyro and accelerometers, load biases in bias registers  
    wait(2);
    mpu9250.initMPU9250(); 
    pc.printf("MPU9250 initialized for active data mode....\n\r"); // Initialize device for active mode read of acclerometer, gyroscope, and temperature
    mpu9250.initAK8963(magCalibration);
    pc.printf("AK8963 initialized for active data mode....\n\r"); // Initialize device for active mode read of magnetometer
    pc.printf("Accelerometer full-scale range = %f  g\n\r", 2.0f*(float)(1<<Ascale));
    pc.printf("Gyroscope full-scale range = %f  deg/s\n\r", 250.0f*(float)(1<<Gscale));
    if(Mscale == 0) pc.printf("Magnetometer resolution = 14  bits\n\r");
    if(Mscale == 1) pc.printf("Magnetometer resolution = 16  bits\n\r");
    if(Mmode == 2) pc.printf("Magnetometer ODR = 8 Hz\n\r");
    if(Mmode == 6) pc.printf("Magnetometer ODR = 100 Hz\n\r");
    wait(2);
   }
   else
   {
    pc.printf("Could not connect to MPU9250: \n\r");
    pc.printf("%#x \n",  whoami);
   }

    mpu9250.getAres(); // Get accelerometer sensitivity
    mpu9250.getGres(); // Get gyro sensitivity
    mpu9250.getMres(); // Get magnetometer sensitivity
    pc.printf("Accelerometer sensitivity is %f LSB/g \n\r", 1.0f/aRes);
    pc.printf("Gyroscope sensitivity is %f LSB/deg/s \n\r", 1.0f/gRes);
    pc.printf("Magnetometer sensitivity is %f LSB/G \n\r", 1.0f/mRes);
    magbias[0] = +470.;  // User environmental x-axis correction in milliGauss, should be automatically calculated
    magbias[1] = +120.;  // User environmental x-axis correction in milliGauss
    magbias[2] = +125.;  // User environmental x-axis correction in milliGauss
}
 void refresh_imu(void) {
  
  // If intPin goes high, all data registers have new data
  if(mpu9250.readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01) {  // On interrupt, check if data ready interrupt

    mpu9250.readAccelData(accelCount);  // Read the x/y/z adc values   
    // Now we'll calculate the accleration value into actual g's
    ax = (float)accelCount[0]*aRes - accelBias[0];  // get actual g value, this depends on scale being set
    ay = (float)accelCount[1]*aRes - accelBias[1];   
    az = (float)accelCount[2]*aRes - accelBias[2];  
   
    mpu9250.readGyroData(gyroCount);  // Read the x/y/z adc values
    // Calculate the gyro value into actual degrees per second
    gx = (float)gyroCount[0]*gRes - gyroBias[0];  // get actual gyro value, this depends on scale being set
    gy = (float)gyroCount[1]*gRes - gyroBias[1];  
    gz = (float)gyroCount[2]*gRes - gyroBias[2];   
  
    mpu9250.readMagData(magCount);  // Read the x/y/z adc values   
    // Calculate the magnetometer values in milliGauss
    // Include factory calibration per data sheet and user environmental corrections
    mx = (float)magCount[0]*mRes*magCalibration[0] - magbias[0];  // get actual magnetometer value, this depends on scale being set
    my = (float)magCount[1]*mRes*magCalibration[1] - magbias[1];  
    mz = (float)magCount[2]*mRes*magCalibration[2] - magbias[2];   
  }
   
    Now = t.read_us();
    deltat = (float)((Now - lastUpdate)/1000000.0f) ; // set integration time by time elapsed since last filter update
    lastUpdate = Now;
    
    sum += deltat;
    sumCount++;
        
   // Pass gyro rate as rad/s
  mpu9250.MadgwickQuaternionUpdate(ax, ay, az, gx*PI/180.0f, gy*PI/180.0f, gz*PI/180.0f,  my,  mx, mz);
 // mpu9250.MahonyQuaternionUpdate(ax, ay, az, gx*PI/180.0f, gy*PI/180.0f, gz*PI/180.0f, my, mx, mz);

    // Serial print and/or display at 0.5 s rate independent of data rates
    delt_t = t.read_ms() - imu_run_count;
    if (delt_t > 10) { // update LCD once per half-second independent of read rate
   
    tempCount = mpu9250.readTempData();  // Read the adc values
    temperature = ((float) tempCount) / 333.87f + 21.0f; // Temperature in degrees Centigrade
    pc.printf(" temperature = %f  C\n\r", temperature); 
    yaw   = atan2(2.0f * (q[1] * q[2] + q[0] * q[3]), q[0] * q[0] + q[1] * q[1] - q[2] * q[2] - q[3] * q[3]);   
    pitch = -asin(2.0f * (q[1] * q[3] - q[0] * q[2]));
    roll  = atan2(2.0f * (q[0] * q[1] + q[2] * q[3]), q[0] * q[0] - q[1] * q[1] - q[2] * q[2] + q[3] * q[3]);
    pitch *= 180.0f / PI;
    yaw   *= 180.0f / PI; 
    //yaw   -= 13.8f; // Declination at Danville, California is 13 degrees 48 minutes and 47 seconds on 2014-04-04
    roll  *= 180.0f / PI;

    //pc.printf("Yaw, Pitch, Roll: %f %f %f\n\r", yaw, pitch, roll);
    //pc.printf("average rate = %f\n\r", (float) sumCount/sum);
    if((ax || ay || az) >= 1.0)
    pc.printf("AX, AY, AZ: %f %f %f\n\r", ax, ay, az);
    
    myled= !myled;
    imu_run_count = t.read_ms(); 
    sum = 0; 
    sumCount = 0; 
  }
}
 
 
