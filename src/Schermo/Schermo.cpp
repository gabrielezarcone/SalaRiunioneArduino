#include <Arduino.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <MCUFRIEND_kbv.h>   // Hardware-specific library

#include "Schermo.h"


Schermo::Schermo(){
}


void Schermo::setStatusStanza(int statusStanza){
    _statusStanza = statusStanza;
}


void Schermo::setup(){
    uint16_t ID = tft.readID();
    if (ID == 0xD3D3) ID = 0x9481; //force ID if write-only display
    tft.begin(ID);
    tft.setRotation(1); // orientazione landscape
    tft.fillScreen(BLACK);
}

void Schermo::renderLCD(){
    riquadroInCorso(0); // questo riquadro mostra le info della riunione in corso
    riquadroSuccessivo(215); // questo riquadro mostra le info della prossima riunione
}

void Schermo::riquadroInCorso(int yPartenza){
    Serial.println(_statusStanza);
    if (_statusStanza == LIBERO){
        libero(yPartenza);
    }
    else{
        occupato(yPartenza);
    }
    
}

void Schermo::occupato(int yPartenza){
    // più corto di quello libero perchè deve contenere anche organizzatore
    int altezzaRiquadro = 185; 
    tft.fillRect(0,yPartenza,480,altezzaRiquadro, RED);
    printCenterString(_nowDescrizione, 0, yPartenza+80, 4, WHITE );
    organizzatore(_nowOrganizzatore, yPartenza+altezzaRiquadro);
}

void Schermo::libero(int yPartenza){
    int altezzaRiquadro = 210;
    tft.fillRect(0,yPartenza,480,altezzaRiquadro, GREEN);
    printCenterString("Nessuna riunione", 0, yPartenza+80, 4, BLACK );
    printCenterString("in corso", 0, yPartenza+120, 4, BLACK );
}

void Schermo::riquadroSuccessivo(int yPartenza){
    int altezzaRiquadro = 65;
    tft.fillRect(0,yPartenza,480,altezzaRiquadro, CYAN);
    printString(_nextDescrizione, 110, yPartenza+25, 3, BLACK );
    orario(_nextInizio, yPartenza, DARK_CYAN);
    organizzatore(_nextOrganizzatore, yPartenza+altezzaRiquadro);
}

void Schermo::orario(String orario, int yPartenza, uint16_t color){
    int altezzaRiquadro = 65;
    tft.fillRect(0,yPartenza,100,altezzaRiquadro, color);
    printString(orario, 10, yPartenza+25, 3, BLACK );
}

void Schermo::organizzatore(String nome, int yPartenza){
    int altezzaRiquadro = 25;
    tft.fillRect(0,yPartenza,480,altezzaRiquadro, GREY);
    printString("Organizzatore:", 10, yPartenza+5, 2, DARK_GREY );
    printString(nome, 180, yPartenza+5, 2, BLACK );
}

void Schermo::printString(String str, int xCursor, int yCursor , int size, uint16_t color){
    tft.setCursor( xCursor, yCursor );
    tft.setTextColor(color);
    tft.setTextSize(size);
    tft.print(str);
}

void Schermo::printCenterString(const String buf, int x, int y, int size, uint16_t color){
    int16_t x1, y1;
    uint16_t w, h;
    tft.setTextColor(color);
    tft.setTextSize(size);
    tft.getTextBounds(buf, x, y, &x1, &y1, &w, &h); // calcola la lunghezza della stringa
    tft.setCursor( (tft.width()-w)/2, y );
    tft.print(buf);
}

void Schermo::updateNow(String descrizione, String oraInizio, String oraFine, String anagrafica, bool isLibero){
    // aggiorna il riquadro in corso
    if (isLibero){
        _statusStanza = LIBERO;
    }
    else{
        _statusStanza = OCCUPATO;
    }
    _nowDescrizione = descrizione;
    if(oraInizio.length>=5){
        _nowInizio = oraInizio.substring(0,5);
    }
    else{
        _nowInizio = oraInizio;
    }
    if(oraInizio.length>=5){
        _nowFine = oraInizio.substring(0,5);
    }
    else{
        _nowFine = oraFine;
    }
    _nowOrganizzatore = anagrafica;
    renderLCD();
}

void Schermo::updateNext(String descrizione, String oraInizio, String oraFine, String anagrafica){
    // aggiorna il riquadro successivo
    _nextDescrizione = descrizione;
    if(oraInizio.length>=5){
        _nextInizio = oraInizio.substring(0,5);
    }
    else{
        _nextInizio = oraInizio;
    }
    if(oraInizio.length>=5){
        _nextFine = oraInizio.substring(0,5);
    }
    else{
        _nextFine = oraFine;
    }
    _nextOrganizzatore = anagrafica;
    renderLCD();
}