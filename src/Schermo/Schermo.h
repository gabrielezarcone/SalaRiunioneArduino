#ifndef Schermo_h
#define Schermo_h

#include <Arduino.h>
#include <LCDWIKI_GUI.h> //Core graphics library
#include <LCDWIKI_KBV.h> //Hardware-specific library


#define BLACK     0x0000
#define RED       0xD28C
#define GREEN     0x6DC9
#define CYAN      0x779E
#define DARK_CYAN 0x4CF3
#define GREY      0xD6BB 
#define DARK_GREY 0x5AEB 
#define WHITE     0xFFFF


class Schermo{
    public: 
        Schermo();
        LCDWIKI_KBV mylcd;
        void setStatusStanza(int statusStanza);
        void setup();
        void renderLCD();
        void riquadroInCorso(int yPartenza);
        void occupato(int yPartenza, String titoloRiunione);
        void libero(int yPartenza);
        void riquadroSuccessivo(int yPartenza);
        void orario(int hh, int mm, int yPartenza, uint16_t color);
        void organizzatore(String nome, int yPartenza);
    private:
        int _statusStanza; // 0 se stanza libera, 1 se occupata
};

#endif