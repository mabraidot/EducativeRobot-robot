#include <PID_v1.h>
#include "encoder.h"

#ifndef MOTOR_H
#define MOTOR_H

class Motor {

    public:

        Motor(void);

        void init(int encoder_pin, int input1, int input2);
        void run(void);
        void stop(void);
        void move(int new_position);
        bool finished(void);
        //float getSpeed(void);
        void setSpeed(float rpm);

        Encoder *encoder;
        PID *speedPID;
    
    private:

        double _PID_setpoint = 0;
        double _PID_input = 0;
        double _PID_output = 0;
        uint8_t _position_accuracy = 0;   // Set to the highest tolerable inaccuracy (units are encoder counts)

};

extern Motor motor;

#endif //MOTOR_H