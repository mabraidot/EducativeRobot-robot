#ifndef ENCODER_H
#define ENCODER_H

class Encoder {

    public:

        Encoder(){};

        void init(int pin);
        void timerInterrupt(void);
        uint16_t getRPM(void);
        unsigned long getSteps(void);
        void clear(void);

    private:

        int _pin;
        unsigned long _steps = 0;
        uint16_t _RPM = 0;
        unsigned long _RPM_counter = 0;
        unsigned long _millis = 0;
        unsigned long _RPM_read_timeout = millis() + ENCODER_RPM_QUERY_INTERVAL;
        
        
};

extern Encoder encoder;

#endif //ENCODER_H