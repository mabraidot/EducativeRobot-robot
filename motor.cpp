#include <Arduino.h>
#include "config.h"
#include "debug.h"
#include "motor.h"


void Motor::init(int encoder_pin, int motor_pin, bool inverse){

    //speedPID = new PID(&_PID_input, &_PID_output, &_PID_setpoint,1,1,0, DIRECT);
    encoder = new Encoder();
    servo = new ServoTimer2();

    _inverse = (inverse) ? -1 : 1;
    _pin = motor_pin;
    
    /*speedPID->SetSampleTime(ENCODER_RPM_QUERY_INTERVAL / 1000);
    speedPID->SetOutputLimits(SERVO_MIN_SPEED, SERVO_MAX_SPEED);
    speedPID->SetMode(MANUAL);
    */
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
        //_PID_input = (double) encoder->getRPM();
        
        _PWM = SERVO_ZERO_SPEED + (SERVO_MAX_SPEED * _position_direction * _inverse);
        servo->write(_PWM);

        if(DEBUG && _inverse < 0){
            static int serial_timelapse = 100;
            static unsigned long serial_timeout = millis() + serial_timelapse;
            if(serial_timeout < millis()){
                
                serial_timeout = millis() + serial_timelapse;

                debug.print("\t| Steps setpoint: ");
                debug.print(_position);
                debug.print("\t| Steps: ");
                debug.print((double)steps);
                debug.print("\t| _PWM: ");
                debug.print((double)_PWM);
                debug.println("");
            }
            
        }
    }

}
