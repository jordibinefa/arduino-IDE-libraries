#include <RobotController.h>

void setup() {
  Serial.begin(115200);
  RobotBegin();
}

void loop() {
  bool bBR, bBL, bFSL, bFL, bFC, bFR, bFSR;

  vIR(&bBR, &bBL, &bFSL, &bFL, &bFC, &bFR, &bFSR);
  vShowIR(bBR, bBL, bFSL, bFL, bFC, bFR, bFSR);
  
  delay(300);
}
