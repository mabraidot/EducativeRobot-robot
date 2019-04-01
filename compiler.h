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
        void light(byte color, byte mode);
        void sound(byte sound_track);
        void waitLight(void);
        void waitSound(void);
    
    private:
    
        byte _action = 0;
        
};

extern Compiler compiler;

#endif //COMPILER_H