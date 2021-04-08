#include "HttpService.h"


void HttpService::setup(){
    Serial.begin(115200);
    while (!Serial);
    WiFi.setAutoConnect(true);
    WiFi.begin(SSID_WIFI, PASSWORD_WIFI);
    Serial.println("Connecting to WiFi SSID: " + String(SSID_WIFI));
    while(WiFi.status() != WL_CONNECTED){
      wifiManager.setDebugOutput(false);
      wifiManager.setConfigPortalTimeout(180);
      Serial.println("Connecting with WiFiManager");
      wifiManager.autoConnect("ESP8266", "ESP8266");
      yield();
    }
    request.setDebug(true);
}

void HttpService::sendRequest(char* method, char* url, char* body) {
  // per gestire la risposta usare:
  // --- request.onReadyStateChange(funzione) ---
  // dove funzione è solo il nome della funzione da lanciare all'arrivo della risposta con parametri: (void* optParm, AsyncHTTPRequest* request, int readyState)
  // es. request.onReadyStateChange(printResponseText)
  static bool requestOpenResult;

  if (request.readyState() == 0 || request.readyState() == 4){
    // Apre la request HTTP:      
    requestOpenResult = request.open(method, url);

    if (requestOpenResult){
      // Only send() if open() returns true, or crash
      request.send(body);
    }
    else{
      Serial.println("Can't send bad request");
    }
  }
  else{
    Serial.println("Can't send request");
  }
}

void HttpService::printResponseText(void* optParm, asyncHTTPrequest* request, int readyState) {
  (void) optParm;
  
  if (readyState == 4) {
    Serial.println("\n**************************************");
    Serial.println(request->responseText());
    Serial.println("**************************************");
    
    request->setDebug(false);
  }
}