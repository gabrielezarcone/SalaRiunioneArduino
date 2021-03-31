#include <Laser.h>
#include <LaserDetector.h>

#define LASER_PIN 6
#define DETECTOR_PIN A3

Laser laser(LASER_PIN, HIGH);
LaserDetector laserDetector(DETECTOR_PIN);

void setup() {
}

void loop() {
  int val = laserDetector.leggiLuce();
  Serial.println(val);
  delay(100);
}