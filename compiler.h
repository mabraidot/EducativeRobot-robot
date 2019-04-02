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
        void headLights(byte color, byte mode);
        void sound(byte sound_track);
        void waitLight(void);
        void waitSound(void);
        Motor *leftMotor;
        Motor *rightMotor;
        
        Light *light;
    
    private:
    
        byte _action = 0;
        
};

extern Compiler compiler;

#endif //COMPILER_H