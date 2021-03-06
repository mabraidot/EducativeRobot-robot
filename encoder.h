#ifndef ENCODER_H
#define ENCODER_H

class Encoder {

    public:

        Encoder(){};

        void init(int pin);
        void timerInterrupt(void);
        float getRPM(void);
        unsigned long getSteps(void);
        void clear(void);

    private:

        int _pin;
        volatile unsigned long _steps = 0;
        volatile int _state = LOW;
        volatile float _RPM = 0;
        volatile unsigned long _RPM_counter = 0;
        volatile unsigned long _micros = 0;
        
};

//extern Encoder encoder;

#endif //ENCODER_H