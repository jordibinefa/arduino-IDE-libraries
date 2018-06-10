/*
Connection schematic at 1st part of
http://www.binefa.cat/php/doc/lib-eCat03/
*/

#include <ecat.h>
#include <LiquidCrystal.h>

Ecat ecat;
lcdP2_init();

void setup(){
  lcdP2.begin(16, 2);
  ecat.vUltrasonicSensorP1b0b1_init();
  ecat.vUltrasonicSensorP1b2b3_init();
}

void loop(){
  lcdP2.setCursor(0, 0);
  lcdP2.print("P1b0b1 : ");lcdP2.print(ecat.nUsDistanceCmP1b0b1());lcdP2.print(" cm    ");
  lcdP2.setCursor(0, 1);
  lcdP2.print("P1b2b3 : ");lcdP2.print(ecat.nUsDistanceCmP1b2b3());lcdP2.print(" cm    ");
  delay(200);
}
