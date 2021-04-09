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
    http.request.onReadyStateChange(SerialComunication::_handlerGetPrenotazioneAttuale);    // TODO da mandare la risposta alla board principale gestendo il JSON
}


void SerialComunication::httpGetPrenotazioneSuccessiva(){
    http.sendRequest("GET", "http://192.168.1.136:8050/prenotazione/findPrenotazioneSuccessiva/arduino1");
    http.request.onReadyStateChange(SerialComunication::_handlerGetPrenotazioneSuccessiva);    // TODO da mandare la risposta alla board principale gestendo il JSON
}


void SerialComunication::httpPostCounter(){
    while(true){
        if (Serial.available()){
            int counter = Serial.read();

            String body;
            DynamicJsonDocument doc(1024);
            doc["count"] = counter;
            doc["arduinoID"] = "arduino1";
            serializeJson(doc, body);
            
            Serial.println(body);
            http.sendRequest("POST", "http://192.168.1.136:8050/stanza/counter", &body[0]); //inserisce anche il body facoltativo come array di caratteri
            return;
        }
        yield(); // da mettere su ogni while quando si usa ESP8266
    }
}


void SerialComunication::httpPostTemperature(){
    while(true){
        if (Serial.available()){
            int temperature = Serial.read();

            String body;
            DynamicJsonDocument doc(1024);
            doc["temp"] = temperature;
            doc["arduinoID"] = "arduino1";
            serializeJson(doc, body);
            
            http.sendRequest("POST", "http://192.168.1.136:8050/stanza/temperaturaStanza", &body[0]); //inserisce anche il body facoltativo come array di caratteri
            return;
        }
        yield();
    }
} 


void SerialComunication::_printSerialResponseText(void* optParm, asyncHTTPrequest* request, int readyState) {
  (void) optParm;
  
  if (readyState == 4) {
    Serial.println(request->responseText());
    request->setDebug(false);
  }
}


void SerialComunication::_handlerGetPrenotazioneAttuale(void* optParm, asyncHTTPrequest* request, int readyState){
    Serial.println("now");
    SerialComunication::_printSerialResponseText(optParm, request, readyState);
}
void SerialComunication::_handlerGetPrenotazioneSuccessiva(void* optParm, asyncHTTPrequest* request, int readyState){
    Serial.println("next");
    SerialComunication::_printSerialResponseText(optParm, request, readyState);
}