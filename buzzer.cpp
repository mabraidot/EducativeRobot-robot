#include <Arduino.h>
#include "config.h"
#include "buzzer.h"


void Buzzer::init(void){
    pinMode(BUZZER, OUTPUT);
}


void Buzzer::_note(byte index, uint16_t frequency, uint32_t duration){
    
    if(index == _melody_index){

        if(frequency) tone(BUZZER, frequency);
        
        if(micros() > (_previous_time + duration)){
            if(frequency) noTone(BUZZER);
            _previous_time = micros();
            _melody_index++;
        }

    }
}


void Buzzer::stopSound(void){
    _previous_time = 0;
    noTone(BUZZER);
}


void Buzzer::startSound(void){
    _melody_index = 0;
    _previous_time = micros();
}


// Blocking sound, using delay
void Buzzer::error(void){
    
    if(!SILENT){
        startSound();

        tone(BUZZER, 1250, 200);
        delay(250);
        tone(BUZZER, 1250, 200);
        delay(250);
        tone(BUZZER, 250, 500);
        delay(500);
        noTone(BUZZER);
    }

}


// Blocking sound, using delay
void Buzzer::startUp(void){
    
    if(!SILENT){
        startSound();
        
        for(byte i = 0; i < 20; i+=2){
            //_note(i, 1500*sqrt((double)i), 200000/sqrt((double)i));
            //_note(i+1, 0, 50000/sqrt((double)i));
            tone(BUZZER, 1500*sqrt((double)i), 200/sqrt((double)i));
            delay(250/sqrt((double)i));
            noTone(BUZZER);
        }
    }
    

}
