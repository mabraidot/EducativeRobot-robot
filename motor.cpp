#include <Arduino.h>
#include "config.h"
#include "debug.h"
#include "motor.h"


/*void Motor::init(int encoder_pin, int motor_pin, int forward_speed, int backward_speed){

    encoder = new Encoder();
    
    servo = new SoftwareServo();
    servo->setMinimumPulse(1200);
    servo->setMaximumPulse(1800);

    _pin = motor_pin;
    _forward_speed = forward_speed;
    _backward_speed = backward_speed;
    
    encoder->init(encoder_pin);

}*/
void Motor::init(int encoder_pin, int input1, int input2){

    speedPID = new PID(&_PID_input, &_PID_output, &_PID_setpoint,1,1,0, DIRECT);
    encoder = new Encoder();

    _pin1 = input1;
    _pin2 = input2;
    pinMode(input1, OUTPUT);
    pinMode(input2, OUTPUT);
    analogWrite(input1, 0);
    analogWrite(input2, 0);

    speedPID->SetSampleTime(MOTOR_PID_SAMPLE_TIME);
    //speedPID->SetOutputLimits(140,255);
    speedPID->SetMode(MANUAL);

    encoder->init(encoder_pin);

}


bool Motor::finished(void){
    if(abs(_position) - encoder->getSteps() <= 1){
        return true;
    }else{
        return false;
    }
}


//void Motor::move(double new_position){
void Motor::move(double new_position, byte rpm){
    
    new_position = (double) new_position * (double) ENCODER_STEPS_X_CM;

    if(_position != new_position){
        stop();
        _PID_setpoint = (double) rpm;
        _position = abs(new_position);
        _position_direction = new_position/abs(new_position);
        //servo->attach(_pin);
        encoder->clear();
    }
}


void Motor::stop(void){

    speedPID->SetMode(MANUAL);
    encoder->clear();

    _PWM = 0;
    _PID_input = 0;
    _PID_output = 0;
    _PID_setpoint = 0;
    _position = 0;
    _position_direction = 1;
    //servo->detach();
    analogWrite(_pin1, LOW);
    analogWrite(_pin2, LOW);
}


void Motor::run(){

    if(finished() || _position <= 0){
        stop();
    }else{

        unsigned long steps = encoder->getSteps();
        _PID_input = (double) encoder->getRPM();

        if( steps > (_position*0.8) ){
            _PID_setpoint = ROBOT_SPEED / 2;
        }

        speedPID->SetMode(AUTOMATIC);
        speedPID->Compute();
        _PWM = (int) abs(_PID_output);
        //_PWM = (int) _PID_setpoint;

        if(_position_direction < 0){    // Backward
            analogWrite(_pin1, _PWM);
            analogWrite(_pin2, 0);
        }else{                          // Forward
            analogWrite(_pin1, 0);
            analogWrite(_pin2, _PWM);
        }

        if(DEBUG){
            static int serial_timelapse = 20;
            static unsigned long serial_timeout = millis() + serial_timelapse;
            if(serial_timeout < millis()){
                serial_timeout = millis() + serial_timelapse;
                
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
            }
        }

        /*if(_position_direction > 0){
            _PWM = _forward_speed;
        }else{
            _PWM = _backward_speed;
        }
        servo->write(_PWM);
        servo->refresh();

        if(DEBUG){
            static int serial_timelapse = 50;
            static unsigned long serial_timeout = millis() + serial_timelapse;
            if(serial_timeout < millis()){
                
                serial_timeout = millis() + serial_timelapse;

                debug.print((_forward_speed > _backward_speed) ? "LEFT " : "RIGHT ");
                debug.print("\t| Steps target: ");
                debug.print(_position);
                debug.print("\t| Steps: ");
                debug.print((double)encoder->getSteps());
                debug.print("\t| RPM: ");
                debug.print((double)encoder->getRPM());
                debug.print("\t| _PWM: ");
                debug.print((double)_PWM);
                debug.println("");
                
            }
        }
        */

    }

}
