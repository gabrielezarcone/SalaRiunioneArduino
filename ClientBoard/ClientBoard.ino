/*
    Questo codice deve essere inserito all'interno della board (ESP8266) che si occuperà di effettuare le chiamate HTTP al server.
    Riceve istruzioni dalla board principale (MEGA2560) attraversolo la comunicazione seriale.
*/

#include "src/SerialComunication/SerialComunication.h"

SerialComunication serialCom;

char receivedString[10];  

void setup(){
  Serial.begin(9600); 
  serialCom.http.setup(); 
  delay(5000);
  serialCom.httpGetPrenotazioneAttuale();
  serialCom.httpGetPrenotazioneSuccessiva();
  //serialCom.httpPostCounter();
  //Serial.println(1);
  //serialCom.httpPostTemperature();
  //Serial.println(21);
}

void loop(){
  //serialCom.checkMainBoard();
}
