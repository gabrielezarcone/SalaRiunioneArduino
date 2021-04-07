#ifndef HttpService_h
#define HttpService_h

#include <Arduino.h>

#if !( defined(ESP8266) ||  defined(ESP32) )
  #error This code is intended to run on the ESP8266 or ESP32 platform! Please check your Tools->Board setting.
#endif

#if (ESP8266)
  #include <ESP8266WiFi.h>
#elif (ESP32)
  #include <WiFi.h>
#endif

#include <AsyncHTTPRequest_Generic.h>           // https://github.com/khoih-prog/AsyncHTTPRequest_Generic

class HttpService{
    public:     
        AsyncHTTPRequest request;
        int wifiStatus;     // the Wifi radio's status (WL_CONNECTED se connesso)
        void setup();
        void sendRequest(String method, String url);
        void printResponseText(void* optParm, AsyncHTTPRequest* request, int readyState);
};

#endif