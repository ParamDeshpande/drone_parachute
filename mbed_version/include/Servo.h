#ifndef MBED_SERVO_H
#define MBED_SERVO_H

#include "mbed.h"

class Servo {

public:
    Servo(PinName pin);
    void write(float percent);
    float read();
    void position(float degrees);
    void calibrate(float range = 0.0005, float degrees = 45.0); 
    Servo& operator= (float percent);
    Servo& operator= (Servo& rhs);
    operator float();

protected:
    PwmOut _pwm;
    float _range;
    float _degrees;
    float _p;
};

#endif
