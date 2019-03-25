#include <TimerOne.h>
#include "config.h"
#include "debug.h"
#include "buzzer.h"
#include "compiler.h"
#include "rf.h"
#include "encoder.h"
#include "light.h"
//#include "motor.h"


Buzzer buzzer;
Compiler compiler;
RF rf;
Light light;
Encoder leftEncoder;
Encoder rightEncoder;
//Motor leftMotor = Motor(MOTOR_LEFT_ENCODER, MOTOR_LEFT_INPUT_1, MOTOR_LEFT_INPUT_2);
//Motor rightMotor = Motor(MOTOR_RIGHT_ENCODER, MOTOR_RIGHT_INPUT_1, MOTOR_RIGHT_INPUT_2);


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

// test led
void led(bool red, bool yellow, bool blue){
    light.led(LIGHT_RED, red);
    light.led(LIGHT_YELLOW, yellow);
    light.led(LIGHT_BLUE, blue);
}


void timerISR(void){
    Timer1.detachInterrupt();

    leftEncoder.timerInterrupt();
    rightEncoder.timerInterrupt();
    //leftMotor.encoder->timerInterrupt();
    //rightMotor.encoder->timerInterrupt();
    
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

    //light.init();
    
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
        //Serial.print(leftMotor.encoder->getRPM());
        Serial.print(leftEncoder.getRPM());
        Serial.print("\tLeft Steps:\t\t");
        //Serial.println(leftMotor.encoder->getSteps());
        Serial.println(leftEncoder.getSteps());

        Serial.print("Right RPM:\t");
        //Serial.print(rightMotor.encoder->getRPM());
        Serial.print(rightEncoder.getRPM());
        Serial.print("\tRight Steps:\t");
        //Serial.println(rightMotor.encoder->getSteps());
        Serial.println(rightEncoder.getSteps());
        
        serial_timeout = millis() + serial_interval;
    }
}