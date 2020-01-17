#ifndef MPU9250_H
#define MPU9250_H
#include "mbed.h"
#include "math.h"
#include "port.h"
#define AK8963_ADDRESS   0x0C<<1
#define AK8963_WHO_AM_I  0x00
#define AK8963_INFO      0x01
#define AK8963_ST1       0x02
#define AK8963_XOUT_L    0x03
#define AK8963_XOUT_H    0x04
#define AK8963_YOUT_L    0x05
#define AK8963_YOUT_H    0x06
#define AK8963_ZOUT_L    0x07
#define AK8963_ZOUT_H    0x08
#define AK8963_ST2       0x09
#define AK8963_CNTL      0x0A
#define AK8963_ASTC      0x0C
#define AK8963_I2CDIS    0x0F
#define AK8963_ASAX      0x10
#define AK8963_ASAY      0x11
#define AK8963_ASAZ      0x12
#define SELF_TEST_X_GYRO 0x00                  
#define SELF_TEST_Y_GYRO 0x01                                                                          
#define SELF_TEST_Z_GYRO 0x02
#define SELF_TEST_X_ACCEL 0x0D
#define SELF_TEST_Y_ACCEL 0x0E    
#define SELF_TEST_Z_ACCEL 0x0F
#define SELF_TEST_A      0x10
#define XG_OFFSET_H      0x13
#define XG_OFFSET_L      0x14
#define YG_OFFSET_H      0x15
#define YG_OFFSET_L      0x16
#define ZG_OFFSET_H      0x17
#define ZG_OFFSET_L      0x18
#define SMPLRT_DIV       0x19
#define CONFIG           0x1A
#define GYRO_CONFIG      0x1B
#define ACCEL_CONFIG     0x1C
#define ACCEL_CONFIG2    0x1D
#define LP_ACCEL_ODR     0x1E   
#define WOM_THR          0x1F   


#define MOT_DUR          0x20
#define ZMOT_THR         0x21
#define ZRMOT_DUR        0x22
#define FIFO_EN          0x23
#define I2C_MST_CTRL     0x24   
#define I2C_SLV0_ADDR    0x25
#define I2C_SLV0_REG     0x26
#define I2C_SLV0_CTRL    0x27
#define I2C_SLV1_ADDR    0x28
#define I2C_SLV1_REG     0x29
#define I2C_SLV1_CTRL    0x2A
#define I2C_SLV2_ADDR    0x2B
#define I2C_SLV2_REG     0x2C
#define I2C_SLV2_CTRL    0x2D
#define I2C_SLV3_ADDR    0x2E
#define I2C_SLV3_REG     0x2F
#define I2C_SLV3_CTRL    0x30
#define I2C_SLV4_ADDR    0x31
#define I2C_SLV4_REG     0x32
#define I2C_SLV4_DO      0x33
#define I2C_SLV4_CTRL    0x34
#define I2C_SLV4_DI      0x35
#define I2C_MST_STATUS   0x36
#define INT_PIN_CFG      0x37
#define INT_ENABLE       0x38
#define DMP_INT_STATUS   0x39
#define INT_STATUS       0x3A
#define ACCEL_XOUT_H     0x3B
#define ACCEL_XOUT_L     0x3C
#define ACCEL_YOUT_H     0x3D
#define ACCEL_YOUT_L     0x3E
#define ACCEL_ZOUT_H     0x3F
#define ACCEL_ZOUT_L     0x40
#define TEMP_OUT_H       0x41
#define TEMP_OUT_L       0x42
#define GYRO_XOUT_H      0x43
#define GYRO_XOUT_L      0x44
#define GYRO_YOUT_H      0x45
#define GYRO_YOUT_L      0x46
#define GYRO_ZOUT_H      0x47
#define GYRO_ZOUT_L      0x48
#define EXT_SENS_DATA_00 0x49
#define EXT_SENS_DATA_01 0x4A
#define EXT_SENS_DATA_02 0x4B
#define EXT_SENS_DATA_03 0x4C
#define EXT_SENS_DATA_04 0x4D
#define EXT_SENS_DATA_05 0x4E
#define EXT_SENS_DATA_06 0x4F
#define EXT_SENS_DATA_07 0x50
#define EXT_SENS_DATA_08 0x51
#define EXT_SENS_DATA_09 0x52
#define EXT_SENS_DATA_10 0x53
#define EXT_SENS_DATA_11 0x54
#define EXT_SENS_DATA_12 0x55
#define EXT_SENS_DATA_13 0x56
#define EXT_SENS_DATA_14 0x57
#define EXT_SENS_DATA_15 0x58
#define EXT_SENS_DATA_16 0x59
#define EXT_SENS_DATA_17 0x5A
#define EXT_SENS_DATA_18 0x5B
#define EXT_SENS_DATA_19 0x5C
#define EXT_SENS_DATA_20 0x5D
#define EXT_SENS_DATA_21 0x5E
#define EXT_SENS_DATA_22 0x5F
#define EXT_SENS_DATA_23 0x60
#define MOT_DETECT_STATUS 0x61
#define I2C_SLV0_DO      0x63
#define I2C_SLV1_DO      0x64
#define I2C_SLV2_DO      0x65
#define I2C_SLV3_DO      0x66
#define I2C_MST_DELAY_CTRL 0x67
#define SIGNAL_PATH_RESET  0x68
#define MOT_DETECT_CTRL  0x69

#define USER_CTRL        0x6A
#define PWR_MGMT_1       0x6B
#define PWR_MGMT_2       0x6C
#define DMP_BANK         0x6D
#define DMP_RW_PNT       0x6E
#define DMP_REG          0x6F
#define DMP_REG_1        0x70
#define DMP_REG_2        0x71 
#define FIFO_COUNTH      0x72
#define FIFO_COUNTL      0x73
#define FIFO_R_W         0x74
#define WHO_AM_I_MPU9250 0x75
#define XA_OFFSET_H      0x77
#define XA_OFFSET_L      0x78
#define YA_OFFSET_H      0x7A
#define YA_OFFSET_L      0x7B
#define ZA_OFFSET_H      0x7D
#define ZA_OFFSET_L      0x7E
#define ADO 0
#if ADO
#define MPU9250_ADDRESS 0x69<<1 
#else
#define MPU9250_ADDRESS 0x68<<1
#endif  
enum Ascale {
  AFS_2G = 0,
  AFS_4G,
  AFS_8G,
  AFS_16G
};

enum Gscale {
  GFS_250DPS = 0,
  GFS_500DPS,
  GFS_1000DPS,
  GFS_2000DPS
};

enum Mscale {
  MFS_14BITS = 0,
  MFS_16BITS     
};


uint8_t Ascale = AFS_8G;     
uint8_t Gscale = GFS_250DPS; 
uint8_t Mscale = MFS_16BITS; 
uint8_t Mmode = 0x06;        
float aRes, gRes, mRes;      
I2C i2c(I2C_SDA, I2C_SCL);

DigitalOut myled(LED_PIN);
int intPin = 12;
int16_t accelCount[3];
int16_t gyroCount[3];
int16_t magCount[3];

float magCalibration[3] = {0, 0, 0}, magbias[3] = {0, 0, 0};
float gyroBias[3] = {0, 0, 0}, accelBias[3] = {0, 0, 0};
float ax, ay, az, gx, gy, gz, mx, my, mz;
int16_t tempCount;
float temperature;
float SelfTest[6];

int delt_t = 0;
int count = 0;
float PI = 3.14159265358979323846f;

float GyroMeasError = PI * (60.0f / 180.0f);
float beta = sqrt(3.0f / 4.0f) * GyroMeasError;
float GyroMeasDrift = PI * (1.0f / 180.0f);
float zeta = sqrt(3.0f / 4.0f) * GyroMeasDrift;
#define Kp 2.0f * 5.0f
#define Ki 0.0f

float pitch, yaw, roll;

float deltat = 0.0f;
int lastUpdate = 0, firstUpdate = 0, Now = 0;
float q[4] = {1.0f, 0.0f, 0.0f, 0.0f};
float eInt[3] = {0.0f, 0.0f, 0.0f};
class MPU9250 {
    protected:
    public:
    void writeByte(uint8_t address, uint8_t subAddress, uint8_t data)
{
   char data_write[2];
   data_write[0] = subAddress;
   data_write[1] = data;
   i2c.write(address, data_write, 2, 0);
}

    char readByte(uint8_t address, uint8_t subAddress)
{
    char data[1]; 
    char data_write[1];
    data_write[0] = subAddress;
    i2c.write(address, data_write, 1, 1); 
    i2c.read(address, data, 1, 0); 
    return data[0]; 
}

    void readBytes(uint8_t address, uint8_t subAddress, uint8_t count, uint8_t * dest)
{     
    char data[14];
    char data_write[1];
    data_write[0] = subAddress;
    i2c.write(address, data_write, 1, 1);
    i2c.read(address, data, count, 0); 
    for(int ii = 0; ii < count; ii++) {
     dest[ii] = data[ii];
    }
} 
 

void getMres() {
  switch (Mscale)
  {
    case MFS_14BITS:
          mRes = 10.0*4912.0/8190.0;
          break;
    case MFS_16BITS:
          mRes = 10.0*4912.0/32760.0;
          break;
  }
}


void getGres() {
  switch (Gscale)
  {
    case GFS_250DPS:
          gRes = 250.0/32768.0;
          break;
    case GFS_500DPS:
          gRes = 500.0/32768.0;
          break;
    case GFS_1000DPS:
          gRes = 1000.0/32768.0;
          break;
    case GFS_2000DPS:
          gRes = 2000.0/32768.0;
          break;
  }
}


void getAres() {
  switch (Ascale)
  {
    case AFS_2G:
          aRes = 2.0/32768.0;
          break;
    case AFS_4G:
          aRes = 4.0/32768.0;
          break;
    case AFS_8G:
          aRes = 8.0/32768.0;
          break;
    case AFS_16G:
          aRes = 16.0/32768.0;
          break;
  }
}


void readAccelData(int16_t * destination)
{
  uint8_t rawData[6]; 

  readBytes(MPU9250_ADDRESS, ACCEL_XOUT_H, 6, &rawData[0]);
  destination[0] = (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]) ;
  destination[1] = (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]) ;
  destination[2] = (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]) ; 

}

void readGyroData(int16_t * destination)
{

  uint8_t rawData[6];
  readBytes(MPU9250_ADDRESS, GYRO_XOUT_H, 6, &rawData[0]);
  destination[0] = (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]) ;
  destination[1] = (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]) ;  
  destination[2] = (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]) ; 
}

void readMagData(int16_t * destination)
{

  uint8_t rawData[7];
  if(readByte(AK8963_ADDRESS, AK8963_ST1) & 0x01) {
  readBytes(AK8963_ADDRESS, AK8963_XOUT_L, 7, &rawData[0]);
  uint8_t c = rawData[6];
    if(!(c & 0x08)) {
    destination[0] = (int16_t)(((int16_t)rawData[1] << 8) | rawData[0]);
    destination[1] = (int16_t)(((int16_t)rawData[3] << 8) | rawData[2]) ;
    destination[2] = (int16_t)(((int16_t)rawData[5] << 8) | rawData[4]) ; 
   }
  }
}

int16_t readTempData()
{
  
  uint8_t rawData[2];
  readBytes(MPU9250_ADDRESS, TEMP_OUT_H, 2, &rawData[0]);
  return (int16_t)(((int16_t)rawData[0]) << 8 | rawData[1]) ;
}


void resetMPU9250() {
  writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x80);
  wait(0.1);
  }
  
  void initAK8963(float * destination)
{

  uint8_t rawData[3];
  writeByte(AK8963_ADDRESS, AK8963_CNTL, 0x00);
  wait(0.01);

  writeByte(AK8963_ADDRESS, AK8963_CNTL, 0x0F);
  wait(0.01);

  readBytes(AK8963_ADDRESS, AK8963_ASAX, 3, &rawData[0]);
  destination[0] =  (float)(rawData[0] - 128)/256.0f + 1.0f;
  destination[1] =  (float)(rawData[1] - 128)/256.0f + 1.0f;  
  destination[2] =  (float)(rawData[2] - 128)/256.0f + 1.0f; 
  writeByte(AK8963_ADDRESS, AK8963_CNTL, 0x00);
  wait(0.01);
  writeByte(AK8963_ADDRESS, AK8963_CNTL, Mscale << 4 | Mmode);
  wait(0.01);
}


void initMPU9250()
{  
  
  writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x00);
  wait(0.1);
  writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x01);
  writeByte(MPU9250_ADDRESS, CONFIG, 0x03);  
  writeByte(MPU9250_ADDRESS, SMPLRT_DIV, 0x04);
  uint8_t c = readByte(MPU9250_ADDRESS, GYRO_CONFIG);
  c = c & ~0x02; 
  c = c & ~0x18;
  c = c | Gscale << 3;
  writeByte(MPU9250_ADDRESS, GYRO_CONFIG, c );
  c = readByte(MPU9250_ADDRESS, ACCEL_CONFIG); 
  c = c & ~0x18;
  c = c | Ascale << 3;
  writeByte(MPU9250_ADDRESS, ACCEL_CONFIG, c);
  
  c = readByte(MPU9250_ADDRESS, ACCEL_CONFIG2);
  c = c & ~0x0F;
  c = c | 0x03;
  writeByte(MPU9250_ADDRESS, ACCEL_CONFIG2, c);
   writeByte(MPU9250_ADDRESS, INT_PIN_CFG, 0x22);    
   writeByte(MPU9250_ADDRESS, INT_ENABLE, 0x01);
}

void calibrateMPU9250(float * dest1, float * dest2)
{  
  uint8_t data[12];
  uint16_t ii, packet_count, fifo_count;
  int32_t gyro_bias[3] = {0, 0, 0}, accel_bias[3] = {0, 0, 0};
  writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x80); 
  wait(0.1);  
  writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x01);  
  writeByte(MPU9250_ADDRESS, PWR_MGMT_2, 0x00); 
  wait(0.2);

  writeByte(MPU9250_ADDRESS, INT_ENABLE, 0x00);
  writeByte(MPU9250_ADDRESS, FIFO_EN, 0x00);
  writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x00);
  writeByte(MPU9250_ADDRESS, I2C_MST_CTRL, 0x00);
  writeByte(MPU9250_ADDRESS, USER_CTRL, 0x00);
  writeByte(MPU9250_ADDRESS, USER_CTRL, 0x0C);
  wait(0.015);
  
  writeByte(MPU9250_ADDRESS, CONFIG, 0x01);
  writeByte(MPU9250_ADDRESS, SMPLRT_DIV, 0x00);
  writeByte(MPU9250_ADDRESS, GYRO_CONFIG, 0x00);
  writeByte(MPU9250_ADDRESS, ACCEL_CONFIG, 0x00);
  
  uint16_t  gyrosensitivity  = 131;
  
  uint16_t  accelsensitivity = 16384;
  
  writeByte(MPU9250_ADDRESS, USER_CTRL, 0x40);
  writeByte(MPU9250_ADDRESS, FIFO_EN, 0x78);
  wait(0.04);

  writeByte(MPU9250_ADDRESS, FIFO_EN, 0x00);
  readBytes(MPU9250_ADDRESS, FIFO_COUNTH, 2, &data[0]);
  fifo_count = ((uint16_t)data[0] << 8) | data[1];
  packet_count = fifo_count/12;
  for (ii = 0; ii < packet_count; ii++) {
    int16_t accel_temp[3] = {0, 0, 0}, gyro_temp[3] = {0, 0, 0};
    
    readBytes(MPU9250_ADDRESS, FIFO_R_W, 12, &data[0]);
    accel_temp[0] = (int16_t) (((int16_t)data[0] << 8) | data[1]  ) ;
    accel_temp[1] = (int16_t) (((int16_t)data[2] << 8) | data[3]  ) ;
    accel_temp[2] = (int16_t) (((int16_t)data[4] << 8) | data[5]  ) ;    
    gyro_temp[0]  = (int16_t) (((int16_t)data[6] << 8) | data[7]  ) ;
    gyro_temp[1]  = (int16_t) (((int16_t)data[8] << 8) | data[9]  ) ;
    gyro_temp[2]  = (int16_t) (((int16_t)data[10] << 8) | data[11]) ;
    
    accel_bias[0] += (int32_t) accel_temp[0];
    accel_bias[1] += (int32_t) accel_temp[1];
    accel_bias[2] += (int32_t) accel_temp[2];
    gyro_bias[0]  += (int32_t) gyro_temp[0];
    gyro_bias[1]  += (int32_t) gyro_temp[1];
    gyro_bias[2]  += (int32_t) gyro_temp[2];
            
}
    accel_bias[0] /= (int32_t) packet_count;
    accel_bias[1] /= (int32_t) packet_count;
    accel_bias[2] /= (int32_t) packet_count;
    gyro_bias[0]  /= (int32_t) packet_count;
    gyro_bias[1]  /= (int32_t) packet_count;
    gyro_bias[2]  /= (int32_t) packet_count;
    
  if(accel_bias[2] > 0L) {accel_bias[2] -= (int32_t) accelsensitivity;} 
  else {accel_bias[2] += (int32_t) accelsensitivity;}
  
  data[0] = (-gyro_bias[0]/4  >> 8) & 0xFF;
  data[1] = (-gyro_bias[0]/4)       & 0xFF;
  data[2] = (-gyro_bias[1]/4  >> 8) & 0xFF;
  data[3] = (-gyro_bias[1]/4)       & 0xFF;
  data[4] = (-gyro_bias[2]/4  >> 8) & 0xFF;
  data[5] = (-gyro_bias[2]/4)       & 0xFF;
  dest1[0] = (float) gyro_bias[0]/(float) gyrosensitivity;
  dest1[1] = (float) gyro_bias[1]/(float) gyrosensitivity;
  dest1[2] = (float) gyro_bias[2]/(float) gyrosensitivity;
  int32_t accel_bias_reg[3] = {0, 0, 0};
  readBytes(MPU9250_ADDRESS, XA_OFFSET_H, 2, &data[0]);
  accel_bias_reg[0] = (int16_t) ((int16_t)data[0] << 8) | data[1];
  readBytes(MPU9250_ADDRESS, YA_OFFSET_H, 2, &data[0]);
  accel_bias_reg[1] = (int16_t) ((int16_t)data[0] << 8) | data[1];
  readBytes(MPU9250_ADDRESS, ZA_OFFSET_H, 2, &data[0]);
  accel_bias_reg[2] = (int16_t) ((int16_t)data[0] << 8) | data[1];
  
  
  uint32_t mask = 1uL;
  uint8_t mask_bit[3] = {0, 0, 0};
  for(ii = 0; ii < 3; ii++) {
    if(accel_bias_reg[ii] & mask) mask_bit[ii] = 0x01;
  
  }
  accel_bias_reg[0] -= (accel_bias[0]/8);
  accel_bias_reg[1] -= (accel_bias[1]/8);
  accel_bias_reg[2] -= (accel_bias[2]/8);
 
  data[0] = (accel_bias_reg[0] >> 8) & 0xFF;
  data[1] = (accel_bias_reg[0])      & 0xFF;
  
  data[1] = data[1] | mask_bit[0];
  data[2] = (accel_bias_reg[1] >> 8) & 0xFF;
  
  data[3] = (accel_bias_reg[1])      & 0xFF;
  
  data[3] = data[3] | mask_bit[1];
  data[4] = (accel_bias_reg[2] >> 8) & 0xFF;
  
  data[5] = (accel_bias_reg[2])      & 0xFF;
  
  data[5] = data[5] | mask_bit[2];
   dest2[0] = (float)accel_bias[0]/(float)accelsensitivity; 
   dest2[1] = (float)accel_bias[1]/(float)accelsensitivity;
   dest2[2] = (float)accel_bias[2]/(float)accelsensitivity;
}

void MPU9250SelfTest(float * destination)
{
   uint8_t rawData[6] = {0, 0, 0, 0, 0, 0};
   uint8_t selfTest[6];
    int32_t gAvg[3] = {0}, aAvg[3] = {0}, aSTAvg[3] = {0}, gSTAvg[3] = {0};
   float factoryTrim[6];
   uint8_t FS = 0;
   
  
  writeByte(MPU9250_ADDRESS, SMPLRT_DIV, 0x00);
  writeByte(MPU9250_ADDRESS, CONFIG, 0x02);
  writeByte(MPU9250_ADDRESS, GYRO_CONFIG, FS<<3);
  writeByte(MPU9250_ADDRESS, ACCEL_CONFIG2, 0x02);
  writeByte(MPU9250_ADDRESS, ACCEL_CONFIG, FS<<3);
  for( int ii = 0; ii < 200; ii++) {
  
  readBytes(MPU9250_ADDRESS, ACCEL_XOUT_H, 6, &rawData[0]);
  aAvg[0] += (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]) ;
  aAvg[1] += (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]) ;
  aAvg[2] += (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]) ;
  

  
    readBytes(MPU9250_ADDRESS, GYRO_XOUT_H, 6, &rawData[0]);
  gAvg[0] += (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]) ;
  gAvg[1] += (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]) ;
  gAvg[2] += (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]) ;
  }
  
  for (int ii =0; ii < 3; ii++) {
  aAvg[ii] /= 200;
  gAvg[ii] /= 200;
  }
  
   writeByte(MPU9250_ADDRESS, ACCEL_CONFIG, 0xE0);
   writeByte(MPU9250_ADDRESS, GYRO_CONFIG, 0xE0);
   wait_ms(25);
  for( int ii = 0; ii < 200; ii++) {
  
  readBytes(MPU9250_ADDRESS, ACCEL_XOUT_H, 6, &rawData[0]);
  aSTAvg[0] += (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]) ;
  aSTAvg[1] += (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]) ;
  
  aSTAvg[2] += (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]) ;
  
  
    readBytes(MPU9250_ADDRESS, GYRO_XOUT_H, 6, &rawData[0]);
  gSTAvg[0] += (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]) ;
  gSTAvg[1] += (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]) ;
  gSTAvg[2] += (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]) ;
  }
  
  for (int ii =0; ii < 3; ii++) {
  aSTAvg[ii] /= 200;
  gSTAvg[ii] /= 200;
  }
   writeByte(MPU9250_ADDRESS, ACCEL_CONFIG, 0x00);
   writeByte(MPU9250_ADDRESS, GYRO_CONFIG, 0x00);
   wait_ms(25);
   
   selfTest[0] = readByte(MPU9250_ADDRESS, SELF_TEST_X_ACCEL);
   selfTest[1] = readByte(MPU9250_ADDRESS, SELF_TEST_Y_ACCEL);
   selfTest[2] = readByte(MPU9250_ADDRESS, SELF_TEST_Z_ACCEL);
   
   selfTest[3] = readByte(MPU9250_ADDRESS, SELF_TEST_X_GYRO);
   
   selfTest[4] = readByte(MPU9250_ADDRESS, SELF_TEST_Y_GYRO);
   
   selfTest[5] = readByte(MPU9250_ADDRESS, SELF_TEST_Z_GYRO); 
   
   factoryTrim[0] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[0] - 1.0) ));
   factoryTrim[1] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[1] - 1.0) )); 
   factoryTrim[2] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[2] - 1.0) )); 
   factoryTrim[3] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[3] - 1.0) )); 
   factoryTrim[4] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[4] - 1.0) ));  
   factoryTrim[5] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[5] - 1.0) )); 
   for (int i = 0; i < 3; i++) {
     
     destination[i] = 100.0*((float)(aSTAvg[i] - aAvg[i]))/factoryTrim[i] - 100.;
     destination[i+3] = 100.0*((float)(gSTAvg[i] - gAvg[i]))/factoryTrim[i+3] - 100.; 
   }
   
}
        void MadgwickQuaternionUpdate(float ax, float ay, float az, float gx, float gy, float gz, float mx, float my, float mz)
        {
            float q1 = q[0], q2 = q[1], q3 = q[2], q4 = q[3];  
            float norm;
            float hx, hy, _2bx, _2bz;
            float s1, s2, s3, s4;
            float qDot1, qDot2, qDot3, qDot4;

            float _2q1mx;
            float _2q1my;
            float _2q1mz;
            float _2q2mx;
            float _4bx;
            float _4bz;
            float _2q1 = 2.0f * q1;
            float _2q2 = 2.0f * q2;
            float _2q3 = 2.0f * q3;
            float _2q4 = 2.0f * q4;
            float _2q1q3 = 2.0f * q1 * q3;
            float _2q3q4 = 2.0f * q3 * q4;
            float q1q1 = q1 * q1;
            float q1q2 = q1 * q2;
            float q1q3 = q1 * q3;
            float q1q4 = q1 * q4;
            float q2q2 = q2 * q2;
            float q2q3 = q2 * q3;
            float q2q4 = q2 * q4;
            float q3q3 = q3 * q3;
            float q3q4 = q3 * q4;
            float q4q4 = q4 * q4;

            norm = sqrt(ax * ax + ay * ay + az * az);
            if (norm == 0.0f) return; 
            norm = 1.0f/norm;
            ax *= norm;
            ay *= norm;
            az *= norm;

            norm = sqrt(mx * mx + my * my + mz * mz);
            if (norm == 0.0f) return;
            norm = 1.0f/norm;
            mx *= norm;
            my *= norm;
            mz *= norm;

            _2q1mx = 2.0f * q1 * mx;
            _2q1my = 2.0f * q1 * my;
            _2q1mz = 2.0f * q1 * mz;
            _2q2mx = 2.0f * q2 * mx;
            hx = mx * q1q1 - _2q1my * q4 + _2q1mz * q3 + mx * q2q2 + _2q2 * my * q3 + _2q2 * mz * q4 - mx * q3q3 - mx * q4q4;
            hy = _2q1mx * q4 + my * q1q1 - _2q1mz * q2 + _2q2mx * q3 - my * q2q2 + my * q3q3 + _2q3 * mz * q4 - my * q4q4;
            _2bx = sqrt(hx * hx + hy * hy);
            _2bz = -_2q1mx * q3 + _2q1my * q2 + mz * q1q1 + _2q2mx * q4 - mz * q2q2 + _2q3 * my * q4 - mz * q3q3 + mz * q4q4;
            _4bx = 2.0f * _2bx;
            _4bz = 2.0f * _2bz;
            s1 = -_2q3 * (2.0f * q2q4 - _2q1q3 - ax) + _2q2 * (2.0f * q1q2 + _2q3q4 - ay) - _2bz * q3 * (_2bx * (0.5f - q3q3 - q4q4) + _2bz * (q2q4 - q1q3) - mx) + (-_2bx * q4 + _2bz * q2) * (_2bx * (q2q3 - q1q4) + _2bz * (q1q2 + q3q4) - my) + _2bx * q3 * (_2bx * (q1q3 + q2q4) + _2bz * (0.5f - q2q2 - q3q3) - mz);
            s2 = _2q4 * (2.0f * q2q4 - _2q1q3 - ax) + _2q1 * (2.0f * q1q2 + _2q3q4 - ay) - 4.0f * q2 * (1.0f - 2.0f * q2q2 - 2.0f * q3q3 - az) + _2bz * q4 * (_2bx * (0.5f - q3q3 - q4q4) + _2bz * (q2q4 - q1q3) - mx) + (_2bx * q3 + _2bz * q1) * (_2bx * (q2q3 - q1q4) + _2bz * (q1q2 + q3q4) - my) + (_2bx * q4 - _4bz * q2) * (_2bx * (q1q3 + q2q4) + _2bz * (0.5f - q2q2 - q3q3) - mz);
            s3 = -_2q1 * (2.0f * q2q4 - _2q1q3 - ax) + _2q4 * (2.0f * q1q2 + _2q3q4 - ay) - 4.0f * q3 * (1.0f - 2.0f * q2q2 - 2.0f * q3q3 - az) + (-_4bx * q3 - _2bz * q1) * (_2bx * (0.5f - q3q3 - q4q4) + _2bz * (q2q4 - q1q3) - mx) + (_2bx * q2 + _2bz * q4) * (_2bx * (q2q3 - q1q4) + _2bz * (q1q2 + q3q4) - my) + (_2bx * q1 - _4bz * q3) * (_2bx * (q1q3 + q2q4) + _2bz * (0.5f - q2q2 - q3q3) - mz);
            s4 = _2q2 * (2.0f * q2q4 - _2q1q3 - ax) + _2q3 * (2.0f * q1q2 + _2q3q4 - ay) + (-_4bx * q4 + _2bz * q2) * (_2bx * (0.5f - q3q3 - q4q4) + _2bz * (q2q4 - q1q3) - mx) + (-_2bx * q1 + _2bz * q3) * (_2bx * (q2q3 - q1q4) + _2bz * (q1q2 + q3q4) - my) + _2bx * q2 * (_2bx * (q1q3 + q2q4) + _2bz * (0.5f - q2q2 - q3q3) - mz);
            norm = sqrt(s1 * s1 + s2 * s2 + s3 * s3 + s4 * s4);   
            norm = 1.0f/norm;
            s1 *= norm;
            s2 *= norm;
            s3 *= norm;
            s4 *= norm;

            qDot1 = 0.5f * (-q2 * gx - q3 * gy - q4 * gz) - beta * s1;
            qDot2 = 0.5f * (q1 * gx + q3 * gz - q4 * gy) - beta * s2;
            qDot3 = 0.5f * (q1 * gy - q2 * gz + q4 * gx) - beta * s3;
            qDot4 = 0.5f * (q1 * gz + q2 * gy - q3 * gx) - beta * s4;

            q1 += qDot1 * deltat;
            q2 += qDot2 * deltat;
            q3 += qDot3 * deltat;
            q4 += qDot4 * deltat;
            norm = sqrt(q1 * q1 + q2 * q2 + q3 * q3 + q4 * q4);  
            norm = 1.0f/norm;
            q[0] = q1 * norm;
            q[1] = q2 * norm;
            q[2] = q3 * norm;
            q[3] = q4 * norm;

        }

        void MahonyQuaternionUpdate(float ax, float ay, float az, float gx, float gy, float gz, float mx, float my, float mz)
        {
            float q1 = q[0], q2 = q[1], q3 = q[2], q4 = q[3];
            float norm;
            float hx, hy, bx, bz;
            float vx, vy, vz, wx, wy, wz;
            float ex, ey, ez;
            float pa, pb, pc;

            float q1q1 = q1 * q1;
            float q1q2 = q1 * q2;
            float q1q3 = q1 * q3;
            float q1q4 = q1 * q4;
            float q2q2 = q2 * q2;
            float q2q3 = q2 * q3;
            float q2q4 = q2 * q4;
            float q3q3 = q3 * q3;
            float q3q4 = q3 * q4;
            float q4q4 = q4 * q4;   

            norm = sqrt(ax * ax + ay * ay + az * az);
            if (norm == 0.0f) return; 
            norm = 1.0f / norm;       
            ax *= norm;
            ay *= norm;
            az *= norm;

            norm = sqrt(mx * mx + my * my + mz * mz);
            if (norm == 0.0f) return;
            norm = 1.0f / norm;
            mx *= norm;
            my *= norm;
            mz *= norm;
            hx = 2.0f * mx * (0.5f - q3q3 - q4q4) + 2.0f * my * (q2q3 - q1q4) + 2.0f * mz * (q2q4 + q1q3);
            hy = 2.0f * mx * (q2q3 + q1q4) + 2.0f * my * (0.5f - q2q2 - q4q4) + 2.0f * mz * (q3q4 - q1q2);
            bx = sqrt((hx * hx) + (hy * hy));
            bz = 2.0f * mx * (q2q4 - q1q3) + 2.0f * my * (q3q4 + q1q2) + 2.0f * mz * (0.5f - q2q2 - q3q3);
            vx = 2.0f * (q2q4 - q1q3);
            vy = 2.0f * (q1q2 + q3q4);
            vz = q1q1 - q2q2 - q3q3 + q4q4;
            wx = 2.0f * bx * (0.5f - q3q3 - q4q4) + 2.0f * bz * (q2q4 - q1q3);
            wy = 2.0f * bx * (q2q3 - q1q4) + 2.0f * bz * (q1q2 + q3q4);
            wz = 2.0f * bx * (q1q3 + q2q4) + 2.0f * bz * (0.5f - q2q2 - q3q3);  
            ex = (ay * vz - az * vy) + (my * wz - mz * wy);
            ey = (az * vx - ax * vz) + (mz * wx - mx * wz);
            ez = (ax * vy - ay * vx) + (mx * wy - my * wx);
            if (Ki > 0.0f)
            {
                eInt[0] += ex;     
                eInt[1] += ey;
                eInt[2] += ez;
            }
            else
            {
                eInt[0] = 0.0f;     
                eInt[1] = 0.0f;
                eInt[2] = 0.0f;
            }
 
            gx = gx + Kp * ex + Ki * eInt[0];
            gy = gy + Kp * ey + Ki * eInt[1];
            gz = gz + Kp * ez + Ki * eInt[2];

          
            pa = q2;
            pb = q3;
            pc = q4;
            q1 = q1 + (-q2 * gx - q3 * gy - q4 * gz) * (0.5f * deltat);
            q2 = pa + (q1 * gx + pb * gz - pc * gy) * (0.5f * deltat);
            q3 = pb + (q1 * gy - pa * gz + pc * gx) * (0.5f * deltat);
            q4 = pc + (q1 * gz + pa * gy - pb * gx) * (0.5f * deltat);
 
            norm = sqrt(q1 * q1 + q2 * q2 + q3 * q3 + q4 * q4);
            norm = 1.0f / norm;
            q[0] = q1 * norm;
            q[1] = q2 * norm;
            q[2] = q3 * norm;
            q[3] = q4 * norm;
 
        }
  };
#endif
