#include <Arduino.h>
#include "config.h"
#include "debug.h"
#include "light.h"


void Light::init(void){

	pinMode(LIGHT_RED, OUTPUT);
	pinMode(LIGHT_GREEN, OUTPUT);
	pinMode(LIGHT_BLUE, OUTPUT);
	digitalWrite(LIGHT_RED, LOW);
	digitalWrite(LIGHT_GREEN, LOW);
	digitalWrite(LIGHT_BLUE, LOW);

	memset(_pwmPins,0,sizeof(_pwmPins));

	_pwmPins[0].pin = LIGHT_RED;
	_pwmPins[0].pinMaksLow = LIGHT_RED_MASK_LOW;
	_pwmPins[0].pinMaksHigh = LIGHT_RED_MASK_HIGH;
	_pwmPins[0].pinState = false;

	_pwmPins[1].pin = LIGHT_GREEN;
	_pwmPins[1].pinMaksLow = LIGHT_GREEN_MASK_LOW;
	_pwmPins[1].pinMaksHigh = LIGHT_GREEN_MASK_HIGH;
	_pwmPins[1].pinState = false;

	_pwmPins[2].pin = LIGHT_BLUE;
	_pwmPins[2].pinMaksLow = LIGHT_BLUE_MASK_LOW;
	_pwmPins[2].pinMaksHigh = LIGHT_BLUE_MASK_HIGH;
	_pwmPins[2].pinState = false;
	
}


//void Light::led(byte red_value, byte green_value, byte blue_value, byte mode){
void Light::led(){
	
	if(_activated || _mode != STATE_LED_OFF){
		if(_mode == STATE_LED_BLINK){
			static byte led_on = 1;
			static int blink_interval = 500;
			static unsigned long blink_timeout = millis() + blink_interval;
			
			if(blink_timeout < millis()){
				led_on = !led_on;
				blink_timeout = millis() + blink_interval;
			}
			if(led_on){
				_handlePWM(LIGHT_RED, _red_value);
				_handlePWM(LIGHT_GREEN, _green_value);
				_handlePWM(LIGHT_BLUE, _blue_value);
			}else{
				_handlePWM(LIGHT_RED, 0);
				_handlePWM(LIGHT_GREEN, 0);
				_handlePWM(LIGHT_BLUE, 0);
			}
			_activated = true;
			
		}else if(_mode == STATE_LED_ON){
			_handlePWM(LIGHT_RED, _red_value);
			_handlePWM(LIGHT_GREEN, _green_value);
			_handlePWM(LIGHT_BLUE, _blue_value);
			_activated = true;
		}else{
			_handlePWM(LIGHT_RED, 0);
			_handlePWM(LIGHT_GREEN, 0);
			_handlePWM(LIGHT_BLUE, 0);
			_activated = false;
		}
	}

}


void Light::ledMatrix(byte color){
	_red_value 		= _led_matrix[color][0];
	_green_value 	= _led_matrix[color][1];
	_blue_value		= _led_matrix[color][2];
	_mode 			= STATE_LED_ON;
	_activated 		= true;
}


void Light::ledMatrixOff(void){
	_red_value 		= 0;
	_green_value 	= 0;
	_blue_value		= 0;
	_mode 			= STATE_LED_OFF;
}



void Light::updatePWMTicks(void){

	if (pwmTickCount >= 255) {
		pwmTickCount = 0;
	}else{
		pwmTickCount++;
	}

}


void Light::_handlePWM(int pin, int value){

	for(int i = 0; i < 3; i++){
		if(_pwmPins[i].pin == pin){
			
			if(_pwmPins[i].pinState == true){
				if (pwmTickCount >= value) {
					_pwmPins[i].pinState = false;
					switch(_pwmPins[i].pin){
					  case LIGHT_RED:   PORTD &= _pwmPins[i].pinMaksLow; break;
					  case LIGHT_GREEN: PORTD &= _pwmPins[i].pinMaksLow; break;
					  case LIGHT_BLUE:  PORTC &= _pwmPins[i].pinMaksLow; break;
					}
				}
			}else{
				if (pwmTickCount < value) {
					_pwmPins[i].pinState = true;
					switch(_pwmPins[i].pin){
					  case LIGHT_RED:   PORTD |= _pwmPins[i].pinMaksHigh; break;
					  case LIGHT_GREEN: PORTD |= _pwmPins[i].pinMaksHigh; break;
					  case LIGHT_BLUE:  PORTC |= _pwmPins[i].pinMaksHigh; break;
					}
				}
			}
		}
	}

}