#include <Arduino.h>
#include "config.h"
#include "debug.h"
#include "compiler.h"
#include "rf.h"



/*--------------------------------------*/
/*       PUBLIC FUNCTIONS               */
/*--------------------------------------*/
void Compiler::init(void){
    
    leftMotor = new Motor();
    rightMotor = new Motor();
    light = new Light();

    light->init();

    leftMotor->init(MOTOR_LEFT_ENCODER, MOTOR_LEFT_INPUT_1, MOTOR_LEFT_INPUT_2);
    rightMotor->init(MOTOR_RIGHT_ENCODER, MOTOR_RIGHT_INPUT_1, MOTOR_RIGHT_INPUT_2);
    leftMotor->speedPID->SetTunings(MOTOR_LEFT_PID_kP, MOTOR_LEFT_PID_kI, MOTOR_LEFT_PID_kD);
    rightMotor->speedPID->SetTunings(MOTOR_RIGHT_PID_kP, MOTOR_RIGHT_PID_kI, MOTOR_RIGHT_PID_kD);
    leftMotor->speedPID->SetOutputLimits(68,255);
    rightMotor->speedPID->SetOutputLimits(177,255);

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
            
            if(!rf.sendMessage("ACK", false)){
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
                    delay(400); // Little pause between actions
                    // Send finishing code
                    if(!rf.sendMessage("END", false)){
                        debug.println("RF send of finishing code failed");
                    }
                    _action = 0;
                }
            }
            break;

        default: break;
    }
    


    if(!rightMotor->finished()){
        leftMotor->right_motor_steps = rightMotor->encoder->getSteps();
    }

}


void Compiler::moveForward(bool until_wall_detected = false){
    
    if(!until_wall_detected){
        int block_dimention = DIDACTIC_MAP_BLOCK_SIZE;
        rightMotor->move(block_dimention, ROBOT_SPEED);
        leftMotor->move(block_dimention, ROBOT_SPEED);
    }else{
        // @TODO: implement ultrasonic sensor to do unlimited run 
        // until an obstacle is detected
    }

}


void Compiler::moveBackward(void){
    
    int block_dimention = -DIDACTIC_MAP_BLOCK_SIZE;
    rightMotor->move(block_dimention, ROBOT_SPEED);
    leftMotor->move(block_dimention, ROBOT_SPEED);
    
}


void Compiler::moveTurnLeft(void){

    rightMotor->move(CM_TO_ROTATE_90, ROBOT_TURN_SPEED);
    leftMotor->move(-CM_TO_ROTATE_90, ROBOT_TURN_SPEED);
    
}


void Compiler::moveTurnRight(void){

    rightMotor->move(-CM_TO_ROTATE_90, ROBOT_TURN_SPEED);
    leftMotor->move(CM_TO_ROTATE_90, ROBOT_TURN_SPEED);
    
}


void Compiler::headLights(byte mode){

    static int demo_interval = 1000;
    static unsigned long demo_timeout = millis() + demo_interval;
    static byte rvalue = 0;
    static byte gvalue = 0;
    static byte bvalue = 0;
    if(demo_timeout < millis()){
        rvalue = random(256);
        gvalue = random(256);
        bvalue = random(256);
        demo_timeout = millis() + demo_interval;
    }
    
    light->led(rvalue, gvalue, bvalue, mode);
    
}

void Compiler::headLights(byte red_value, byte green_value, byte blue_value, byte mode){
    light->led(red_value, green_value, blue_value, mode);
}


//void Compiler::sound(byte sound_track);
//void Compiler::waitLight(void);
//void Compiler::waitSound(void);