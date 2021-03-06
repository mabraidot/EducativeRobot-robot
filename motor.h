#include <PID_v1.h>
#include "encoder.h"


#ifndef MOTOR_H
#define MOTOR_H

class Motor {

    public:

        Motor(){};
        
        void init(int encoder_pin, int input1, int input2);
        void run();
        void stop(void);
        void move(double new_position, byte rpm);
        bool finished(void);
        
        Encoder *encoder;
        PID *speedPID;
        long right_motor_steps = -1;
    
    private:

        int _pin1;
        int _pin2;
        double _PID_setpoint = 0;
        double _PID_input = 0;
        double _PID_output = 0;
        int _PWM = 0;
        double _position = 0;
        int _position_direction = 0;
        

};

//extern Motor motor;

#endif //MOTOR_H