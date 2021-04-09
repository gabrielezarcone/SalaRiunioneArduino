#include "src/SensorePassaggio/SensorePassaggio.h"
#include "src/Schermo/Schermo.h"
#include "src/ResponseParser/ResponseParser.h"

#define LASER_PIN1 53
#define LASER_PIN2 51
#define DETECTOR_PIN1 A14
#define DETECTOR_PIN2 A15

SensorePassaggio sensorePorta(LASER_PIN1, LASER_PIN2, DETECTOR_PIN1, DETECTOR_PIN2);
Schermo lcd;
ResponseParser parser(lcd);
int time;

void setup() {
  lcd.setup();
  Serial.begin(115200);
  Serial2.begin(115200); // Serial a cui è collegata la board client wifi
  lcd.renderLCD();
}

void loop() {
  time = millis();
  sensorePorta.controllaEntrata();
  sensorePorta.controllaUscita();
  parser.checkResponses();
  if(time > 3000){
    Serial2.println(NOW);
    if(Serial2.available()){
      String string = Serial2.readString();
      Serial.print("Prova: ");
      Serial.println(string);
    }
    time=0;
  }
}