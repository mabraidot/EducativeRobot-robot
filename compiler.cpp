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


void Compiler::runFinished(void){
    
    delay(400); // Little pause between actions
    // Send finishing code
    if(!rf.sendMessage("END", false)){
        debug.println("RF send of finishing code failed");
    }
    _action = 0;
    _light_millis = millis();

}

void Compiler::run(void){
    
    light->led();
    if(_action == 0 && (millis() - _light_millis) > _light_timeout){
        light->ledMatrixOff();
        _light_millis = millis();
    }

    // No instruction received
    if(_action == 0){
        if(rf.receiveMessage()){
            debug.print("Buffer: ");
            debug.println(rf.getBuffer());
            _action = rf.getNumberFromMessage(0, 2);
            _action_value = rf.getNumberFromMessage(2, 2);
            debug.print("Action: ");
            debug.println(_action);
            debug.print("Action value: ");
            debug.println(_action_value);
            
            if(!rf.sendMessage("ACK", false)){
                debug.println("RF send ACK response failed");
            }

            switch(_action){
                case MODE_SLAVE_FORWARD_ARROW:  moveForward(false);             break;
                case MODE_SLAVE_BACKWARD_ARROW: moveBackward();                 break;
                case MODE_SLAVE_LEFT_ARROW:     moveTurnLeft();                 break;
                case MODE_SLAVE_RIGHT_ARROW:    moveTurnRight();                break;
                case MODE_SLAVE_WAIT_LIGHT:     waitLight();                    break;
                case MODE_SLAVE_WAIT_SOUND:     waitSound();                    break;
                case MODE_SLAVE_SOUND:          setBuzzerSound(_action_value);  break;
                case MODE_SLAVE_LIGHT:          setHeadlight(_action_value);    break;
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
                    /*delay(400); // Little pause between actions
                    // Send finishing code
                    if(!rf.sendMessage("END", false)){
                        debug.println("RF send of finishing code failed");
                    }
                    _action = 0;*/
                    runFinished();
                }
            }
            break;

        case MODE_SLAVE_WAIT_LIGHT: 
            {
                /*debug.print("Light: ");
                debug.print((double)analogRead(SENSOR_LIGHT));
                debug.print("\tAverage: ");
                debug.println((double)_average_light);
                */
                if(analogRead(SENSOR_LIGHT) > (_average_light + 200)){
                    /*delay(400);
                    // Send finishing code
                    if(!rf.sendMessage("END", false)){
                        debug.println("RF send of finishing code failed");
                    }
                    _action = 0;*/
                    runFinished();
                }
            }
            break;

        case MODE_SLAVE_WAIT_SOUND: 
            {
                /*debug.print("Sound: ");
                debug.print((double)analogRead(SENSOR_SOUND));
                debug.print("\tAverage: ");
                debug.println((double)_average_sound);
                */
                if(analogRead(SENSOR_SOUND) > (_average_sound + 10)){
                    /*delay(400);
                    // Send finishing code
                    if(!rf.sendMessage("END", false)){
                        debug.println("RF send of finishing code failed");
                    }
                    _action = 0;*/
                    runFinished();
                }
            }
            break;

        case MODE_SLAVE_SOUND: 
            {
                /*delay(400);
                // Send finishing code
                if(!rf.sendMessage("END", false)){
                    debug.println("RF send of finishing code failed");
                }
                _action = 0;*/
                runFinished();
            }
            break;

        case MODE_SLAVE_LIGHT: 
            {
                /*delay(400);
                // Send finishing code
                if(!rf.sendMessage("END", false)){
                    debug.println("RF send of finishing code failed");
                }
                _action = 0;*/
                runFinished();
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


void Compiler::waitLight(void){
    delay(10);
    _average_light = analogRead(SENSOR_LIGHT);
    delay(10);
    _average_light += analogRead(SENSOR_LIGHT);
    delay(10);
    _average_light += analogRead(SENSOR_LIGHT);
    delay(10);
    _average_light += analogRead(SENSOR_LIGHT);
    _average_light = (int) _average_light / 4;
}


void Compiler::waitSound(void){
    delay(10);
    _average_sound = analogRead(SENSOR_SOUND);
    delay(10);
    _average_sound += analogRead(SENSOR_SOUND);
    delay(10);
    _average_sound += analogRead(SENSOR_SOUND);
    delay(10);
    _average_sound += analogRead(SENSOR_SOUND);
    _average_sound = (int) _average_sound / 4;
}


void Compiler::setBuzzerSound(byte action_value){
    buzzer->toneMatrix(action_value, 3);
}


void Compiler::setHeadlight(byte action_value){
    light->ledMatrix(action_value);
}