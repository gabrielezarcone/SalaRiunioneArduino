#ifndef SerialComunication_h
#define SerialComunication_h

#include <Arduino.h>
#include "../HttpService/HttpService.h"

// La classe usa Serial1 per funzionare quindi inizializzarlo nel setup
class SerialComunication{
    public: 
        HttpService http;
        void checkMainBoard();                  // Gestisce i messaggi che arrivano dalla board principale, se ci sono.
        void httpGetPrenotazioneAttuale();      // Gestisce la GET verso il server per ricevere la prenotazione attuale
        void httpGetPrenotazioneSuccessiva();   // Gestisce la GET verso il server per ricevere la prenotazione successiva
        void httpPostCounter();                 // Gestisce la POST verso il server per inviare il counter
        void httpPostTemperature();             // Gestisce la POST verso il server per inviare la temperatura
};

#endif