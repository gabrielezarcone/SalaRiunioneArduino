// Da esempio https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266HTTPClient/examples/BasicHttpClient/BasicHttpClient.ino

#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>
  #include <ESP8266WiFiMulti.h>
#endif
#include <WiFiClient.h>

#include "Secrets.h"


ESP8266WiFiMulti WiFiMulti;
char receivedByte[1024];

// --------------------------------------------------------------------------------------------------------
 
void setup () {
 
  Serial.begin(115200);
  // Serial.setDebugOutput(true);

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(200);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(SSID_WIFI, PASSWORD_WIFI);

}
 
void loop() {
  if (Serial.available()){
    String endpoint = Serial.readString();
    sendHttpRequest("GET", endpoint, "");
  }
  delay(2000);   

}


// --------------------------------------------------------------------------------------------------------

void sendHttpRequest(char* method, String endpoint, String body){
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    
    WiFiClient client;
    HTTPClient http;
    
    endpoint.trim(); // Importante! altrimenti la richiesta fallisce
    String url(SERVER_URL);  // Converte SERVER_URL da char[] a String
    url = url + ":" + SERVER_PORT + endpoint;
    
    if (http.begin(client, url)) {  // HTTP
      //Serial.print("[HTTP] GET...");
      Serial.println(url);
      // start connection and send HTTP header
      int httpCode = http.sendRequest(method, body);

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.println(payload);
        }
      } 
      else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    }
    else {
      Serial.printf("[HTTP] Unable to connect\n");
    }
  }
}
