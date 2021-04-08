#include "src/SensorePassaggio/SensorePassaggio.h"
#include "src/Schermo/Schermo.h"

#define LASER_PIN1 6
#define LASER_PIN2 7
#define DETECTOR_PIN1 A3
#define DETECTOR_PIN2 A5

SensorePassaggio sensorePorta(LASER_PIN1, LASER_PIN2, DETECTOR_PIN1, DETECTOR_PIN2);
Schermo lcd;
int i = 0;

void setup() {
  lcd.setup();
  Serial.begin(9600);
  Serial2.begin(9600); // Serial a cui è collegata la board client wifi
}

void loop() {
  //sensorePorta.controllaEntrata();
  //sensorePorta.controllaUscita();
  lcd.renderLCD();
  delay(3500);
  lcd.setStatusStanza(i%2);
  i++;
  Serial2.print("hello");
}