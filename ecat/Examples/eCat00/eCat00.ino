/*
Connection schematic at http://www.binefa.cat/php/doc/lib-eCat01/
*/

#include <ecat.h>

Ecat ecat;

void setup(){
  ecat.setupNibbleMode(NIBBLE_H_P1,OUTPUT);
  ecat.setupNibbleMode(NIBBLE_L_P1,OUTPUT);
  ecat.setupNibbleMode(NIBBLE_H_P2,OUTPUT);
  ecat.setupNibbleMode(NIBBLE_L_P2,OUTPUT);
}

void loop(){
  byte by = 0x01;
  int i;
  
  for(i = 0 ; i < 4 ; i++){
    ecat.vWriteLowNibbleP1(by);
    by <<= 1;
    delay(200);
  }
  ecat.vWriteLowNibbleP1(0x00);
  for(i = 4 ; i < 8 ; i++ , by <<= 1){
    ecat.vWriteHighNibbleP1Raw(by);
    delay(200);
  }
  ecat.vWriteHighNibbleP1(0x00);
  for(by = 0x01 ; by >0 && by <= 0x80 ; by <<= 1, delay(200))
    ecat.vWriteP2(by);
  ecat.vWriteP2(0x00);
}
