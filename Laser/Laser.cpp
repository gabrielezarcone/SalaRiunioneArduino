#include <Arduino.h>
#include "Laser.h"

Laser::Laser(int pin, int stato){
    pinMode(pin, OUTPUT);
    digitalWrite(pin, stato);
    _pin = pin;
    _stato = stato;
}

void Laser::on(){
    digitalWrite(_pin, HIGH);
    _stato = HIGH;
}

void Laser::off(){
    digitalWrite(_pin, LOW);
    _stato = LOW;
}