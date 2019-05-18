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
    
    /*_micros += ENCODER_ISR_QUERY_INTERVAL;
    if(_micros > ENCODER_RPM_QUERY_INTERVAL){
        _RPM = (float) (_RPM_counter * 60 * 1000 * 1000) / (ENCODER_HOLES * ENCODER_RPM_QUERY_INTERVAL);
        _RPM_counter = 0;
        _micros = 0;
    }*/
    
    // DEBOUNCING
    // http://www.embedded.com/electronics-blogs/break-points/4024981/My-favorite-software-debouncers
    /*_state = (_state << 1) | !digitalRead(_pin) | 0xe000;
    if(_state == 0xf000){
        _RPM_counter++;
        _steps++;
    }*/
    
    _micros += ENCODER_ISR_QUERY_INTERVAL;
    if(_RPM_counter >= TICKS_RPM_COUNTER){
        _RPM = (float) (_RPM_counter * 60 * 1000 * 1000) / (ENCODER_HOLES * _micros);
        _RPM_counter = 0;
        _micros = 0;
    }
    
    // NO DEBOUNCING
    // RPM counts rising and falling edge for twice precision.
    if(digitalRead(_pin) != _state){
        _state = digitalRead(_pin);
        _RPM_counter++;
        //if(_state == LOW){
            _steps++;
        //}
    }


}