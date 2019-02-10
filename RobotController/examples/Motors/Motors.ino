#include <RobotController.h>

void setup()
{
  Serial.begin(9600);
  RobotBegin();
}

void loop()
{
  if( getFrontSideLeft() ) {
    frontLeft(255,FORWARD);
  }else if( getFrontSideRight() ){
    frontRight(255,FORWARD);
  }else if( getBackRight() ){
    backRight(255,FORWARD);
  }else if( getBackLeft() ){
    backLeft(255,FORWARD);
  }else if( getFrontLeft() ){
    left(255,FORWARD);
  }else if( getFrontRight() ){
    right(255,FORWARD);
  }else if( getFrontCenter() ){ 
    front(255, BACKWARD);
    back(255, BACKWARD);
  }else{
    stopMotors();
  }
}
