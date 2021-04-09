#ifndef ResponseParser_h
#define ResponseParser_h

#include <Arduino.h>
#include <ArduinoJson.h>  // https://arduinojson.org/  --- Fornisce serializer/deserializer per JSON --- 
#include "../Comandi.h"

class ResponseParser{
    public:
        DynamicJsonDocument ResponseParser::parseJson(String jsonString);
        void checkResponses();
        void onNowReceived();
        void onNextReceived();
};

#endif