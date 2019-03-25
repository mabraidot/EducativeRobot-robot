#include <Arduino.h>
#include "config.h"
#include "debug.h"
#include "encoder.h"



void Encoder::init(int pin){
    _pin = pin;
    pinMode(_pin, INPUT_PULLUP);
}


uint16_t Encoder::getRPM(void){
    return (uint16_t) _RPM;
}


unsigned long Encoder::getSteps(void){
    return _steps;
}


void Encoder::clear(void){
    _RPM_counter = 0;
    _steps = 0;
}


void Encoder::timerInterrupt(void){
    
    _micros += 50; //ISR is called each 50us
    if(((_micros*1000) - _RPM_read_timeout) > ENCODER_RPM_QUERY_INTERVAL){
        _RPM = (_RPM_counter * 60 * 1000) / (ENCODER_HOLES * ENCODER_RPM_QUERY_INTERVAL);
        _RPM_counter = 0;
        
        _RPM_read_timeout = (_micros*1000) + ENCODER_RPM_QUERY_INTERVAL;
    }

    // DEBOUNCING
    // http://www.embedded.com/electronics-blogs/break-points/4024981/My-favorite-software-debouncers
    static volatile uint16_t _state = 0;
    _state = (_state << 1) | !digitalRead(_pin) | 0xe000;
    if(_state == 0xf000){
        _RPM_counter++;
        _steps++;
    }

}