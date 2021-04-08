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

void SerialComunication::_handlerGetPrenotazioneAttuale(void* optParm, asyncHTTPrequest* request, int readyState){
    
  (void) optParm;
  
  if (readyState == 4) {

    DynamicJsonDocument doc(1024);

    // converte la String restituita da responseText() in un char array
    String jsonString = request->responseText();
    char* json;
    json = &jsonString[0];

    DeserializationError error = deserializeJson(doc, json);

    // Test if parsing succeeds.
    if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
    }

    if(request->responseHTTPcode() == 404){
        const char* message = doc["message"];
        Serial.println("now");
        Serial.println("404");
        Serial.println(message);
    }

    const char* descrizione = doc["descrizione"];
    const char* oraInizio = doc["oraInizio"];
    const char* oraFine = doc["oraFine"];
    const char* anagrafica = doc["anagrafica"];

    Serial.println("now");
    Serial.println(descrizione);
    Serial.println(oraInizio);
    Serial.println(oraFine);
    Serial.println(anagrafica);
    
    request->setDebug(false);
  }
}