#ifndef ResponseParser_h
#define ResponseParser_h

#include <Arduino.h>
#include <ArduinoJson.h>  // https://arduinojson.org/  --- Fornisce serializer/deserializer per JSON --- 
#include "../Comandi.h"
#include "../Schermo/Schermo.h"

class ResponseParser{
    public:
        ResponseParser(Schermo schermo);
        Schermo lcd;
        DynamicJsonDocument ResponseParser::parseJson(String jsonString);
        void checkResponses();
        void onNowReceived();
        void onNextReceived();
};

#endif