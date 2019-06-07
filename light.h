#ifndef LIGHT_H
#define LIGHT_H

class Light {

    public:

        Light() {};

        void init(void);
        void led(byte red_value, byte green_value, byte blue_value, byte mode);
        
    private:

        void _handlePWM(int pin, int value);

        typedef struct {
            int pin;
            bool pinState;
            int pwmTickCount;
        } _pwmPin;

        _pwmPin _pwmPins[3];
        unsigned long _previousMicros = 0;
        

};

extern Light light;

#endif //LIGHT_H