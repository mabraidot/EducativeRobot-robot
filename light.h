#ifndef LIGHT_H
#define LIGHT_H

class Light {

    public:

        Light() {};

        void init(void);
        //void led(byte red_value, byte green_value, byte blue_value, byte mode);
        void led();
        void updatePWMTicks(void);
        void ledMatrix(byte color);
        void ledMatrixOff(void);
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
        byte _led_matrix[13][3] = {
            {  0,    0,  0  }, // OFF
            {255,    0,  0  }, // Red
            {255,   40,  0  }, // Orange
            {180,  100,  0  }, // Yellow
            {255,  255,  0  }, // Chartreuse
            {  0,  255,  0  }, // Green
            {  0,  255,  150}, // Aquamarine
            {  0,  255,  255}, // Cyan
            {  0,  150,  255}, // Azure
            {  0,    0,  255}, // Blue
            {150,    0,  255}, // Violet
            {255,    0,  255}, // Magenta
            {255,    0,  150}  // Rose
		};
        byte _red_value = 0;
        byte _green_value = 0;
        byte _blue_value = 0;
        byte _mode = STATE_LED_OFF;
        bool _activated = 0;
        
};

extern Light light;

#endif //LIGHT_H