#include <Arduino.h>
#include "ObstacleAvoid.h"

ObstacleAvoid::ObstacleAvoid(int pin){
    pinMode(pin, INPUT);
    _pin = pin;
}

int ObstacleAvoid::leggiLuce(){
    return digitalRead(_pin);
}

bool ObstacleAvoid::isLaser(){
    // Simula un LaserDetector che percepisce la luce del laser
    return leggiLuce() == 0;
}

bool ObstacleAvoid::isBlack(){
    // Simula un LaserDetector che percepisce il buio
    return leggiLuce() == 1;
}