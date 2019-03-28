#ifndef PWM_H
#define PWM_H

class PWM {

    public:

        PWM(){};

        void setPins(int pins[]);
        void setPWMValue(int pin, int value);
        void handlePWM(int pin, int value);

    private:

        typedef struct {
            int pin;
            //int pwmValue;
            bool pinState;
            int pwmTickCount;
        } _pwmPin;

        _pwmPin _pwmPins[MOTOR_PWM_PINS_QTY];
        unsigned long _previousMicros = 0;

};

extern PWM pwm;

#endif //PWM_H