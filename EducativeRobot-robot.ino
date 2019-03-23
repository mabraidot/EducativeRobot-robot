#include "config.h"
#include "debug.h"
#include "buzzer.h"
#include "compiler.h"
#include "rf.h"

Buzzer buzzer;
Compiler compiler;
RF rf;


void help(){
  debug.println(F("\nCONSOLE INTERFACE"));
  debug.println(F("Available commands:"));
  debug.println(F(""));
  debug.println(F("H: This help"));
  debug.println(F("F: Move Forward"));
  debug.println(F("B: Move Backward"));
  debug.println(F("L: Turn Left"));
  debug.println(F("R: Turn Right"));
}


void process_serial(){
    if(DEBUG){
        char cmd = Serial.read();
        byte address;
        if (cmd > 'Z') cmd -= 32;
        switch (cmd) {
            case 'H': help(); break;
            case 'F': /*move forward;*/ break;
            case 'B': /*move backward;*/ break;
            case 'L': /*move left;*/ break;
            case 'R': /*move right;*/ break;
        }
        while (Serial.read() != 10); // dump extra characters till LF is seen (you can use CRLF or just LF)
    }
}


void setup(){
    if(DEBUG){
        Serial.begin(9600);
    }
    rf.init();
    compiler.init();

    buzzer.init();
    buzzer.startUp();
}


void loop(){
    if (Serial.available()) process_serial();

    compiler.run();
}