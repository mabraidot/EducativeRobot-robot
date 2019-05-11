#include <ServoTimer2.h>
#include "encoder.h"


#ifndef MOTOR_H
#define MOTOR_H

class Motor {

    public:

        Motor(){};
        
        void init(int encoder_pin, int motor_pin, bool inverse);
        void run();
        void stop(void);
        void move(double new_position);
        bool finished(void);
        void setSpeed(float rpm);
        Encoder *encoder;
        ServoTimer2 *servo;
    
    private:

        int _pin;
        int _inverse = 0;
        int _PWM = 0;
        double _position = 0;
        int _position_direction = 0;
        
};

//extern Motor motor;

#endif //MOTOR_H