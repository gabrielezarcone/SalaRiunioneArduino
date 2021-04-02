#ifndef Laser_h
#define Laser_h

#include <Arduino.h>

class Laser{
    public: 
        Laser(int pin, int stato);
        void on();
        void off();
    private:
        int _pin;
        int _stato;
};

#endif