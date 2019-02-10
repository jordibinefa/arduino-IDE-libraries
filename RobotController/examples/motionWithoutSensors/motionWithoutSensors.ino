#include <RobotController.h>

#define STATE_STOP  0
#define STATE_FAST_FORWARD 1
#define STATE_FORWARD 2
#define STATE_FAST_BACKWARDS 3
#define STATE_BAKWARDS  4
#define STATE_RIGHT 5
#define STATE_LEFT 6

#define N_STEPS 10

#define VERBOSE

void vRunState(byte byCS) {
  switch (byCS) {
    case STATE_STOP: vMotion(0, 0);
#ifdef VERBOSE
      Serial.println("STATE_STOP");
#endif
      break;
    case STATE_FAST_FORWARD: vMotion(255, 255);
#ifdef VERBOSE
      Serial.println("STATE_FAST_FORWARD");
#endif
      break;
    case STATE_FORWARD: vMotion(127, 127);
#ifdef VERBOSE
      Serial.println("STATE_FORWARD");
#endif
      break;
    case STATE_FAST_BACKWARDS: vMotion(-255, -255);
#ifdef VERBOSE
      Serial.println("STATE_FAST_BACKWARDS");
#endif
      break;
    case STATE_BAKWARDS: vMotion(-127, -127);
#ifdef VERBOSE
      Serial.println("STATE_BAKWARDS");
#endif
      break;
    case STATE_RIGHT: vMotion(127, -127);
#ifdef VERBOSE
      Serial.println("STATE_RIGHT");
#endif
      break;
    case STATE_LEFT: vMotion(-127, 127);
#ifdef VERBOSE
      Serial.println("STATE_LEFT");
#endif
      break;
  }
}

void setup() {
  Serial.begin(115200);
  RobotBegin();
}

void loop() {
  byte byStates[N_STEPS] = {STATE_STOP, STATE_FORWARD, STATE_FAST_FORWARD, STATE_STOP, STATE_BAKWARDS, STATE_FAST_BACKWARDS, STATE_STOP, STATE_RIGHT, STATE_STOP, STATE_LEFT};
  static unsigned long int ulLastMillis = millis();
  unsigned long int ulNow = millis();
  unsigned long int ulDif = ulNow - ulLastMillis;
  static byte byCurrentStep = 0;
  byte byCurrentState = byStates[byCurrentStep];

  if (ulDif >= 500) {
    ulLastMillis = ulNow;
    byCurrentStep++;
    if (byCurrentStep >= N_STEPS)
      byCurrentStep = 0;
    byCurrentState = byStates[byCurrentStep];
    vRunState(byCurrentState);
  }
}
