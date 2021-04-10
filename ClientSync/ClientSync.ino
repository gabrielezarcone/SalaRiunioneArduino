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

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(SSID_WIFI, PASSWORD_WIFI);

}
 
void loop() {
  Serial.println("ready");
  if (Serial.available()){
    //Serial.readBytes(receivedByte, 1024);
    //char url[] = "http://jsonplaceholder.typicode.com/users/";
    //strcat(url, receivedByte);
    //String urlString(url); // converte char* in String
    String url = "http://jsonplaceholder.typicode.com/users/";
    String num = Serial.readString();
    getRequest(url+num);
  }
  delay(3000);   

}


// --------------------------------------------------------------------------------------------------------

void getRequest(String url){
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    
    WiFiClient client;
    HTTPClient http;
    
    url.trim(); // Importante! altrimenti la richiesta fallisce
    
    if (http.begin(client, url)) {  // HTTP
      Serial.print("[HTTP] GET...");
      Serial.print(url);
      Serial.print("--\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

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

char* concatBaseAndEndpoint(char* endpoint){
  char* url;
  strcpy(url, BASE_URL);
  strcat(url, endpoint);
  return url;
}
