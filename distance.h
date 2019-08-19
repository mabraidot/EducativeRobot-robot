#ifndef DISTANCE_H
#define DISTANCE_H

class Distance {

    public:
        
        Distance() {};

        void init(void);
        void update(void);
        unsigned long get_distance(void);
        boolean obstacle_detected(void);
        boolean imminent_colition(void);
        
    private:
        
        unsigned long _cm = 0;
};

extern Distance distance;

#endif //DISTANCE_H