#include <Arduino.h>
#include "config.h"
#include "debug.h"
#include "motor.h"
#include "pwm.h"

Motor::Motor(void){

    speedPID = new PID(&_PID_input, &_PID_output, &_PID_setpoint,1,1,0, DIRECT);
    encoder = new Encoder();

}


void Motor::init(int encoder_pin, int input1, int input2){

    _pin1 = input1;
    _pin2 = input2;
    pinMode(input1, OUTPUT);
    pinMode(input2, OUTPUT);
    analogWrite(input1, 0);
    analogWrite(input2, 0);

    speedPID->SetSampleTime(50);
    speedPID->SetOutputLimits(0,255);
    speedPID->SetMode(MANUAL);
    speedPID->SetTunings(MOTOR_PID_kP, MOTOR_PID_kI, MOTOR_PID_kD);

    encoder->init(encoder_pin);

}


bool Motor::finished(void){
    if(abs(_position - encoder->getSteps()) <= _position_accuracy){
        return true;
    }else{
        return false;
    }
}


void Motor::move(int new_position, byte rpm){
    
    new_position = (double) new_position * ENCODER_STEPS_X_CM;

    if(_position != new_position){
        stop();
        encoder->clear();
        _PID_setpoint = (double) rpm * WHEEL_GEAR_RATIO;
        _position = abs(new_position);
        _position_direction = new_position/abs(new_position);
    }

}


void Motor::stop(void){

    speedPID->SetMode(MANUAL);
    encoder->clear();

    _PID_input = 0;
    _PID_output = 0;
    _PWM = 0;
    _PID_setpoint = 0;
    _position = 0;
    _position_direction = 1;

    analogWrite(_pin1, 0);
    analogWrite(_pin2, 0);

}


void Motor::run(void){

    if(finished() || _position <= 0){
        stop();
    }else{

        unsigned long steps = encoder->getSteps();
        _PID_input = (double) encoder->getRPM();
        speedPID->SetMode(AUTOMATIC);
        speedPID->Compute();
        _PWM = (int) abs(_PID_output);

        if((float)steps <= float(_position/10)){
            // If we are on the first 10% of the trajectory
            // calculate the ascendent ramp

            // @todo: modify _PWM with sigmoid function (max of _PID_setpoint)

        }else if((float)steps >= float(_position - (_position/10))){
            // If we are on the last 10% of the trajectory
            // calculate the descendent ramp

            // @todo: modify _PWM with inverted sigmoid function (max of _PID_setpoint)

        }

        static int serial_timelapse = 1000;
        static unsigned long serial_timeout = millis() + serial_timelapse;
        if(serial_timeout < millis()){
            debug.print("\nSteps setpoint: ");
            debug.print(_position);
            debug.print("\tSteps: ");
            debug.print((double)steps);
            debug.print("\t| _PWM: ");
            debug.print((byte)_PWM);
            debug.print("\t| RPM setpoint: ");
            debug.print(_PID_setpoint);
            debug.print("\tRPM: ");
            debug.println(_PID_input);
            
            serial_timeout = millis() + serial_timelapse;
        }

        if(_position_direction < 0){    // Backward
            pwm.handlePWM(_pin1, _PWM);
            digitalWrite(_pin2, LOW);
        }else{                          // Forward
            digitalWrite(_pin1, LOW);
            pwm.handlePWM(_pin2, _PWM);
        }

    }

}