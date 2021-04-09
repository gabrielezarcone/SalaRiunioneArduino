#ifndef SensorePassaggio_h
#define SensorePassaggio_h

#include <Arduino.h>
#include "../Laser/Laser.h"
#include "../LaserDetector/LaserDetector.h"
#include "../Comandi.h"

class SensorePassaggio{
    public: 
        SensorePassaggio(int pinLaser1, int pinLaser2, int pinDetector1, int pinDetector2);
        Laser laser1;
        Laser laser2;
        LaserDetector detector1;
        LaserDetector detector2;
        void controllaEntrata();
        void controllaUscita();
    private:
        int _pinLaser1;
        int _pinLaser2;
        int _pinDetector1;
        int _pinDetector2;
        bool stato1(LaserDetector detector1, LaserDetector detector2);
        bool stato2(LaserDetector detector1, LaserDetector detector2);
        bool stato3(LaserDetector detector1, LaserDetector detector2);
        bool stato4(LaserDetector detector1, LaserDetector detector2);
        bool stato5();
};

#endif