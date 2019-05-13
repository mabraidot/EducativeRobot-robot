#include <TimerOne.h>
#include "config.h"
#include "debug.h"
#include "buzzer.h"
#include "rf.h"
#include "compiler.h"

Buzzer buzzer;
Compiler compiler;
RF rf;


void help(){
  debug.println(F("\nCONSOLE INTERFACE"));
  debug.println(F("Available commands:"));
  debug.println(F(""));
  debug.println(F("H: This help"));
  debug.println(F("M<dir>: Move Motors. 1: Forward. 2: Backward. 3: Left. 4: Right"));
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
                    /*int lspeed = Serial.parseInt();
                    int rspeed = Serial.parseInt();
                    compiler.leftMotor->servo->attach(MOTOR_LEFT_INPUT);
                    compiler.rightMotor->servo->attach(MOTOR_RIGHT_INPUT);
                    compiler.leftMotor->servo->write(lspeed);
                    compiler.rightMotor->servo->write(rspeed);
                    */
                    int subcmd = Serial.parseInt();
                    if(subcmd == 1){
                        Serial.println(F("Moving forward"));
                        compiler.leftMotor->move(DIDACTIC_MAP_BLOCK_SIZE);
                        compiler.rightMotor->move(DIDACTIC_MAP_BLOCK_SIZE);
                    }else if(subcmd == 2){
                        Serial.println(F("Moving backward"));
                        compiler.leftMotor->move(-DIDACTIC_MAP_BLOCK_SIZE);
                        compiler.rightMotor->move(-DIDACTIC_MAP_BLOCK_SIZE);
                    }else if(subcmd == 3){
                        Serial.println(F("Moving left"));
                        compiler.leftMotor->move(-ENCODER_CM_TO_ROTATE_90);
                        compiler.rightMotor->move(ENCODER_CM_TO_ROTATE_90);
                    }else if(subcmd == 4){
                        Serial.println(F("Moving right"));
                        compiler.leftMotor->move(ENCODER_CM_TO_ROTATE_90);
                        compiler.rightMotor->move(-ENCODER_CM_TO_ROTATE_90);
                    }
                }
                break;
            case 'L': 
                {
                    bool red = Serial.parseInt();
                    bool yellow = Serial.parseInt();
                    bool blue = Serial.parseInt();
                    compiler.headLights(LIGHT_RED, red);
                    compiler.headLights(LIGHT_GREEN, yellow);
                    compiler.headLights(LIGHT_BLUE, blue);
                }
                break;
            
        }
        while (Serial.read() != 10); // dump extra characters till LF is seen (you can use CRLF or just LF)
    }
}


void timerISR(void){
    Timer1.detachInterrupt();

    compiler.leftMotor->encoder->timerInterrupt();
    compiler.rightMotor->encoder->timerInterrupt();
    
    Timer1.attachInterrupt( timerISR );
}


void setup(){
    if(DEBUG){
        Serial.begin(115200);
    }

    rf.init();
    compiler.init();
    
    Timer1.initialize(ENCODER_ISR_QUERY_INTERVAL);
    Timer1.attachInterrupt( timerISR );

    buzzer.init();
    buzzer.startUp();

}

void loop(){
    if (Serial.available()) process_serial();

    compiler.run();

    /// TEST ////////////////
    //compiler.leftMotor->run();
    //compiler.rightMotor->run();
    /*if(compiler.leftMotor->servo->read() > 0 || compiler.rightMotor->servo->read() > 0){
        
        static unsigned long ttt = millis() + 2000;
        if(millis() >= ttt){
            compiler.leftMotor->servo->detach();
            compiler.rightMotor->servo->detach();
            ttt = millis() + 2000;
        }
    }
    compiler.leftMotor->servo->refresh();
    compiler.rightMotor->servo->refresh();
    */
}