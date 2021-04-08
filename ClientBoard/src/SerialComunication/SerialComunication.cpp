#include <Arduino.h>
#include "SerialComunication.h"
#include "../HttpService/HttpService.h"

void SerialComunication::checkMainBoard(){
    
    int receivedString;

    if(Serial1.available()){
        receivedString = Serial.read();
    }

    if(receivedString==NOW) { httpGetPrenotazioneAttuale(); }
    if(receivedString==NEXT) { httpGetPrenotazioneSuccessiva(); }
    if(receivedString==COUNT) { httpPostCounter(); }
    if(receivedString==TEMP) { httpPostTemperature(); }
}

void SerialComunication::httpGetPrenotazioneAttuale(){
    http.sendRequest("GET", "http://192.168.1.136:8050/prenotazione/findPrenotazioneAttuale/arduino1");
    http.request.onReadyStateChange(SerialComunication::_printSerialResponseText);    // TODO da mandare la risposta alla board principale gestendo il JSON
    Serial.print("Json ricevuto da http");
}
void SerialComunication::httpGetPrenotazioneSuccessiva(){
    http.sendRequest("GET", "/findPrenotazioneSuccessiva");
    http.request.onReadyStateChange(SerialComunication::_printSerialResponseText);    // TODO da mandare la risposta alla board principale gestendo il JSON
    Serial1.print("Json ricevuto da http");
}
void SerialComunication::httpPostCounter(){
    while(Serial1.available()){
        int counter = Serial1.read();
        http.sendRequest("POST", "/counter");
        // TODO inserire counter nel body
    }
}
void SerialComunication::httpPostTemperature(){
    while(Serial1.available()){
        int temperature = Serial1.read();
        http.sendRequest("POST", "/temperaturaStanza");
        // TODO inserire temperatura nel body
    }
} 


void SerialComunication::_printSerialResponseText(void* optParm, asyncHTTPrequest* request, int readyState) {
  (void) optParm;
  
  if (readyState == 4) {
    Serial.println("\n**************************************");
    Serial.println(request->responseText());
    Serial.println("**************************************");
    
    request->setDebug(false);
  }
}