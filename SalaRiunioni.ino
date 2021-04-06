#include "src/Laser/Laser.h"
#include "src/LaserDetector/LaserDetector.h"
#include "src/LaserDetector/ObstacleAvoid.h"
#include "src/SensorePassaggio/SensorePassaggio.h"
#include <LCDWIKI_GUI.h> //Core graphics library
#include <LCDWIKI_KBV.h> //Hardware-specific library

#define BLACK     0x0000
#define BLUE      0x001F
#define RED       0xD28C
#define GREEN     0x6DC9
#define CYAN      0x779E
#define DARK_CYAN 0x4CF3
#define MAGENTA   0xF81F
#define YELLOW    0xFFE0
#define GREY      0xD6BB 
#define WHITE     0xFFFF

#define ROTATION 1

#define LASER_PIN1 6
#define LASER_PIN2 7
#define DETECTOR_PIN1 A3
#define DETECTOR_PIN2 5

SensorePassaggio sensorePorta(LASER_PIN1, LASER_PIN2, DETECTOR_PIN1, DETECTOR_PIN2);
LCDWIKI_KBV mylcd(ILI9486,A3,A2,A1,A0,A4); //model,cs,cd,wr,rd,reset

void setup() {
  Serial.begin(9600);
  mylcd.Init_LCD();
  mylcd.Set_Rotation(ROTATION);
  mylcd.Fill_Screen(BLACK);
  
  mylcd.Set_Draw_color(GREEN);
  mylcd.Fill_Rectangle(0,0,480,210);
  
  mylcd.Set_Draw_color(CYAN);
  mylcd.Fill_Rectangle(0,215,480,280);
  
  mylcd.Set_Draw_color(GREY);
  mylcd.Fill_Rectangle(0,280,480,305);
}

void loop() {
  //sensorePorta.controllaEntrata();
  //sensorePorta.controllaUscita();
}