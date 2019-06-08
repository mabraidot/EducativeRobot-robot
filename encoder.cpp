#include <Arduino.h>
#include "config.h"
#include "debug.h"
#include "encoder.h"



void Encoder::init(int pin){
    _pin = pin;
    pinMode(_pin, INPUT_PULLUP);
}


float Encoder::getRPM(void){
    return _RPM;
}


unsigned long Encoder::getSteps(void){
    return _steps;
}


void Encoder::clear(void){
    _RPM_counter = 0;
    _steps = 0;
    _micros = 0;
    _RPM = 0;
}


void Encoder::timerInterrupt(void){
    
    _micros += ENCODER_ISR_QUERY_INTERVAL;
    if(_RPM_counter >= TICKS_RPM_COUNTER){
        _RPM = (float) (_RPM_counter * 60 * 1000 * 1000) / (ENCODER_HOLES * _micros);
        _RPM_counter = 0;
        _micros = 0;
    }
    
    if(digitalRead(_pin) != _state){
        _state = digitalRead(_pin);
        _RPM_counter++;
        _steps++;
    }


}