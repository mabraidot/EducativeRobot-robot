#include <TimerOne.h>
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
  debug.println(F("MF: Move Forward"));
  debug.println(F("MB: Move Backward"));
  debug.println(F("ML: Turn Left"));
  debug.println(F("MR: Turn Right"));
}


void process_serial(){
    if(DEBUG){
        char cmd = Serial.read();
        byte address;
        if (cmd > 'Z') cmd -= 32;
        switch (cmd) {
            case 'H': help(); break;
            case 'M': 
                {
                    byte mode = Serial.read();
                    switch(mode) {
                        case 'F': /*Move forward*/ break;
                        case 'B': /*Move backward*/ break;
                        case 'L': /*Move left*/ break;
                        case 'R': /*Move right*/ break;
                    }
                }
                break;
            case 'L': 
                {
                    bool red = Serial.parseInt();
                    bool yellow = Serial.parseInt();
                    bool blue = Serial.parseInt();
                    led(red, yellow, blue); 
                }
                break;
            
        }
        while (Serial.read() != 10); // dump extra characters till LF is seen (you can use CRLF or just LF)
    }
}

void led(bool red, bool yellow, bool blue){
    digitalWrite(LIGHT_RED, red);
    digitalWrite(LIGHT_YELLOW, yellow);
    digitalWrite(LIGHT_BLUE, blue);
}


void timerISR(void){
    Timer1.detachInterrupt();

    leftEncoder.timerInterrupt();
    rightEncoder.timerInterrupt();
    
    Timer1.attachInterrupt( timerISR );
}


void setup(){
    if(DEBUG){
        Serial.begin(9600);
    }

    leftEncoder.init(MOTOR_LEFT_ENCODER);
    rightEncoder.init(MOTOR_RIGHT_ENCODER);
    Timer1.initialize(50);
    Timer1.attachInterrupt( timerISR );

    rf.init();
    compiler.init();


    
    buzzer.init();
    buzzer.startUp();
}


void loop(){
    if (Serial.available()) process_serial();

    compiler.run();

    // TEST ENCODERS
    //static byte luz = 0;
    static int serial_interval = 150;
    static unsigned long serial_timeout = millis() + serial_interval;
    if(serial_timeout < millis()){

        Serial.print("\nLeft RPM:\t");
        Serial.print(leftEncoder.getRPM());
        Serial.print("\tLeft Steps:\t\t");
        Serial.println(leftEncoder.getSteps());

        Serial.print("Right RPM:\t");
        Serial.print(rightEncoder.getRPM());
        Serial.print("\tRight Steps:\t");
        Serial.println(rightEncoder.getSteps());
        
        /*switch(luz){
            case 0: led(0,0,0); break;
            case 1: led(1,0,0); break;
            case 2: led(0,1,0); break;
            case 3: led(0,0,1); break;
            case 4: led(1,1,0); break;
            case 5: led(0,1,1); break;
            case 6: led(1,0,1); break;
        }

        luz++;
        if(luz >= 7){luz = 0;};*/
        
        serial_timeout = millis() + serial_interval;
    }
}