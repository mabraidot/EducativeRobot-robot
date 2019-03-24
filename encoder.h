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
        unsigned long _RPM_counter;
        uint16_t _survey_interval = ENCODER_QUERY_INTERVAL;
        unsigned long _read_timeout = millis() + _survey_interval;
        
        
};

extern Encoder encoder;

#endif //ENCODER_H