#ifndef BUZZER_H
#define BUZZER_H

class Buzzer {

    public:

        Buzzer() {};

        void init(void);
        void startSound(void);
        void stopSound(void);
        void toneMatrix(byte theme, byte repetitions = 1);
        
        void startUp(void);
        void error(void);

    private:
        void _note(byte index, uint16_t frequency, uint32_t duration);

        byte _melody_index = 0;
        unsigned long _previous_time = 0;
        unsigned long _pause_interval = 0;


};

extern Buzzer buzzer;

#endif //BUZZER_H