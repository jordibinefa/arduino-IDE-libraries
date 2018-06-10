#include <ecat.h>

Ecat ecat;

void setup(){
  ecat.setupNibbleMode(NIBBLE_H_P1,OUTPUT);
  ecat.setupNibbleMode(NIBBLE_L_P1,OUTPUT);
  ecat.setupNibbleMode(NIBBLE_H_P2,INPUT);
  ecat.setupNibbleMode(NIBBLE_L_P2,INPUT);
}

void loop(){
  ecat.vWriteP1(0x7F & ecat.byReadP2());
}
