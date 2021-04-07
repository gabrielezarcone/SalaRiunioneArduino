#include <Arduino.h>
#include "HttpService.h"

#if !( defined(ESP8266) ||  defined(ESP32) )
  #error This code is intended to run on the ESP8266 or ESP32 platform! Please check your Tools->Board setting.
#endif

#if (ESP8266)
  #include <ESP8266WiFi.h>
#elif (ESP32)
  #include <WiFi.h>
#endif

#include <AsyncHTTPRequest_Generic.h>           // https://github.com/khoih-prog/AsyncHTTPRequest_Generic



void HttpService::sendRequest(String method, String url) {
    // per gestire la risposta usare:
    // --- request.onReadyStateChange(funzione) ---
    // dove funzione è solo il nome della funzione da lanciare all'arrivo della risposta con parametri: (void* optParm, AsyncHTTPRequest* request, int readyState)
    // es. request.onReadyStateChange(printResponseText)
    static bool requestOpenResult;

    if (request.readyState() == readyStateUnsent || request.readyState() == readyStateDone){
    // Apre la request HTTP:      
    requestOpenResult = request.open(method, url);

    if (requestOpenResult){
        // Only send() if open() returns true, or crash
        request.send();
    }
    else{
        Serial.println("Can't send bad request");
    }
    }
    else{
    Serial.println("Can't send request");
    }
}

void HttpService::printResponseText(void* optParm, AsyncHTTPRequest* request, int readyState) {
  (void) optParm;
  
  if (readyState == readyStateDone) {
    Serial.println("\n**************************************");
    Serial.println(request->responseText());
    Serial.println("**************************************");
    
    request->setDebug(false);
  }
}