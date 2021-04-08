#ifndef HttpService_h
#define HttpService_h

#include <Arduino.h>
#include "Secrets.h"

#if defined(ESP8266)
  #include <ESP8266WiFi.h>
#elif defined(ESP32)
  #include <WiFi.h>
#else
  #error Invalid platform
#endif

#include <WiFiManager.h>
#include <asyncHTTPrequest.h>  // https://github.com/boblemaire/asyncHTTPrequest/wiki

class HttpService{
    public:     
        WiFiManager wifiManager;
        asyncHTTPrequest request;
        void setup();
        void sendRequest(char* method, char* url);
        void printResponseText(void* optParm, asyncHTTPrequest* request, int readyState);
};

#endif