#include <RobotController.h>

void setup()
{
  Serial.begin(9600);
  RobotBegin();
}

void loop()
{
  Serial.println("FRONT LEFT FORWARD");
  frontLeft(255,FORWARD);
  delay(3000);
  stopMotors();
  Serial.println("FRONT LEFT BACKWARD");
  frontLeft(255,BACKWARD);
  delay(3000);
  stopMotors();
  Serial.println("FRONT RIGHT FORWARD");
  frontRight(255,FORWARD);
  delay(3000);
  stopMotors();
  Serial.println("FRONT RIGHT BACKWARD");
  frontRight(255,BACKWARD);
  delay(3000);
  stopMotors();
  Serial.println("BACK RIGHT FORWARD");
  backRight(255,FORWARD);
  delay(3000);
  stopMotors();
  Serial.println("BACK RIGHT BACKWARD");
  backRight(255,BACKWARD);
  delay(3000);
  stopMotors();
  Serial.println("BACK LEFT FORWARD");
  backLeft(255,FORWARD);
  delay(3000);
  stopMotors();
  Serial.println("BACK LEFT BACKWARD");
  backLeft(255,BACKWARD);
  delay(3000);
  stopMotors();
}
