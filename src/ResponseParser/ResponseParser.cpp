#include "ResponseParser.h"

ResponseParser::ResponseParser(Schermo schermo){
    lcd = schermo;
}

DynamicJsonDocument ResponseParser::parseJson(String jsonString){
    DynamicJsonDocument doc(2048);
    // converte la String un char array
    int str_len = jsonString.length() + 1; 
    const char json[str_len];
    jsonString.toCharArray(json, str_len);
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


void ResponseParser::checkResponses(){
}

void ResponseParser::onNowReceived(Schermo schermo){
    // deve leggere il valore ceh si trova su serial2 dopo il comando
    // poi deve parsare il json letto
    // infine aggiornare il display
    String received = Serial2.readStringUntil('\n');
    Serial.println(received);
    received.trim();
    DynamicJsonDocument json = parseJson(received);
    const char* descrizione = json["descrizione"].as<char*>();
    const char* oraInizio = json["oraInizio"].as<char*>();
    const char* oraFine = json["oraFine"].as<char*>();
    const char* anagrafica = json["anagrafica"].as<char*>();
    const char* message = json["message"].as<char*>();
    bool isLibero = false;
    if(message!=NULL){
        isLibero=true;
    }
    Serial.print("descrizione json: ");
    Serial.println(descrizione);
    schermo.updateNow(descrizione, oraInizio, oraFine, anagrafica, isLibero);
}

void ResponseParser::onNextReceived(){
    // deve leggere il valore ceh si trova su serial2 dopo il comando
    // poi deve parsare il json letto
    // infine aggiornare il display
    String received = Serial2.readStringUntil('\n');
    Serial.println(received);
    DynamicJsonDocument json = parseJson(received);
    const char* descrizione = json["descrizione"];
    const char* oraInizio = json["oraInizio"];
    const char* oraFine = json["oraFine"];
    const char* anagrafica = json["anagrafica"];
    lcd.updateNext(descrizione, oraInizio, oraFine, anagrafica);
}
