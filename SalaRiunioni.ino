#include "src/SensorePassaggio/SensorePassaggio.h"
#include "src/Schermo/Schermo.h"

#define LASER_PIN1 6
#define LASER_PIN2 7
#define DETECTOR_PIN1 A3
#define DETECTOR_PIN2 5

SensorePassaggio sensorePorta(LASER_PIN1, LASER_PIN2, DETECTOR_PIN1, DETECTOR_PIN2);
Schermo lcd;

void setup() {
  lcd.setup();
  lcd.renderLCD();
}

void loop() {
  //sensorePorta.controllaEntrata();
  //sensorePorta.controllaUscita();
}