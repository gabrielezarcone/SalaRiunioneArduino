#include "src/Laser/Laser.h"
#include "src/LaserDetector/LaserDetector.h"
#include "src/LaserDetector/ObstacleAvoid.h"

#define LASER_PIN1 6
#define LASER_PIN2 7
#define DETECTOR_PIN1 A3
#define DETECTOR_PIN2 5

Laser laser1(LASER_PIN1, HIGH);
Laser laser2(LASER_PIN2, HIGH);
LaserDetector laserDetector1(DETECTOR_PIN1);
ObstacleAvoid laserDetector2(DETECTOR_PIN2);

void setup() {
}

void loop() {
  controllaEntrata();
  //controllaUscita();
  //Serial.println(laserDetector2.isBlack());
}

void controllaEntrata(){
  if (laserDetector1.isBlack()){
    Serial.println("controllo entrata");
    if (stato1(laserDetector1, laserDetector2)){
      Serial.println("Entrata");
    }
  }
  
}

// void controllaUscita(){
//   if (laserDetector2.isBlack()){
//     Serial.println("controllo uscita");
//     if (stato1(laserDetector2, laserDetector1)){
//       Serial.println("Uscita");
//     }
//   }
// }

bool stato1(LaserDetector detector1, ObstacleAvoid detector2){
  Serial.println("Stato 1");
  while (!detector1.isLaser()){ // rimane dentro finchè non si riaccende il laser
    if (detector2.isBlack()){
      return stato5();
    }
  }
  return stato2(detector1, detector2);
}

bool stato2(LaserDetector detector1, ObstacleAvoid detector2){
  Serial.println("Stato 2");
  while (!detector2.isBlack()){
    if (detector1.isBlack()){
      return stato1(detector1, detector2);
    }
  }
  return stato3(detector1, detector2);
}

bool stato3(LaserDetector detector1, ObstacleAvoid detector2){
  Serial.println("Stato 3");
  while (!detector2.isLaser()){
    if (detector1.isBlack()){
      return stato5();
    }
  }
  return stato4(detector1, detector2);
}

bool stato4(LaserDetector detector1, ObstacleAvoid detector2){
  Serial.println("Stato 4");
  return true;
}

bool stato5(){
  Serial.println("Stato 5");
  Serial.println("Entrambi detector spenti");
  return false;
}