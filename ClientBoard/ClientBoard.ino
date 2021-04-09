/*
    Questo codice deve essere inserito all'interno della board (ESP8266) che si occuperà di effettuare le chiamate HTTP al server.
    Riceve istruzioni dalla board principale (MEGA2560) attraversolo la comunicazione seriale.
    [IMPORTANTE!] :
          Questo codice va caricato attraverso IDE arduino e non con VScode altrimenti la scheda non viene correttamente resettata e restituisce
          strani errori di allocazione di memoria
*/

#include "src/SerialComunication/SerialComunication.h"

SerialComunication serialCom;

char receivedString[10];  

void setup(){
  Serial.begin(9600); 
  serialCom.http.setup(); 
}

void loop(){
  serialCom.checkMainBoard();
}
