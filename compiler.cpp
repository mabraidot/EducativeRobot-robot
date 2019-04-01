#include <Arduino.h>
#include "config.h"
#include "debug.h"
#include "compiler.h"
#include "rf.h"
#include "light.h"
#include "motor.h"
#include "buzzer.h"


/*--------------------------------------*/
/*       PUBLIC FUNCTIONS               */
/*--------------------------------------*/
void Compiler::init(void){
    pinMode(LIGHT_YELLOW, OUTPUT);
    pinMode(LIGHT_RED, OUTPUT);
    pinMode(LIGHT_BLUE, OUTPUT);
}


// Test RF
//static int action_interval = 4000;
//static unsigned long action_timeout = millis() + action_interval;
void Compiler::run(void){

    // No instruction received
    if(_action == 0){
        if(rf.receiveMessage()){
            debug.print("Buffer: ");
            debug.println(rf.getBuffer());
            _action = rf.getNumberFromMessage(0, 2);
            debug.print("Action: ");
            debug.println(_action);
            //action_timeout = millis() + action_interval;

            if(!rf.sendMessage("ACK", true)){
                debug.println("RF send ACK response failed");
            }
        }
    }

    // Instruction was received
    /*if(_action > 0){
        if(action_timeout < millis()){
            action_timeout = millis() + action_interval;
            
            // Send finishing code
            if(!rf.sendMessage("END", true)){
                debug.println("RF send of finishing code failed");
            }
            _action = 0;
        }
    }*/

    switch(_action){
        case MODE_SLAVE_FORWARD_ARROW: 
            {
                moveForward(false);
            }
            break;
        case MODE_SLAVE_BACKWARD_ARROW: 
            {
                moveBackward(false);
            }
            break;
        case MODE_SLAVE_LEFT_ARROW: 
            {
                moveTurnLeft(false);
            }
            break;
        case MODE_SLAVE_RIGHT_ARROW: 
            {
                moveTurnRight(false);
            }
            break;

        default: break;
    }

}


void Compiler::moveForward(bool until_wall_detected = false){
    
    if(!until_wall_detected){
        int block_dimention = 20;
        leftMotor.move(block_dimention, ROBOT_SPEED);
        rightMotor.move(block_dimention, ROBOT_SPEED);
    }else{
        // @TODO: implement ultrasonic sensor to do unlimited run 
        // until an obstacle is detected
    }

}


void Compiler::moveBackward(void){
    
    int block_dimention = -20;
    leftMotor.move(block_dimention, ROBOT_SPEED);
    rightMotor.move(block_dimention, ROBOT_SPEED);

}


void Compiler::moveTurnLeft(void){

    leftMotor.move(-1 * ENCODER_CM_TO_ROTATE_90, ROBOT_SPEED);
    rightMotor.move(ENCODER_CM_TO_ROTATE_90, ROBOT_SPEED);

}


void Compiler::moveTurnRight(void){

    leftMotor.move(ENCODER_CM_TO_ROTATE_90, ROBOT_SPEED);
    rightMotor.move(-1 * ENCODER_CM_TO_ROTATE_90, ROBOT_SPEED);

}


void Compiler::light(byte color, byte mode){

    light.led(color, mode);
    
}


void Compiler::sound(byte sound_track);
void Compiler::waitLight(void);
void Compiler::waitSound(void);