#include <ecat.h>
#include <LiquidCrystal.h>

Ecat ecat;
lcdP2_init();

void setup(){
  ecat.setupNibbleMode(NIBBLE_H_P1,OUTPUT);
  ecat.setupNibbleMode(NIBBLE_L_P1,OUTPUT);
  lcdP2.begin(16, 2);
  lcdP2.print("electronics.cat");
}

void loop(){
  static byte by = 0x01;
  
  lcdP2.setCursor(0, 1);
  lcdP2.print("PORT2 ");lcdP2.print(millis()/1000);lcdP2.print(" seconds");
  ecat.vWriteP1(by);
  by <<= 1;
  if(!by || by >0x80)
    by = 0x01;
  delay(200);
}
