#include "src/SensorePassaggio/SensorePassaggio.h"
#include "src/Schermo/Schermo.h"
#include "src/ResponseParser/ResponseParser.h"
#include "src/Secrets.h"
#include "src/Endpoint.h"

#define LASER_PIN1 53
#define LASER_PIN2 51
#define DETECTOR_PIN1 A14
#define DETECTOR_PIN2 A15

SensorePassaggio sensorePorta(LASER_PIN1, LASER_PIN2, DETECTOR_PIN1, DETECTOR_PIN2);
Schermo lcd;
ResponseParser parser(lcd);
String arduinoName(ARDUINO_NAME);
unsigned long startTime = millis();
unsigned long time = 0;

void setup() {
  lcd.setup();
  Serial.begin(9600);
  delay(200);
  Serial2.begin(4800); // Serial a cui è collegata la board client wifi
  delay(200);
  lcd.renderLCD();
}

void loop() {
  time = millis();
  sensorePorta.controllaEntrata();
  sensorePorta.controllaUscita();
  while (Serial2.available()){
    String serial2Str = Serial2.readStringUntil('\n');
    serial2Str.trim();
    Serial.println(serial2Str);
    Serial.print("equals: ");
    Serial.println(serial2Str.equals(RIUNIONE_ATTUALE+arduinoName));
    if(serial2Str.equals(RIUNIONE_ATTUALE+arduinoName)){
      parser.onNowReceived(lcd);
    }
  }
  if (time-startTime > 9000){
    Serial.println(time);
    Serial2.println(RIUNIONE_ATTUALE+arduinoName);
    delay(200);
    //Serial2.println(RIUNIONE_SUCCESSIVA+arduinoName);
    startTime = millis();
  }
}