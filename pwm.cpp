#include <Arduino.h>
#include "config.h"
#include "pwm.h"

void PWM::setPins(int pins[]){
    
    memset(_pwmPins,0,sizeof(_pwmPins));
    
    for(int i = 0; i < MOTOR_PWM_PINS_QTY; i++){
        if(pins[i]){
            _pwmPins[i].pin = pins[i];
            _pwmPins[i].pinState = true;
            _pwmPins[i].pwmTickCount = 0;
            //pinMode(_pwmPins[i].pin, OUTPUT);
        }
    }
}


void PWM::handlePWM(int pin, int value){
    for(int i = 0; i < MOTOR_PWM_PINS_QTY; i++){
        if(_pwmPins[i].pin == pin){
            
            if(micros() - _previousMicros >= MOTOR_PWM_FREQUENCY){
                _pwmPins[i].pwmTickCount++;
    
                if(_pwmPins[i].pinState == true){
                    if (_pwmPins[i].pwmTickCount >= value) {
                        _pwmPins[i].pinState = false;
                    }
                }else{
                    if (_pwmPins[i].pwmTickCount >= 255) {
                        _pwmPins[i].pinState = true;
                        _pwmPins[i].pwmTickCount = 0;
                    }
                }
                digitalWrite(_pwmPins[i].pin, _pwmPins[i].pinState);
                _previousMicros = micros();
            }

        }
    }
}