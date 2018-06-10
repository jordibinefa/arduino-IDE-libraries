#include <ecat.h>
#include <LiquidCrystal.h>

Ecat ecat;
lcdP1_init();


void setup(){
  ecat.setupNibbleMode(NIBBLE_H_P2,OUTPUT);
  ecat.vUltrasonicSensorP2b0b1_init();
  lcdP1.begin(16, 2);
}

void vRobotAturat(){
  ecat.vWriteHighNibbleP2(0x00);
}

void vRobotEndavant(){
  ecat.vWriteHighNibbleP2(B00001001);
}

void vRobotEndarrera(){
  ecat.vWriteHighNibbleP2(B00000110);
}


void loop(){
  long int nDist;
  
  nDist = ecat.nUsDistanceCmP2b0b1();
  lcdP1.setCursor(0, 1);lcdP1.print("Dist : ");lcdP1.print(nDist);lcdP1.print(" cm      ");
  if(!(nDist < 2+5 && nDist >=0)){
    vRobotEndavant();   
    lcdP1.setCursor(0, 0);lcdP1.print("Endavant   ");
  }else{
    vRobotEndarrera();
    lcdP1.setCursor(0, 0);lcdP1.print("Endarrera  ");
    delay(300);
    vRobotAturat();
    lcdP1.setCursor(0, 0);lcdP1.print("Aturat     ");
  }
  delay(200);
}
