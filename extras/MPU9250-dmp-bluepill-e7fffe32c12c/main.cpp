<<<<<<< HEAD
#include "SparkFunMPU9250-DMP.h"
#include "mdcompat.h"
#include "stm32f103c8t6.h"
//In order to compile, you should define MPU9250 in build macros
//definitions
#define DEBUG 0
//classes
Serial pc(SERIAL_TX,SERIAL_RX);
DigitalOut led(LED1);
MPU9250_DMP imu;

//variables
#if DEBUG
    unsigned char whoami[1]={0};
    unsigned char outbuff[4];
    unsigned char inbuff[4];
#endif

unsigned char regadd;
char registeradress[5];
unsigned char registerdata[]={33};

//Prorotypes
void printIMUData(void);

int main() 
{
  pc.baud(115200);
  pc.printf("Hello World\n");
  imu_init();
  stamper_init();
#if ~DEBUG//Regular program
  // Call imu.begin() to verify communication and initialize
  if (imu.begin() != INV_SUCCESS){
    while (1){
      pc.printf("Unable to communicate with MPU-9250");
      pc.printf("Check connections, and try again.\n");
      wait_ms(5000);
    }
  }
    pc.printf("imu.begin() suceeded\n");
  
    if(imu.dmpBegin(DMP_FEATURE_6X_LP_QUAT | // Enable 6-axis quat
               DMP_FEATURE_GYRO_CAL, // Use gyro calibration
              150)==INV_ERROR){ // Set DMP FIFO rate to 150 Hz
        pc.printf("imu.dmpBegin have failed\n");//dmpLoad function under it fails which is caused by memcmp(firmware+ii, cur, this_write) (it is located at row 2871 of inv_mpu.c)
              }
    else{
        pc.printf("imu.dmpBegin() suceeded\n");
    }
    pc.printf("$GETEU,*\n");
#endif
#if DEBUG //this scope is only for debugging purposes of mbed_i2c_read and write functions
    mbed_i2c_read(0x68,0x75,1,whoami);
    pc.printf("whoami=%d\n",whoami[0]);
    mbed_i2c_read(0x68,0x23,2,inbuff);
    pc.printf("Buffer=%d-%d\n",inbuff[0],inbuff[1]);
    outbuff[0]=inbuff[0]&0x01;
    outbuff[1]=inbuff[1]&0x02;
    pc.printf("updated buffer=%d-%d\n",outbuff[0],outbuff[1]);
    mbed_i2c_write(0x68,0x23,2,outbuff);
    mbed_i2c_read(0x68,0x23,2,inbuff);
    pc.printf("new out buffer=%d-%d(if zero, write function still needs to be fixed)\n",inbuff[0],inbuff[1]);
#endif
while(1){
    if(pc.readable()){
        pc.scanf("%s",&registeradress);
        regadd=(registeradress[0]-48)*100+(registeradress[1]-48)*10+(registeradress[2]-48);
        mbed_i2c_read(0x68,(unsigned)regadd,1,registerdata);
        pc.printf("%d is gotten from serial port, data at that register is %d\n",regadd,registerdata[0]);
    }

  // Check for new data in the FIFO
  if (imu.fifoAvailable()){//fifo is not being available
    led=0;
    wait_ms(1);
    led=1;
    wait_ms(1);
    // Use dmpUpdateFifo to update the ax, gx, mx, etc. values
    if ( imu.dmpUpdateFifo() == INV_SUCCESS){
      // computeEulerAngles can be used -- after updating the
      // quaternion values -- to estimate roll, pitch, and yaw
      imu.computeEulerAngles();
      printIMUData();
    }
  }
  else{
    led=0;
  }
}
  return 0;
}

void printIMUData(void)
{  
  // After calling dmpUpdateFifo() the ax, gx, mx, etc. values
  // are all updated.
  // Quaternion values are, by default, stored in Q30 long
  // format. calcQuat turns them into a float between -1 and 1
  float q0 = imu.calcQuat(imu.qw);
  float q1 = imu.calcQuat(imu.qx);
  float q2 = imu.calcQuat(imu.qy);
  float q3 = imu.calcQuat(imu.qz);
  
  pc.printf("$,%.4lf,%.4lf,%.4lf,*\n", imu.yaw,imu.pitch,imu.roll);
}
=======
#include "SparkFunMPU9250-DMP.h"
#include "mdcompat.h"
#include "stm32f103c8t6.h"
//In order to compile, you should define MPU9250 in build macros
//definitions
#define DEBUG 0
//classes
Serial pc(SERIAL_TX,SERIAL_RX);
DigitalOut led(LED1);
MPU9250_DMP imu;

//variables
#if DEBUG
    unsigned char whoami[1]={0};
    unsigned char outbuff[4];
    unsigned char inbuff[4];
#endif

unsigned char regadd;
char registeradress[5];
unsigned char registerdata[]={33};

//Prorotypes
void printIMUData(void);

int main() 
{
  pc.baud(115200);
  pc.printf("Hello World\n");
  imu_init();
  stamper_init();
#if ~DEBUG//Regular program
  // Call imu.begin() to verify communication and initialize
  if (imu.begin() != INV_SUCCESS){
    while (1){
      pc.printf("Unable to communicate with MPU-9250");
      pc.printf("Check connections, and try again.\n");
      wait_ms(5000);
    }
  }
    pc.printf("imu.begin() suceeded\n");
  
    if(imu.dmpBegin(DMP_FEATURE_6X_LP_QUAT | // Enable 6-axis quat
               DMP_FEATURE_GYRO_CAL, // Use gyro calibration
              150)==INV_ERROR){ // Set DMP FIFO rate to 150 Hz
        pc.printf("imu.dmpBegin have failed\n");//dmpLoad function under it fails which is caused by memcmp(firmware+ii, cur, this_write) (it is located at row 2871 of inv_mpu.c)
              }
    else{
        pc.printf("imu.dmpBegin() suceeded\n");
    }
    pc.printf("$GETEU,*\n");
#endif
#if DEBUG //this scope is only for debugging purposes of mbed_i2c_read and write functions
    mbed_i2c_read(0x68,0x75,1,whoami);
    pc.printf("whoami=%d\n",whoami[0]);
    mbed_i2c_read(0x68,0x23,2,inbuff);
    pc.printf("Buffer=%d-%d\n",inbuff[0],inbuff[1]);
    outbuff[0]=inbuff[0]&0x01;
    outbuff[1]=inbuff[1]&0x02;
    pc.printf("updated buffer=%d-%d\n",outbuff[0],outbuff[1]);
    mbed_i2c_write(0x68,0x23,2,outbuff);
    mbed_i2c_read(0x68,0x23,2,inbuff);
    pc.printf("new out buffer=%d-%d(if zero, write function still needs to be fixed)\n",inbuff[0],inbuff[1]);
#endif
while(1){
    if(pc.readable()){
        pc.scanf("%s",&registeradress);
        regadd=(registeradress[0]-48)*100+(registeradress[1]-48)*10+(registeradress[2]-48);
        mbed_i2c_read(0x68,(unsigned)regadd,1,registerdata);
        pc.printf("%d is gotten from serial port, data at that register is %d\n",regadd,registerdata[0]);
    }

  // Check for new data in the FIFO
  if (imu.fifoAvailable()){//fifo is not being available
    led=0;
    wait_ms(1);
    led=1;
    wait_ms(1);
    // Use dmpUpdateFifo to update the ax, gx, mx, etc. values
    if ( imu.dmpUpdateFifo() == INV_SUCCESS){
      // computeEulerAngles can be used -- after updating the
      // quaternion values -- to estimate roll, pitch, and yaw
      imu.computeEulerAngles();
      printIMUData();
    }
  }
  else{
    led=0;
  }
}
  return 0;
}

void printIMUData(void)
{  
  // After calling dmpUpdateFifo() the ax, gx, mx, etc. values
  // are all updated.
  // Quaternion values are, by default, stored in Q30 long
  // format. calcQuat turns them into a float between -1 and 1
  float q0 = imu.calcQuat(imu.qw);
  float q1 = imu.calcQuat(imu.qx);
  float q2 = imu.calcQuat(imu.qy);
  float q3 = imu.calcQuat(imu.qz);
  
  pc.printf("$,%.4lf,%.4lf,%.4lf,*\n", imu.yaw,imu.pitch,imu.roll);
}
>>>>>>> 3285a02e86f6d9532a0dda0541a2d4119531dbf8
