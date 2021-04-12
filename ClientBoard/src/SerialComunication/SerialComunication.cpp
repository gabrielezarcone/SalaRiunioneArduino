#include <Arduino.h>
#include "SerialComunication.h"
#include "../HttpService/HttpService.h"

void SerialComunication::checkMainBoard(){

    char receivedByte[1024];

    if(Serial.available()){
        Serial.readBytes(receivedByte, 1024);
        int receivedInt = atoi(receivedByte);

        if(receivedInt==NOW) { httpGetPrenotazioneAttuale(); }
        if(receivedInt==NEXT) { httpGetPrenotazioneSuccessiva(); }
        if(receivedInt==COUNT) { httpPostCounter(); }
        if(receivedInt==TEMP) { httpPostTemperature(); }
    }
}


void SerialComunication::httpGetPrenotazioneAttuale(){
    char* url;
    strcpy(url, BASE_URL);
    strcat(url, "/prenotazione/findPrenotazioneAttuale/");
    strcat(url, ARDUINO_NAME);
    http.sendRequest("GET", url);
    http.request.onReadyStateChange(SerialComunication::_handlerGetPrenotazioneAttuale);    // TODO da mandare la risposta alla board principale gestendo il JSON
}


void SerialComunication::httpGetPrenotazioneSuccessiva(){
    char* url;
    strcpy(url, BASE_URL);
    strcat(url, "/prenotazione/findPrenotazioneSuccessiva/");
    strcat(url, ARDUINO_NAME);
    http.sendRequest("GET", url);
    http.request.onReadyStateChange(SerialComunication::_handlerGetPrenotazioneSuccessiva);    // TODO da mandare la risposta alla board principale gestendo il JSON
}


void SerialComunication::httpPostCounter(){
    while(true){
        if (Serial.available()){

            char receivedByte[1024];
            Serial.readBytes(receivedByte, 1024);
            int counter = atoi(receivedByte);
            if(counter == 43){ // ASCII per +
                counter = 1;
            }
            else if (counter == 45){ // ASCII per -
                counter = -1;
            }

            String body;
            DynamicJsonDocument doc(1024);
            doc["count"] = counter;
            doc["arduinoID"] = "arduino1";
            serializeJson(doc, body);
            
            char* url;
            strcpy(url, BASE_URL);
            strcat(url, "/stanza/counter");
            http.sendRequest("POST", url, &body[0]); //inserisce anche il body facoltativo come array di caratteri
            return;
        }
        yield(); // da mettere su ogni while quando si usa ESP8266
    }
}


void SerialComunication::httpPostTemperature(){
    while(true){
        if (Serial.available()){

            char receivedByte[1024];
            Serial.readBytes(receivedByte, 1024);
            int temperature = atoi(receivedByte);

            String body;
            DynamicJsonDocument doc(1024);
            doc["temp"] = temperature;
            doc["arduinoID"] = "arduino1";
            serializeJson(doc, body);
            
            char* url;
            strcpy(url, BASE_URL);
            strcat(url, "/stanza/temperaturaStanza");
            http.sendRequest("POST", url, &body[0]); //inserisce anche il body facoltativo come array di caratteri
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
    Serial.println(NOW);
    SerialComunication::_printSerialResponseText(optParm, request, readyState);
}
void SerialComunication::_handlerGetPrenotazioneSuccessiva(void* optParm, asyncHTTPrequest* request, int readyState){
    Serial.println(NEXT);
    SerialComunication::_printSerialResponseText(optParm, request, readyState);
}