#include <Arduino.h>

#include "../Laser/Laser.h"
#include "../LaserDetector/LaserDetector.h"

#include "SensorePassaggio.h"

SensorePassaggio::SensorePassaggio(int pinLaser1, int pinLaser2, int pinDetector1, int pinDetector2) 
        : laser1(pinLaser1,HIGH), laser2(pinLaser2,HIGH), detector1(pinDetector1), detector2(pinDetector2) {
    _pinLaser1 = pinLaser1;
    _pinLaser2 = pinLaser2;
    _pinDetector1 = pinDetector1;
    _pinDetector2 = pinDetector2;
}


void SensorePassaggio::controllaEntrata(){
  if (detector1.isBlack()){
    Serial.println("Controllo entrata");
    if (stato1(detector1, detector2)){
      Serial.println("Entrata");
    }
  }
  
}

void SensorePassaggio::controllaUscita(){
  if (detector2.isBlack()){
    Serial.println("Controllo uscita");
    if (stato1(detector2, detector1)){
      Serial.println("Uscita");
    }
  }
}


bool SensorePassaggio::stato1(LaserDetector detector1, LaserDetector detector2){
  Serial.println("Stato 1");
  while (!detector1.isLaser()){ // rimane dentro finchè non si riaccende il laser
    if (detector2.isBlack()){
      return stato5();
    }
  }
  return stato2(detector1, detector2);
}


bool SensorePassaggio::stato2(LaserDetector detector1, LaserDetector detector2){
  Serial.println("Stato 2");
  while (!detector2.isBlack()){
    if (detector1.isBlack()){
      return stato1(detector1, detector2);
    }
  }
  return stato3(detector1, detector2);
}


bool SensorePassaggio::stato3(LaserDetector detector1, LaserDetector detector2){
  Serial.println("Stato 3");
  while (!detector2.isLaser()){
    if (detector1.isBlack()){
      return stato5();
    }
  }
  return stato4(detector1, detector2);
}


bool SensorePassaggio::stato4(LaserDetector detector1, LaserDetector detector2){
  Serial.println("Stato 4");
  return true;
}


bool SensorePassaggio::stato5(){
  Serial.println("Stato 5");
  Serial.println("Entrambi detector spenti");
  return false;
}