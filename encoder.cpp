#include <Arduino.h>
#include "config.h"
#include "debug.h"
#include "encoder.h"



void Encoder::init(int pin){
    _pin = pin;
    pinMode(_pin, INPUT);
}


uint16_t Encoder::getRPM(void){
    return _RPM;
}


unsigned long Encoder::getSteps(void){
    return _steps;
}


void Encoder::timerInterrupt(void){
    
    if(_read_timeout < millis()){

        _RPM = (60 * 1000 / ENCODER_HOLES ) / ENCODER_QUERY_INTERVAL * _RPM_counter;
        _RPM_counter = 0;

        _read_timeout = millis() + ENCODER_QUERY_INTERVAL;
    }

    // DEBOUNCING
    // http://www.embedded.com/electronics-blogs/break-points/4024981/My-favorite-software-debouncers
    static uint16_t state = 0;
    state = (state << 1) | !digitalRead(_pin) | 0xe000;
    if(state == 0xf000){
        _RPM_counter++;
        _steps++;
    }

}