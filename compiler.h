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
        void sound(byte sound_track);
        void waitLight(void);
        void waitSound(void);
        
        void headLights(byte mode); // Random light color
        void headLights(byte red_value, byte green_value, byte blue_value, byte mode); // Light color specified
        
        Motor *leftMotor;
        Motor *rightMotor;
        
        Light *light;
    
    private:
    
        byte _action = 0;
        
};

extern Compiler compiler;

#endif //COMPILER_H