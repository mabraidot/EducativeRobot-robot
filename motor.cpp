#include <Arduino.h>
#include "config.h"
#include "debug.h"
#include "motor.h"


void Motor::init(int encoder_pin, int motor_pin, int forward_speed, int backward_speed){

    encoder = new Encoder();
    
    servo = new SoftwareServo();
    servo->setMinimumPulse(1200);
    servo->setMaximumPulse(1800);

    _pin = motor_pin;
    _forward_speed = forward_speed;
    _backward_speed = backward_speed;
    
    encoder->init(encoder_pin);

}


bool Motor::finished(void){
    if(abs(_position) - encoder->getSteps() <= 0){
        return true;
    }else{
        return false;
    }
}


void Motor::move(double new_position){
    
    new_position = (double) new_position * (double) ENCODER_STEPS_X_CM;

    if(_position != new_position){
        stop();
        _position = abs(new_position);
        _position_direction = new_position/abs(new_position);
        servo->attach(_pin);
        encoder->clear();
    }
}


void Motor::stop(void){

    encoder->clear();

    _PWM = 0;
    _position = 0;
    _position_direction = 1;
    servo->detach();
}


void Motor::run(){

    if(finished() || _position <= 0){
        stop();
    }else{

        unsigned long steps = encoder->getSteps();
        
        if(_position_direction > 0){
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
    }

}
