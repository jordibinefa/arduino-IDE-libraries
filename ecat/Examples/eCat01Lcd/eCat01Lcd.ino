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
  lcdP1.print("ecat.h - v");lcdP1.print(ecat.fVersion());
  lcdP2.begin(16, 2);
  lcdP2.print("electronics.cat");
}

void loop(){
  lcdP1.setCursor(0, 1);
  lcdP1.print("PORT1 ");lcdP1.print(millis()/1000);lcdP1.print(" seconds");
  lcdP2.setCursor(0, 1);
  lcdP2.print("PORT2 ");lcdP2.print(millis()/1000);lcdP2.print(" seconds");
}
