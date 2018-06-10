/*
Connection schematic at 2nd part of
http://www.binefa.cat/php/doc/lib-eCat03/
*/

#include <ecat.h>
#include <LiquidCrystal.h>

Ecat ecat;
lcdP1_init();

void setup(){
  lcdP1.begin(16, 2);
  ecat.vUltrasonicSensorP2b0b1_init();
  ecat.vUltrasonicSensorP2b2b3_init();
}

void loop(){
  lcdP1.setCursor(0, 0);
  lcdP1.print("P2b0b1 : ");lcdP1.print(ecat.nUsDistanceCmP2b0b1());lcdP1.print(" cm    ");
  lcdP1.setCursor(0, 1);
  lcdP1.print("P2b2b3 : ");lcdP1.print(ecat.nUsDistanceCmP2b2b3());lcdP1.print(" cm    ");
  delay(200);
}
