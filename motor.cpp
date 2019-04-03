#include <Arduino.h>
#include "config.h"
#include "debug.h"
#include "motor.h"



void Motor::init(int encoder_pin, int input1, int input2){

    speedPID = new PID(&_PID_input, &_PID_output, &_PID_setpoint,1,1,0, DIRECT);
    encoder = new Encoder();

    _pin1 = input1;
    _pin2 = input2;
    pinMode(input1, OUTPUT);
    pinMode(input2, OUTPUT);
    analogWrite(input1, 0);
    analogWrite(input2, 0);

    speedPID->SetSampleTime(ENCODER_RPM_QUERY_INTERVAL / 8000);
    speedPID->SetOutputLimits(0,255);
    speedPID->SetMode(MANUAL);

    encoder->init(encoder_pin);

}


bool Motor::finished(void){
    if(abs(_position) - encoder->getSteps() <= 0){
        return true;
    }else{
        return false;
    }
}


void Motor::move(double new_position, byte rpm){
    
    new_position = (double) new_position * (double) ENCODER_STEPS_X_CM;

    if(_position != new_position){
        stop();
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

    analogWrite(_pin1, LOW);
    analogWrite(_pin2, LOW);

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
        
        
        if(DEBUG){
            static int serial_timelapse = 200;
            static unsigned long serial_timeout = millis() + serial_timelapse;
            if(serial_timeout < millis()){
                
                debug.print("Steps setpoint: ");
                debug.print(_position);
                debug.print("\t| Steps: ");
                debug.print((double)steps);
                debug.print("\t| _PWM: ");
                debug.print((byte)_PWM);
                debug.print("\t| RPM setpoint: ");
                debug.print(_PID_setpoint);
                debug.print("\t| RPM: ");
                debug.println(_PID_input);
                
                serial_timeout = millis() + serial_timelapse;
            }
        }

        if(_position_direction < 0){    // Backward
            analogWrite(_pin1, _PWM);
            analogWrite(_pin2, 0);
        }else{                          // Forward
            analogWrite(_pin1, 0);
            analogWrite(_pin2, _PWM);
        }

    }

}
