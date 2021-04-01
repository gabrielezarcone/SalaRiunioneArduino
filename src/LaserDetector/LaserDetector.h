#ifndef LaserDetector_h
#define LaserDetector_h

#include <Arduino.h>

class LaserDetector{
    public:
        LaserDetector(int pin);
        int leggiLuce(); // restituisce il valore letto da fotoresistore
        bool isLaser(); // restituisce true se il fotorestistore è a contatto con il laser
        bool isBlack(); // restituisce true se il valore di luminosità corrisponde al valore di oscuritò
    private:
        int _pin;
};

#endif