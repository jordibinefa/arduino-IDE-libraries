#include <RobotController.h>

void setup() {
  Serial.begin(115200);
  RobotBegin();
}

void loop() {
  bool bBR, bBL, bFSL, bFL, bFC, bFR, bFSR;
  static unsigned long int ulLastMillis = millis();
  unsigned long int ulNow = millis();
  unsigned long int ulDif = ulNow - ulLastMillis;
  int nUsDist = nUltrasonicCm();

  vIR(&bBR, &bBL, &bFSL, &bFL, &bFC, &bFR, &bFSR);

  if (ulDif >= 300) {
    ulLastMillis = ulNow;
    char c = digitalRead(BUTTON_START) ? 'N':'P';
    Serial.print("   { "); Serial.print(nUsDist,DEC);Serial.println(" cm }");
    vShowIR(bBR, bBL, bFSL, bFL, bFC, bFR, bFSR);
  }
}
