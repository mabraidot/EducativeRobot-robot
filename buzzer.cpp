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


void Buzzer::toneMatrix(byte theme, byte repetitions = 1){
    char tone_notes[5][5] = {
        " ",
        "cCA ",
        "abcd",
        "AdAd",
        "f A "
    }; // a space represents a rest
    int tone_beats[5][4] = {
        { 0 },
        { 4,6,10,8 },
        { 4,4,4,4 },
        { 8,4,8,4 },
        { 8,4,8,4 }
    };
    int tone_tempo = 80;

    byte tone_matrix_size = (sizeof(tone_notes) / sizeof(tone_notes[0])) - 1;
    char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C', 'A' }; 
    int tones[] = { 2110, 1880, 1675, 1581, 1409, 1255, 1118, 1055, 1184 };

    for (int j = 0; j < repetitions; j++) {
        for (int i = 0; i < tone_matrix_size; i++) {
            if (tone_notes[theme][i] == ' ') {
                delay(tone_beats[theme][i] * tone_tempo); // rest
            } else {
                for (int k = 0; k < sizeof(names); k++) {
                    if (names[k] == tone_notes[theme][i]) {
                        //playToneMatrix(tones[i], tone_beats[theme][i] * tone_tempo);
                        tone(BUZZER, tones[k], tone_beats[theme][i] * tone_tempo);
                        delay(tone_beats[theme][i] * tone_tempo * 1.2);
                    }
                }
                noTone(BUZZER);
            }
        }
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
