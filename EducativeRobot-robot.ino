#include "config.h"
#include "debug.h"
#include "buzzer.h"
#include "compiler.h"
#include "rf.h"
#include "encoder.h"

Buzzer buzzer;
Compiler compiler;
RF rf;
Encoder leftEncoder;
Encoder rightEncoder;

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


void timerInterrupt(void){
    leftEncoder.timerInterrupt();
    rightEncoder.timerInterrupt();
}


void setup(){
    if(DEBUG){
        Serial.begin(9600);
    }

    Timer1.initialize(50);
    Timer1.attachInterrupt( timerInterrupt );

    rf.init();
    compiler.init();


    leftEncoder.init(MOTOR_LEFT_ENCODER);
    rightEncoder.init(MOTOR_RIGHT_ENCODER);
    
    buzzer.init();
    buzzer.startUp();
}


void loop(){
    if (Serial.available()) process_serial();

    compiler.run();

    // TEST ENCODERS
    static int serial_interval = 300;
    static unsigned long serial_timeout = millis() + serial_interval;
    if(serial_timeout < millis()){

        Serial.print("\nLeft RPM:\t");
        Serial.print(leftEncoder.getRPM());
        Serial.print("\tLeft Steps:\t");
        Serial.println(leftEncoder.getSteps());

        Serial.print("Right RPM:\t");
        Serial.print(rightEncoder.getRPM());
        Serial.print("\tRight Steps:\t");
        Serial.println(rightEncoder.getSteps());
        
        serial_timeout = millis() + serial_interval;
    }
}