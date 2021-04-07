/*
    Questo codice deve essere inserito all'interno della board (ESP8266) che si occuperà di effettuare le chiamate HTTP al server.
    Riceve istruzioni dalla board principale (MEGA2560) attraversolo la comunicazione seriale.
*/

#include "src/SerialComunication/SerialComunication.h"

SerialComunication serialCom;

char receivedString[10];  

void setup(){
    Serial1.begin(9600);  
    Serial.begin(115200);
    while (!Serial);

    WiFi.mode(WIFI_STA);

    WiFi.begin(ssid, password);
    
    Serial.println("Connecting to WiFi SSID: " + String(ssid));
}

void loop(){
  serialCom.checkMainBoard();
}
