#ifndef IMU_H
#define IMU_H

void imu_init(void);
void refresh_imu(void);
void check_state(void);

extern bool FREEFALL_MAYDAY ; 

#endif // !IMU_H
