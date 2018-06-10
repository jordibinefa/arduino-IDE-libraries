/*
Connection schematic at http://www.binefa.cat/php/doc/lib-eCat02/
*/

#include <ecat.h>
#include <LiquidCrystal.h>

Ecat ecat;
lcdP1_init();
lcdP2_init();

void setup(){
  lcdP1.begin(16, 2);
  lcdP1.print("everybody from");
  lcdP2.begin(16, 2);
  lcdP2.print("Happy New Year");
}

void loop(){
  lcdP1.setCursor(0, 1);
  lcdP1.print("electronics.cat");
  lcdP2.setCursor(0, 1);
  lcdP2.print("2015 !!!!  to");
}
