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
            
            http.sendRequest("POST", "http://192.168.1.136:8050/stanza/counter", &body[0]); //inserisce anche il body facoltativo come array di caratteri
            return;
        }
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

    Serial.println("now-response");

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

    Serial.println(descrizione);
    Serial.println(oraInizio);
    Serial.println(oraFine);
    Serial.println(anagrafica);
    
    request->setDebug(false);
  }
}


void SerialComunication::_handlerGetPrenotazioneSuccessiva(void* optParm, asyncHTTPrequest* request, int readyState){
    
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

    Serial.println("next-response");

    if(request->responseHTTPcode() == 404){
        const char* message = doc["message"];
        Serial.println("404");
        Serial.println(message);
    }

    const char* descrizione = doc["descrizione"];
    const char* oraInizio = doc["oraInizio"];
    const char* oraFine = doc["oraFine"];
    const char* anagrafica = doc["anagrafica"];

    Serial.println(descrizione);
    Serial.println(oraInizio);
    Serial.println(oraFine);
    Serial.println(anagrafica);
    
    request->setDebug(false);
  }
}