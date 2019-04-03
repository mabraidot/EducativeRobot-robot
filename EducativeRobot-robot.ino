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
  debug.println(F("M<dir>,<speed>: Move Motors. 1: Forward. 2: Backward. 3: Left. 4: Right"));
  debug.println(F("L<red>,<yellow>,<blue>: Turn on LEDs"));
  debug.println(F("K<kp>,<ki>,<kd>: Sets PID gains"));
}


void process_serial(){
    if(DEBUG){
        char cmd = Serial.read();
        if (cmd > 'Z') cmd -= 32;
        switch (cmd) {
            case 'H': help(); break;
            case 'M': 
                {
                    int subcmd = Serial.parseInt();
                    //int speed = Serial.parseInt();
                    if(subcmd == 1){
                        Serial.println(F("Moving forward"));
                        compiler.moveForward();
                        //compiler.leftMotor->move(DIDACTIC_MAP_BLOCK_SIZE, speed);
                        //compiler.rightMotor->move(DIDACTIC_MAP_BLOCK_SIZE, speed);
                    }else if(subcmd == 2){
                        Serial.println(F("Moving backward"));
                        //compiler.moveBackward();
                        compiler.leftMotor->move(-DIDACTIC_MAP_BLOCK_SIZE, speed);
                        compiler.rightMotor->move(-DIDACTIC_MAP_BLOCK_SIZE, speed);
                    }else if(subcmd == 3){
                        Serial.println(F("Moving left"));
                        compiler.moveTurnLeft();
                    }else if(subcmd == 4){
                        Serial.println(F("Moving right"));
                        compiler.moveTurnRight();
                    }
                }
                break;
            case 'L': 
                {
                    bool red = Serial.parseInt();
                    bool yellow = Serial.parseInt();
                    bool blue = Serial.parseInt();
                    compiler.headLights(LIGHT_RED, red);
                    compiler.headLights(LIGHT_YELLOW, yellow);
                    compiler.headLights(LIGHT_BLUE, blue);
                }
                break;
            case 'K': 
                {
                    double kp = (double) Serial.parseFloat();
                    double ki = (double) Serial.parseFloat();
                    double kd = (double) Serial.parseFloat();
                    compiler.leftMotor->speedPID->SetTunings(kp,ki,kd);
                    compiler.rightMotor->speedPID->SetTunings(kp,ki,kd);
                    Serial.print(F("Setting PID tunning: "));
                    Serial.print(kp);
                    Serial.print(F(", "));
                    Serial.print(ki);
                    Serial.print(F(", "));
                    Serial.println(kd);
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

}