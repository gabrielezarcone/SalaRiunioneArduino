/*
    Usala terminologia del laser perchè l'utilizzo di questo sensore è solo temporaneo
    Verrà sostituito coin un laser
*/

#ifndef ObstacleAvoid_h
#define ObstacleAvoid_h

#include <Arduino.h>
#include "LaserDetector.h"

class ObstacleAvoid : public LaserDetector{
    public:
        ObstacleAvoid(int pin);
        int leggiLuce(); // restituisce il valore letto dal sensore di ObstacleAvoid
        bool isLaser(); // Simula un LaserDetector che percepisce la luce del laser
        bool isBlack(); // Simula un LaserDetector che percepisce il buio
    private:
        int _pin;
};

#endif