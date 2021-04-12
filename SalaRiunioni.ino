#include "src/SensorePassaggio/SensorePassaggio.h"
#include "src/Schermo/Schermo.h"
#include "src/ResponseParser/ResponseParser.h"
#include <SPI.h>

#define LASER_PIN1 53
#define LASER_PIN2 51
#define DETECTOR_PIN1 A14
#define DETECTOR_PIN2 A15

SensorePassaggio sensorePorta(LASER_PIN1, LASER_PIN2, DETECTOR_PIN1, DETECTOR_PIN2);
Schermo lcd;
ResponseParser parser(lcd);

void setup() {
  lcd.setup();
  Serial.begin(9600);
  delay(200);
  Serial2.begin(9600); // Serial a cui è collegata la board client wifi
  delay(200);
  lcd.renderLCD();
}

void loop() {
  sensorePorta.controllaEntrata();
  sensorePorta.controllaUscita();
  //parser.checkResponses();
  while (Serial2.available()){
    String serial2Str = Serial2.readString();
    Serial.println(serial2Str);
  }
  //delay(2000);
  //Serial2.write("/stanze/stanza");
}