#include <RobotController.h>

void setup()
{
  Serial.begin(9600);
  RobotBegin();
}

void loop()
{
  Serial.print("Sensor 1: "); Serial.println(getFrontSideLeft());
  Serial.print("Sensor 2: "); Serial.println(getFrontLeft());
  Serial.print("Sensor 3: "); Serial.println(getFrontCenter());
  Serial.print("Sensor 4: "); Serial.println(getFrontRight());
  Serial.print("Sensor 5: "); Serial.println(getFrontSideRight());
  Serial.print("Sensor 6: "); Serial.println(getBackRight());
  Serial.print("Sensor 7: "); Serial.println(getBackLeft());
  Serial.println("----------------------------");
  delay(3000);	//Cada 3 segons
}
