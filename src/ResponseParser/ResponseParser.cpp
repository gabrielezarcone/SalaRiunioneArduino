#include "ResponseParser.h"

ResponseParser::ResponseParser(Schermo schermo){
    lcd = schermo;
}

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


void ResponseParser::checkResponses(){
    if (Serial2.available()){
        int command = Serial2.read();

        if (command == NOW) { onNowReceived(); }
        else if(command == NEXT) { onNextReceived(); }
    }

}

void ResponseParser::onNowReceived(){
    // deve leggere il valore ceh si trova su serial2 dopo il comando
    // poi deve parsare il json letto
    // infine aggiornare il display
    String received = Serial2.readString();
    DynamicJsonDocument json = parseJson(received);
    const char* descrizione = json["descrizione"];
    const char* oraInizio = json["oraInizio"];
    const char* oraFine = json["oraFine"];
    const char* anagrafica = json["anagrafica"];
    lcd.updateNow(descrizione, oraInizio, oraFine, anagrafica);
}

void ResponseParser::onNextReceived(){
    // deve leggere il valore ceh si trova su serial2 dopo il comando
    // poi deve parsare il json letto
    // infine aggiornare il display
}
