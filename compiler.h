#include "motor.h"
#include "light.h"

#ifndef COMPILER_H
#define COMPILER_H

class Compiler {

    public:
        
        Compiler() {};

        void init(void);
        void run(void);

        void moveForward(bool until_wall_detected = false);
        void moveBackward(void);
        void moveTurnLeft(void);
        void moveTurnRight(void);
        void waitLight(void);
        void waitSound(void);
        void setBuzzerSound(byte action_value);
        void setHeadlight(byte action_value);
        
        Motor *leftMotor;
        Motor *rightMotor;
        
        Light *light;
    
    private:
    
        byte _action = 0;
        byte _action_value = 0;
        int _average_light = 0;
        int _average_sound = 0;
        
        
};

extern Compiler compiler;

#endif //COMPILER_H