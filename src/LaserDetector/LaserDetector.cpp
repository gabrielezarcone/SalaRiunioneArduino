#include <Arduino.h>
#include "LaserDetector.h"

LaserDetector::LaserDetector(int pin){
    pinMode(pin, INPUT);
    _pin = pin;
}

int LaserDetector::leggiLuce(){
    return analogRead(_pin);
}

bool LaserDetector::isLaser(){
    // Restituisco true quando il sensore non rileva la completa oscuritò
    // Questo perchè circondiamo il sensore di nastro isolante lasciandolo al buio con solo un piccolo spiraglio per far passare il led
    return !isBlack();
}

bool LaserDetector::isBlack(){
    // Il nostro fotoresistore restituisce un valore di 1023 in caso di completa oscurità
    // All'aumentare della quantità della luce il valore restituito scende diventando sempre più piccolo
    return leggiLuce() > 1010; 
}