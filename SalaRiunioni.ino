#define LASER_PIN 6
#define LIGHT_PIN A3

void setup() {
  pinMode(LASER_PIN, OUTPUT);
  pinMode(LIGHT_PIN, INPUT);
  digitalWrite(LASER_PIN, HIGH);
}

void loop() {
  int val = analogRead(LIGHT_PIN);
  Serial.println(val);
  delay(100);
}