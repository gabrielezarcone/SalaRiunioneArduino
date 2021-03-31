#include <Laser.h>

#define LASER_PIN 6
#define LIGHT_PIN A3

Laser laser(LASER_PIN, HIGH);

void setup() {
  pinMode(LIGHT_PIN, INPUT);
}

void loop() {
  int val = analogRead(LIGHT_PIN);
  Serial.println(val);
  delay(100);
}