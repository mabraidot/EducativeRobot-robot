#ifndef LIGHT_H
#define LIGHT_H

class Light {

    public:

        Light() {};

        void init(void);
        void led(byte color, byte mode);

};

extern Light light;

#endif //LIGHT_H