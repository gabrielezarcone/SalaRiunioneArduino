#include "src/Laser/Laser.h"
#include "src/LaserDetector/LaserDetector.h"

#define LASER_PIN1 6
#define LASER_PIN2 7
#define DETECTOR_PIN1 A3
#define DETECTOR_PIN2 A4

Laser laser1(LASER_PIN1, HIGH);
Laser laser2(LASER_PIN2, HIGH);
LaserDetector laserDetector1(DETECTOR_PIN1);
LaserDetector laserDetector2(DETECTOR_PIN2);

void setup() {
}

void loop() {
  if(laserDetector1.isBlack()){
    while (!laserDetector1.isLaser()){}
    Serial.println("Passato dal primo sensore");
  }
  if(laserDetector2.isBlack()){
    while (!laserDetector2.isLaser()){}
    Serial.println("Passato dal secondo sensore");
  }
}