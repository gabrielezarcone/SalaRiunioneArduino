/*
    Questo codice deve essere inserito all'interno della board (ESP8266) che si occuperà di effettuare le chiamate HTTP al server.
    Riceve istruzioni dalla board principale (MEGA2560) attraversolo la comunicazione seriale.
*/

#include "src/SerialComunication/SerialComunication.h"

SerialComunication serialCom;

char receivedString[10];  

void setup(){
    Serial1.begin(9600);  
}

void loop(){
  //serialCom.checkMainBoard();
  serialCom.httpGetPrenotazioneAttuale();
  delay(1000);
}
