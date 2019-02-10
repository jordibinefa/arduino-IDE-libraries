#include <RobotController.h>

void setup()
{
  RobotBegin();
  Serial.begin(9600);
}

void loop()
{
  Serial.print("Ultrasons: "); Serial.println(getDistance());
  if(getDistance()>50){
    Serial.println("STOP!");
  }else{
    Serial.println("RUN!");
  }
}