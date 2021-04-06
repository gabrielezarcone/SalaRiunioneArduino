#include <Arduino.h>
#include <LCDWIKI_GUI.h> //Core graphics library
#include <LCDWIKI_KBV.h> //Hardware-specific library

#include "Schermo.h"


Schermo::Schermo()
    : mylcd(ILI9486,A3,A2,A1,A0,A4) {
    _statusStanza = 1;
}



void Schermo::setup(){
    Serial.begin(9600);
    mylcd.Init_LCD();
    mylcd.Set_Rotation(1); // orientazione landscape
    mylcd.Fill_Screen(BLACK);
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
        occupato(yPartenza, "Descrizione riunione");
    }
    
}

void Schermo::occupato(int yPartenza, String titoloRiunione){
    // più corto di quello libero perchè deve contenere anche organizzatore
    int altezzaRiquadro = 185; 
    mylcd.Set_Draw_color(RED);
    mylcd.Fill_Rectangle(0,yPartenza,480,yPartenza+altezzaRiquadro);
    mylcd.Set_Text_colour(BLACK);
    mylcd.Set_Text_Mode(1); // SFONDO TRASPARENTE
    mylcd.Set_Text_Size(4);
    mylcd.Print_String(titoloRiunione, 50, yPartenza+80);
    organizzatore("Luca Verdi", yPartenza+altezzaRiquadro);
}

void Schermo::libero(int yPartenza){
    int altezzaRiquadro = 210;
    mylcd.Set_Draw_color(GREEN);
    mylcd.Fill_Rectangle(0,yPartenza,480,yPartenza+altezzaRiquadro);
    mylcd.Set_Text_colour(BLACK);
    mylcd.Set_Text_Mode(1); // SFONDO TRASPARENTE
    mylcd.Set_Text_Size(4);
    mylcd.Print_String("Nessuna riunione", 50, yPartenza+80);
    mylcd.Print_String("in corso", 140, yPartenza+120);
}

void Schermo::riquadroSuccessivo(int yPartenza){
    int altezzaRiquadro = 65;
    mylcd.Set_Draw_color(CYAN);
    mylcd.Fill_Rectangle(0,yPartenza,480,yPartenza+altezzaRiquadro);
    mylcd.Set_Text_colour(BLACK);
    mylcd.Set_Text_Mode(1); // SFONDO TRASPARENTE
    mylcd.Set_Text_Size(3);
    mylcd.Print_String("Prossima riunione", 110, yPartenza+25);
    orario(16, 30, yPartenza, DARK_CYAN);
    organizzatore("Mario Rossi", yPartenza+altezzaRiquadro);
}

void Schermo::orario(int hh, int mm, int yPartenza, uint16_t color){
    int altezzaRiquadro = 65;
    char hhString [2];
    char mmString [2];
    sprintf(hhString,"%d",hh); 
    sprintf(mmString,"%d",mm);
    mylcd.Set_Draw_color(color);
    mylcd.Fill_Rectangle(0,yPartenza,100,yPartenza+altezzaRiquadro);
    mylcd.Set_Text_colour(BLACK);
    mylcd.Set_Text_Mode(1); // SFONDO TRASPARENTE
    mylcd.Set_Text_Size(3);
    mylcd.Print_String(hhString, 10, yPartenza+25);
    mylcd.Print_String(":", 41, yPartenza+25);
    mylcd.Print_String(mmString, 53, yPartenza+25);
}

void Schermo::organizzatore(String nome, int yPartenza){
    int altezzaRiquadro = 25;
    mylcd.Set_Draw_color(GREY);
    mylcd.Fill_Rectangle(0,yPartenza,480,yPartenza+altezzaRiquadro);
    mylcd.Set_Text_colour(DARK_CYAN);
    mylcd.Set_Text_Mode(1); // SFONDO TRASPARENTE
    mylcd.Set_Text_Size(2);
    mylcd.Print_String("Organizzatore:", 10, yPartenza+5);
    mylcd.Set_Text_colour(BLACK);
    mylcd.Print_String(nome, 180, yPartenza+5);
}