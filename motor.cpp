#include <Arduino.h>
#include "config.h"
#include "debug.h"
#include "motor.h"


Motor::Motor(int encoder_pin, int input1, int input2){

    pinMode(input1, OUTPUT);
    pinMode(input2, OUTPUT);

    PID speedPID = PID(&_PID_input, &_PID_output, &_PID_setpoint,1,1,0, DIRECT);
    speedPID.SetSampleTime(50);
    speedPID.SetOutputLimits(0,255);
    speedPID.SetMode(MANUAL);
    speedPID.SetTunings(MOTOR_PID_kP, MOTOR_PID_kI, MOTOR_PID_kD);

    Encoder encoder = Encoder();
    encoder.init(encoder_pin);

    
}