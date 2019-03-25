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
        volatile float _RPM = 0;
        volatile unsigned long _RPM_counter = 0;
        volatile unsigned long _micros = 0;
        volatile unsigned long _RPM_read_timeout = millis() + ENCODER_RPM_QUERY_INTERVAL;
        
        
};

extern Encoder encoder;

#endif //ENCODER_H