#include <Arduino.h>
#include "config.h"
#include "debug.h"
#include "compiler.h"
#include "rf.h"
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
static int action_interval = 4000;
static unsigned long action_timeout = millis() + action_interval;
void Compiler::run(void){

    // No instruction received
    if(_action == 0){
        if(rf.receiveMessage()){
            debug.print("Buffer: ");
            debug.println(rf.getBuffer());
            _action = rf.getNumberFromMessage(0, 2);
            debug.print("Action: ");
            debug.println(_action);
            action_timeout = millis() + action_interval;

            if(!rf.sendMessage("ACK", true)){
                debug.println("RF send ACK response failed");
            }
        }
    }

    // Instruction was received
    if(_action > 0){
        if(action_timeout < millis()){
            action_timeout = millis() + action_interval;
            
            // Send finishing code
            if(!rf.sendMessage("END", true)){
                debug.println("RF send of finishing code failed");
            }
            _action = 0;
        }
    }

}