#include <PID_v1.h>
#include "encoder.h"

#ifndef MOTOR_H
#define MOTOR_H

class Motor {

    public:

        //Motor(void);
        Motor(){};
        
        void init(int encoder_pin, int input1, int input2);
        void run(void);
        void stop(void);
        void move(int new_position, byte rpm);
        bool finished(void);
        void setSpeed(float rpm);
        Encoder *encoder;
        PID *speedPID;
    
    private:

        int _pin1;
        int _pin2;
        double _PID_setpoint = 0;
        double _PID_input = 0;
        double _PID_output = 0;
        uint8_t _position_accuracy = 2;   // Set to the highest tolerable inaccuracy (units are encoder counts)
        int _PWM = 0;
        double _position = 0;
        int _position_direction = 0;
        
};

//extern Motor motor;

#endif //MOTOR_H