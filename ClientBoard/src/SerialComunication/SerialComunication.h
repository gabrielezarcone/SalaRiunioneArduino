#ifndef SerialComunication_h
#define SerialComunication_h

#include <Arduino.h>
#include "../HttpService/HttpService.h"

enum Status {
    NOW,
    NEXT,
    COUNT,
    TEMP
};

// La classe usa Serial1 per funzionare quindi inizializzarlo nel setup
class SerialComunication{
    public: 
        HttpService http;
        void checkMainBoard();                  // Gestisce i messaggi che arrivano dalla board principale, se ci sono.
        void httpGetPrenotazioneAttuale();      // Gestisce la GET verso il server per ricevere la prenotazione attuale
        void httpGetPrenotazioneSuccessiva();   // Gestisce la GET verso il server per ricevere la prenotazione successiva
        void httpPostCounter();                 // Gestisce la POST verso il server per inviare il counter
        void httpPostTemperature();             // Gestisce la POST verso il server per inviare la temperatura
    private:
        static void _printSerialResponseText(void* optParm, asyncHTTPrequest* request, int readyState);
        static void _handlerGetPrenotazioneAttuale(void* optParm, asyncHTTPrequest* request, int readyState);
        static void _handlerGetPrenotazioneSuccessiva(void* optParm, asyncHTTPrequest* request, int readyState);
};

#endif