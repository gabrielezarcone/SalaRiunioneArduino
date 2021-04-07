#include <Arduino.h>
#include "SerialComunication.h"
#include "../HttpService/HttpService.h"

void SerialComunication::checkMainBoard(){
    if(Serial1.available()){
      receivedString = Serial.read();
    }

    if(receivedString=="now") { httpGetPrenotazioneAttuale(); }
    if(receivedString=="next") { httpGetPrenotazioneSuccessiva(); }
    if(receivedString=="count") { httpPostCounter(); }
    if(receivedString=="temp") { httpPostTemperature(); }
}

void SerialComunication::httpGetPrenotazioneAttuale(){
    http.sendRequest("GET", "/findPrenotazioneAttuale");
    http.request.onReadyStateChange(printResponseText);    // TODO da mandare la risposta alla board principale gestendo il JSON
    Serial1.print("Json ricevuto da http");
}
void SerialComunication::httpGetPrenotazioneSuccessiva(){
    http.sendRequest("GET", "/findPrenotazioneSuccessiva");
    http.request.onReadyStateChange(printResponseText);    // TODO da mandare la risposta alla board principale gestendo il JSON
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