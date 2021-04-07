/*
    Questo codice deve essere inserito all'interno della board (ESP8266) che si occuperà di effettuare le chiamate HTTP al server.
    Riceve istruzioni dalla board principale (MEGA2560) attraversolo la comunicazione seriale.
*/

#if !( defined(ESP8266) ||  defined(ESP32) )
  #error This code is intended to run on the ESP8266 or ESP32 platform! Please check your Tools->Board setting.
#endif

#if (ESP8266)
  #include <ESP8266WiFi.h>
#elif (ESP32)
  #include <WiFi.h>
#endif

#include <AsyncHTTPRequest_Generic.h>           // https://github.com/khoih-prog/AsyncHTTPRequest_Generic

int wifiStatus;     // the Wifi radio's status (WL_CONNECTED se connesso)
AsyncHTTPRequest request;

const char* ssid        = "";
const char* password    = "";

char receivedString[10];  

void setup(){
    Serial1.begin(9600);  
    Serial.begin(115200);
    while (!Serial);

    WiFi.mode(WIFI_STA);

    WiFi.begin(ssid, password);
    
    Serial.println("Connecting to WiFi SSID: " + String(ssid));
}

void loop(){
    if(Serial1.available()){
      receivedString = Serial.read();
    }

    if(receivedString=="now") { httpGetPrenotazioneAttuale(); }
    if(receivedString=="next") { httpGetPrenotazioneSuccessiva(); }
    if(receivedString=="count") { httpPostCounter(); }
    if(receivedString=="temp") { httpPostTemperature(); }
}

void httpGetPrenotazioneAttuale(){
    // TODO Chimata http a /findPrenotazioneAttuale
    Serial1.print("Json ricevuto da http");
}
void httpGetPrenotazioneSuccessiva(){
    // TODO Chimata http a /findPrenotazioneSuccessiva 
    Serial1.print("Json ricevuto da http");
}
void httpPostCounter(){
    while(Serial1.available()){
        int counter = Serial1.read();
        // TODO Chimata http a /counter con variabile counter nel body
    }
}
void httpPostTemperature(){
    while(Serial1.available()){
        int temperature = Serial1.read();
        // TODO Chimata http a /temperaqturaStanza  con la temperatura nel body
    }
} 


void sendRequest(String method, String url) {
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

void printResponseText(void* optParm, AsyncHTTPRequest* request, int readyState) {
  (void) optParm;
  
  if (readyState == readyStateDone) {
    Serial.println("\n**************************************");
    Serial.println(request->responseText());
    Serial.println("**************************************");
    
    request->setDebug(false);
  }
}
