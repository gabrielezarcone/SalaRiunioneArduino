#include "src/Laser/Laser.h"
#include "src/LaserDetector/LaserDetector.h"
#include "src/LaserDetector/ObstacleAvoid.h"
#include "src/SensorePassaggio/SensorePassaggio.h"

#define LASER_PIN1 6
#define LASER_PIN2 7
#define DETECTOR_PIN1 A3
#define DETECTOR_PIN2 5

SensorePassaggio sensorePorta(LASER_PIN1, LASER_PIN2, DETECTOR_PIN1, DETECTOR_PIN2);

void setup() {
}

void loop() {
  sensorePorta.controllaEntrata();
  //sensorePorta.controllaUscita();
}