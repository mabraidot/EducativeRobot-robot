#include <TimerOne.h>
#include "config.h"
#include "debug.h"
#include "buzzer.h"
#include "compiler.h"
#include "rf.h"
#include "encoder.h"
#include "light.h"
#include "motor.h"


Buzzer buzzer;
Compiler compiler;
RF rf;
Light light;
Motor leftMotor = Motor();
Motor rightMotor = Motor();

void help(){
  debug.println(F("\nCONSOLE INTERFACE"));
  debug.println(F("Available commands:"));
  debug.println(F(""));
  debug.println(F("H: This help"));
  debug.println(F("M<cm_left>,<cm_right>,<speed>: Move Motors"));
  debug.println(F("L<red>,<yellow>,<blue>: Turn on LEDs"));
}


void process_serial(){
    if(DEBUG){
        char cmd = Serial.read();
        if (cmd > 'Z') cmd -= 32;
        switch (cmd) {
            case 'H': help(); break;
            case 'M': 
                {
                    int cml = (int) Serial.parseInt();
                    int cmr = (int) Serial.parseInt();
                    byte speed = (byte) Serial.parseInt();
                    leftMotor.move(cml, speed);
                    rightMotor.move(cmr, speed);
                }
                break;
            case 'L': 
                {
                    bool red = Serial.parseInt();
                    bool yellow = Serial.parseInt();
                    bool blue = Serial.parseInt();
                    light.led(LIGHT_RED, red);
                    light.led(LIGHT_YELLOW, yellow);
                    light.led(LIGHT_BLUE, blue);
                }
                break;
            
        }
        while (Serial.read() != 10); // dump extra characters till LF is seen (you can use CRLF or just LF)
    }
}


void timerISR(void){
    Timer1.detachInterrupt();

    leftMotor.encoder->timerInterrupt();
    rightMotor.encoder->timerInterrupt();
    
    Timer1.attachInterrupt( timerISR );
}


void setup(){
    if(DEBUG){
        Serial.begin(9600);
    }

    rf.init();
    
    leftMotor.init(MOTOR_LEFT_ENCODER, MOTOR_LEFT_INPUT_1, MOTOR_LEFT_INPUT_2);
    rightMotor.init(MOTOR_RIGHT_ENCODER, MOTOR_RIGHT_INPUT_1, MOTOR_RIGHT_INPUT_2);

    Timer1.initialize(ENCODER_ISR_QUERY_INTERVAL);
    Timer1.attachInterrupt( timerISR );

    compiler.init();

    light.init();
    
    buzzer.init();
    buzzer.startUp();

}


void loop(){
    if (Serial.available()) process_serial();

    compiler.run();

    //leftMotor.run();
    rightMotor.run();

}