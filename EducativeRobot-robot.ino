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
                    
                    //int lspeed = Serial.parseInt();
                    //int rspeed = Serial.parseInt();
                    
                    if(subcmd == 1){
                        Serial.println(F("Moving forward"));
                        compiler.leftMotor->move(DIDACTIC_MAP_BLOCK_SIZE, ROBOT_SPEED);
                        compiler.rightMotor->move(DIDACTIC_MAP_BLOCK_SIZE, ROBOT_SPEED);
                        //compiler.leftMotor->move(DIDACTIC_MAP_BLOCK_SIZE, lspeed);
                        //compiler.rightMotor->move(DIDACTIC_MAP_BLOCK_SIZE, rspeed);
                    }else if(subcmd == 2){
                        Serial.println(F("Moving backward"));
                        compiler.leftMotor->move(-DIDACTIC_MAP_BLOCK_SIZE, ROBOT_SPEED);
                        compiler.rightMotor->move(-DIDACTIC_MAP_BLOCK_SIZE, ROBOT_SPEED);
                        //compiler.leftMotor->move(-DIDACTIC_MAP_BLOCK_SIZE, lspeed);
                        //compiler.rightMotor->move(-DIDACTIC_MAP_BLOCK_SIZE, rspeed);
                    }else if(subcmd == 3){
                        Serial.println(F("Moving left"));
                        compiler.leftMotor->move(-CM_TO_ROTATE_90, ROBOT_TURN_SPEED);
                        compiler.rightMotor->move(CM_TO_ROTATE_90, ROBOT_TURN_SPEED);
                        //compiler.leftMotor->move(-CM_TO_ROTATE_90, lspeed);
                        //compiler.rightMotor->move(CM_TO_ROTATE_90, rspeed);
                    }else if(subcmd == 4){
                        Serial.println(F("Moving right"));
                        compiler.leftMotor->move(CM_TO_ROTATE_90, ROBOT_TURN_SPEED);
                        compiler.rightMotor->move(-CM_TO_ROTATE_90, ROBOT_TURN_SPEED);
                        //compiler.leftMotor->move(CM_TO_ROTATE_90, lspeed);
                        //compiler.rightMotor->move(-CM_TO_ROTATE_90, rspeed);
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
            case 'K': 
                {
                    int subk = Serial.parseInt();
                    if(subk == 1){
                        double kp = (double) Serial.parseFloat();
                        double ki = (double) Serial.parseFloat();
                        double kd = (double) Serial.parseFloat();
                        compiler.leftMotor->speedPID->SetTunings(kp,ki,kd);
                        Serial.print(F("Setting LEFT PID tunning: "));
                        Serial.print(kp);
                        Serial.print(F(", "));
                        Serial.print(ki);
                        Serial.print(F(", "));
                        Serial.println(kd);
                    }else if(subk == 2){
                        double kp = (double) Serial.parseFloat();
                        double ki = (double) Serial.parseFloat();
                        double kd = (double) Serial.parseFloat();
                        compiler.rightMotor->speedPID->SetTunings(kp,ki,kd);
                        Serial.print(F("Setting RIGHT PID tunning: "));
                        Serial.print(kp);
                        Serial.print(F(", "));
                        Serial.print(ki);
                        Serial.print(F(", "));
                        Serial.println(kd);
                    }
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