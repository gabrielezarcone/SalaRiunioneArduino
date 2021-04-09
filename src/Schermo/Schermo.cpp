#include <Arduino.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <MCUFRIEND_kbv.h>   // Hardware-specific library

#include "Schermo.h"


Schermo::Schermo(){
    _statusStanza = 1;
}


void Schermo::setStatusStanza(int statusStanza){
    _statusStanza = statusStanza;
}


void Schermo::setup(){
    Serial.begin(9600);
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
    if (_statusStanza == 0){
        libero(yPartenza);
    }
    else{
        occupato(yPartenza, "Descrizione lunga della riunione");
    }
    
}

void Schermo::occupato(int yPartenza, String titoloRiunione){
    // più corto di quello libero perchè deve contenere anche organizzatore
    int altezzaRiquadro = 185; 
    tft.fillRect(0,yPartenza,480,altezzaRiquadro, RED);
    printCenterString(titoloRiunione, 0, yPartenza+80, 4, BLACK );
    organizzatore("Luca Verdi", yPartenza+altezzaRiquadro);
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
    printString("Prossima riunione", 110, yPartenza+25, 3, BLACK );
    orario(16, 30, yPartenza, DARK_CYAN);
    organizzatore("Mario Rossi", yPartenza+altezzaRiquadro);
}

void Schermo::orario(int hh, int mm, int yPartenza, uint16_t color){
    int altezzaRiquadro = 65;
    char hhString [2];
    char mmString [2];
    sprintf(hhString,"%d",hh); 
    sprintf(mmString,"%d",mm);
    tft.fillRect(0,yPartenza,100,altezzaRiquadro, color);
    printString(hhString, 10, yPartenza+25, 3, BLACK );
    printString(":", 41, yPartenza+25, 3, BLACK );
    printString(mmString, 53, yPartenza+25, 3, BLACK );
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

void Schermo::updateNow(String descrizione, String oraInizio, String oraFine, String anagrafica){
    // aggiorna il riquadro in corso
}