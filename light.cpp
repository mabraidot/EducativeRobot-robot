#include <Arduino.h>
#include "config.h"
#include "debug.h"
#include "light.h"


void Light::init(void){

    pinMode(LIGHT_RED, OUTPUT);
    pinMode(LIGHT_GREEN, OUTPUT);
    pinMode(LIGHT_BLUE, OUTPUT);
    
    memset(_pwmPins,0,sizeof(_pwmPins));
    
    _pwmPins[0].pin = LIGHT_RED;
    _pwmPins[0].pinMaksLow = LIGHT_RED_MASK_LOW;
    _pwmPins[0].pinMaksHigh = LIGHT_RED_MASK_HIGH;
    _pwmPins[0].pinState = true;
    _pwmPins[0].pwmTickCount = 0;

    _pwmPins[1].pin = LIGHT_GREEN;
    _pwmPins[1].pinMaksLow = LIGHT_GREEN_MASK_LOW;
    _pwmPins[1].pinMaksHigh = LIGHT_GREEN_MASK_HIGH;
    _pwmPins[1].pinState = true;
    _pwmPins[1].pwmTickCount = 0;

    _pwmPins[2].pin = LIGHT_BLUE;
    _pwmPins[2].pinMaksLow = LIGHT_BLUE_MASK_LOW;
    _pwmPins[2].pinMaksHigh = LIGHT_BLUE_MASK_HIGH;
    _pwmPins[2].pinState = true;
    _pwmPins[2].pwmTickCount = 0;
    
}


void Light::led(byte red_value, byte green_value, byte blue_value, byte mode){
    
    /*if(mode == STATE_LED_BLINK){
      static byte led_on = 1;
      static int blink_interval = 500;
      static unsigned long blink_timeout = millis() + blink_interval;
      
      if(blink_timeout < millis()){
        led_on = !led_on;
        blink_timeout = millis() + blink_interval;
      }
      digitalWrite(color, led_on);
    }else if(mode == STATE_LED_ON){
      digitalWrite(color, 1);
    }else{
      digitalWrite(color, 0);
    }*/

    if(mode == STATE_LED_BLINK){
      static byte led_on = 1;
      static int blink_interval = 500;
      static unsigned long blink_timeout = millis() + blink_interval;
      
      if(blink_timeout < millis()){
        led_on = !led_on;
        blink_timeout = millis() + blink_interval;
      }
      if(led_on){
        _handlePWM(LIGHT_RED, red_value);
        _handlePWM(LIGHT_GREEN, green_value);
        _handlePWM(LIGHT_BLUE, blue_value);
      }

    }else if(mode == STATE_LED_ON){
      _handlePWM(LIGHT_RED, red_value);
      _handlePWM(LIGHT_GREEN, green_value);
      _handlePWM(LIGHT_BLUE, blue_value);
    }

}


void Light::updatePWMTicks(void){

  //_previousMicros += ENCODER_ISR_QUERY_INTERVAL;
  //if(_previousMicros >= 62){ // 60 Hz => 16000 / 256
    for(int i = 0; i < 3; i++){
      if (_pwmPins[i].pwmTickCount >= 255) {
        _pwmPins[i].pwmTickCount = 0;
      }else{
        _pwmPins[i].pwmTickCount++;
      }
    }
  //  _previousMicros = 0;
  //}

}

void Light::_handlePWM(int pin, int value){
    for(int i = 0; i < 3; i++){
        if(_pwmPins[i].pin == pin){
            
            /*if(micros() - _previousMicros >= 1){
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
            */
            if(_pwmPins[i].pinState == true){
                if (_pwmPins[i].pwmTickCount >= value) {
                    _pwmPins[i].pinState = false;
                    //digitalWrite(_pwmPins[i].pin, _pwmPins[i].pinState);
                    //PORTD = PORTD & B11111100
                    //PORTC = PORTC & B11101111
                    _pwmPins[i].pinMaksLow;
                }
            }else{
                if (_pwmPins[i].pwmTickCount < value) {
                    _pwmPins[i].pinState = true;
                    //digitalWrite(_pwmPins[i].pin, _pwmPins[i].pinState);
                    //PORTD = PORTD | B00000011
                    //PORTC = PORTC | B00010000
                    _pwmPins[i].pinMaksHigh;
                }
            }
            

        }
    }
}