#include <Arduino.h>
#include "config.h"
#include "debug.h"
#include "light.h"


void Light::init(void){

    pinMode(LIGHT_RED, OUTPUT);
    pinMode(LIGHT_YELLOW, OUTPUT);
    pinMode(LIGHT_BLUE, OUTPUT);

}


void Light::led(byte color, byte mode){
    
    if(mode == STATE_LED_BLINK){
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
    }

}