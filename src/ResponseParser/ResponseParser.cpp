#include "ResponseParser.h"

DynamicJsonDocument ResponseParser::parseJson(String jsonString){
    DynamicJsonDocument doc(1024);
    // converte la String un char array
    char* json;
    json = &jsonString[0];
    // ------------------------
    DeserializationError error = deserializeJson(doc, json);
    // Test if parsing succeeds.
    if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
    }
    return doc;

    /* ES: Json Prenotazione
        const char* descrizione = doc["descrizione"];
        const char* oraInizio = doc["oraInizio"];
        const char* oraFine = doc["oraFine"];
        const char* anagrafica = doc["anagrafica"]; 
    */
}
