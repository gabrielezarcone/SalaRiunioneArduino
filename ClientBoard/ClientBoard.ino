/*
    Questo codice deve essere inserito all'interno della board (ESP8266) che si occuperà di effettuare le chiamate HTTP al server.
    Riceve istruzioni dalla board principale (MEGA2560) attraversolo la comunicazione seriale.
    [IMPORTANTE!] :
          Questo codice va caricato attraverso IDE arduino e non con VScode altrimenti la scheda non viene correttamente resettata e restituisce
          strani errori di allocazione di memoria
    [IMPORTANTE!] :
          Il codie non può essere troppo grosso altrimenti sfora heap
*/

#include "src/HttpService/HttpService.h"

HttpService http;  

void setup(){
  Serial.begin(115200); 
  http.setup(); 
}

void loop(){
  if(Serial.available()){
    char receivedByte[1024];
    Serial.readBytes(receivedByte, 1024);
    char url[200];
    strcpy(url, BASE_URL);
    strcat(url, receivedByte);
    strcat(url, ARDUINO_NAME);
    http.sendRequest("GET", url);
    http.request.onReadyStateChange(HttpService::printResponseText);
  }
}
