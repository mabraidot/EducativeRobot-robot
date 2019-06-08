#ifndef LIGHT_H
#define LIGHT_H

class Light {

    public:

        Light() {};

        void init(void);
        void led(byte red_value, byte green_value, byte blue_value, byte mode);
        void updatePWMTicks(void);

        volatile byte pwmTickCount = 0;
        
    private:

        void _handlePWM(int pin, int value);

        typedef struct {
            int pin;
            byte pinMaksLow;
            byte pinMaksHigh;
            bool pinState;
        } _pwmPin;

        _pwmPin _pwmPins[3];
        unsigned long _previousMicros = 0;
        

};

extern Light light;

#endif //LIGHT_H