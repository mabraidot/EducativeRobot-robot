#include <Arduino.h>
#include "config.h"
#include "debug.h"
#include "compiler.h"
#include "rf.h"



/*--------------------------------------*/
/*       PUBLIC FUNCTIONS               */
/*--------------------------------------*/
void Compiler::init(void){
    pinMode(LIGHT_RED, OUTPUT);
    pinMode(LIGHT_GREEN, OUTPUT);
    pinMode(LIGHT_BLUE, OUTPUT);

    leftMotor = new Motor();
    rightMotor = new Motor();
    light = new Light();

    light->init();

    leftMotor->init(MOTOR_LEFT_ENCODER, MOTOR_LEFT_INPUT, false);
    rightMotor->init(MOTOR_RIGHT_ENCODER, MOTOR_RIGHT_INPUT, true);

}


void Compiler::run(void){

    // No instruction received
    if(_action == 0){
        if(rf.receiveMessage()){
            debug.print("Buffer: ");
            debug.println(rf.getBuffer());
            _action = rf.getNumberFromMessage(0, 2);
            debug.print("Action: ");
            debug.println(_action);
            
            if(!rf.sendMessage("ACK", true)){
                debug.println("RF send ACK response failed");
            }

            switch(_action){
                case MODE_SLAVE_FORWARD_ARROW:  moveForward(false);     break;
                case MODE_SLAVE_BACKWARD_ARROW: moveBackward();         break;
                case MODE_SLAVE_LEFT_ARROW:     moveTurnLeft();         break;
                case MODE_SLAVE_RIGHT_ARROW:    moveTurnRight();        break;
                default: break;
            }
        }
    }

    switch(_action){
        case MODE_SLAVE_FORWARD_ARROW: 
        case MODE_SLAVE_BACKWARD_ARROW: 
        case MODE_SLAVE_LEFT_ARROW: 
        case MODE_SLAVE_RIGHT_ARROW: 
            {
                if(!leftMotor->finished() || !rightMotor->finished()){
                    rightMotor->run();
                    leftMotor->run();
                }else{
                    leftMotor->stop();
                    rightMotor->stop();
                    // Send finishing code
                    if(!rf.sendMessage("END", true)){
                        debug.println("RF send of finishing code failed");
                    }
                    _action = 0;
                }
            }
            break;

        default: break;
    }
    

}


void Compiler::moveForward(bool until_wall_detected = false){
    
    if(!until_wall_detected){
        int block_dimention = DIDACTIC_MAP_BLOCK_SIZE;
        rightMotor->move(block_dimention);
        leftMotor->move(block_dimention);
    }else{
        // @TODO: implement ultrasonic sensor to do unlimited run 
        // until an obstacle is detected
    }

}


void Compiler::moveBackward(void){
    
    int block_dimention = -DIDACTIC_MAP_BLOCK_SIZE;
    rightMotor->move(block_dimention);
    leftMotor->move(block_dimention);
    
}


void Compiler::moveTurnLeft(void){

    rightMotor->move(ENCODER_CM_TO_ROTATE_90);
    leftMotor->move(-ENCODER_CM_TO_ROTATE_90);
    
}


void Compiler::moveTurnRight(void){

    rightMotor->move(-ENCODER_CM_TO_ROTATE_90);
    leftMotor->move(ENCODER_CM_TO_ROTATE_90);
    
}


void Compiler::headLights(byte color, byte mode){

    light->led(color, mode);
    
}


//void Compiler::sound(byte sound_track);
//void Compiler::waitLight(void);
//void Compiler::waitSound(void);