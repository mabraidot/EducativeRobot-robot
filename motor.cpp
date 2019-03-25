#include <Arduino.h>
#include "config.h"
#include "debug.h"
#include "motor.h"
#include "encoder.h"


void Motor::Motor(Encoder &encoder, int input1, int input2) : encoder(encoder){

    pinMode(input1, OUTPUT);
    pinMode(input2, OUTPUT);

    speedPID = new PID(&_PID_input, &_PID_output, &_PID_setpoint,1,1,0, DIRECT);
    speedPID->SetSampleTime(50);
    speedPID->SetOutputLimits(0,255);
    speedPID->SetMode(MANUAL);
    speedPID->SetTunings(MOTOR_PID_kP, MOTOR_PID_kI, MOTOR_PID_kD);

    
}