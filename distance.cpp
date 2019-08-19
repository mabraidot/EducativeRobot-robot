#include <Arduino.h>
#include "config.h"
#include "distance.h"


void Distance::init(void){
    pinMode(SENSOR_ULTRASONIC_TRIGGER, OUTPUT);
    pinMode(SENSOR_ULTRASONIC_ECHO, INPUT);
}


void Distance::update(void){
    unsigned long duration = 0;
    static unsigned long sonar_timeout = millis();
    
    if(millis() - sonar_timeout <= 2){
        digitalWrite(SENSOR_ULTRASONIC_TRIGGER, LOW);
    }else if(millis() - sonar_timeout > 2 && millis() - sonar_timeout <= 7){
        digitalWrite(SENSOR_ULTRASONIC_TRIGGER, HIGH);
    }else if(millis() - sonar_timeout > 7){
        digitalWrite(SENSOR_ULTRASONIC_TRIGGER, LOW);
        duration = pulseInLong(SENSOR_ULTRASONIC_ECHO, HIGH, 5820);
        _cm = (duration / 2) / 29.1;
        sonar_timeout = millis();
    }
}


unsigned long Distance::get_distance(void){
    return _cm;
}


boolean Distance::obstacle_detected(void){
    if(get_distance() > 2 && get_distance() <= DIDACTIC_MAP_BLOCK_SIZE){
        return true;
    }else{
        return false;
    }
}

boolean Distance::imminent_colition(void){
    if(get_distance() > 0 && get_distance() <= 5){
        return true;
    }else{
        return false;
    }
}