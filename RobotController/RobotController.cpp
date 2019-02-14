/*
  RobotController.cpp - Library for robot code.
  Created by EDCO, January 31, 2019.
  Released into the public domain.
*/

#include "RobotController.h"


//See http://www.ti.com/lit/ds/symlink/pcf8574a.pdf
PCF8574 IRSensors(I2C_INFRA);  // add switches to lines  	(used as input)
PCF8574 MotorController(I2C_MOTORS);  // add LEDs to lines  (used as output)
uint8_t _motorStatus = 0;

void RobotBegin(){
	pinMode(BUTTON_START, INPUT_PULLUP);   	
	pinMode(PWM_CONTROL_FRONT_LEFT, OUTPUT);   	// Sets the (analog) pin as output
	pinMode(PWM_CONTROL_BACK_LEFT, OUTPUT);   	// Sets the (analog) pin as output
	pinMode(PWM_CONTROL_FRONT_RIGHT, OUTPUT);   // Sets the (analog) pin as output
	pinMode(PWM_CONTROL_BACK_RIGHT, OUTPUT);   	// Sets the (analog) pin as output
	MotorController.begin(0);										// Set the initial status of the motors (off)
	_motorStatus = 0;
	MotorController.write8(_motorStatus);				// TO DO: Set the initial status of the motors (off)
}

uint8_t statusMotor(){
	return _motorStatus;
}

void frontRight(int value, int mode){
  switch(mode){
    case FORWARD:
			analogWrite(PWM_CONTROL_FRONT_RIGHT, value);
			_motorStatus = (_motorStatus & (0b00111111) ) | 0x40;
			MotorController.write8(_motorStatus);
      break;
    case BACKWARD:
			analogWrite(PWM_CONTROL_FRONT_RIGHT, value);
			_motorStatus = (_motorStatus & (0b00111111) ) | 0x80;
			MotorController.write8(_motorStatus);
      break;
  }
}

void frontLeft(int value, int mode){
  switch(mode){
    case FORWARD:
			analogWrite(PWM_CONTROL_FRONT_LEFT, value);
			_motorStatus = (_motorStatus & (0b11001111) ) | 0x10;
			MotorController.write8(_motorStatus);
      break;
    case BACKWARD:
			analogWrite(PWM_CONTROL_FRONT_LEFT, value);
			_motorStatus = (_motorStatus & (0b11001111) ) | 0x20;
			MotorController.write8(_motorStatus);
      break;
  }
}

void backRight(int value, int mode){
  switch(mode){
    case FORWARD:
			analogWrite(PWM_CONTROL_BACK_RIGHT, value);
			_motorStatus = (_motorStatus & (0b11111100) ) | 0x01;
			MotorController.write8(_motorStatus);
      break;
    case BACKWARD:
			analogWrite(PWM_CONTROL_BACK_RIGHT, value);
			_motorStatus = (_motorStatus & (0b11111100) ) | 0x02;
			MotorController.write8(_motorStatus);
      break;
  }
}

void backLeft(int value, int mode){
  switch(mode){
    case FORWARD:
			analogWrite(PWM_CONTROL_BACK_LEFT, value);
			_motorStatus = (_motorStatus & (0b11110011) ) | 0x08;
			MotorController.write8(_motorStatus);
      break;
    case BACKWARD:
			analogWrite(PWM_CONTROL_BACK_LEFT, value);
			_motorStatus = (_motorStatus & (0b11110011) ) | 0x04;
			MotorController.write8(_motorStatus);
      break;
  }
}

void vMotion(int nLeft,int nRight){ // -255 <= nLeft <= 255      -255 <= nRight <= 255
	if(nRight >= 0){
		analogWrite(PWM_CONTROL_FRONT_RIGHT, nRight);
		_motorStatus = (_motorStatus & (0b00111111) ) | ((nRight != 0) ? 0x40 : 0x00);
		analogWrite(PWM_CONTROL_BACK_RIGHT, nRight);
		_motorStatus = (_motorStatus & (0b11111100) ) | ((nRight != 0) ? 0x01 : 0x00);
	}else{
		analogWrite(PWM_CONTROL_FRONT_RIGHT, -nRight);
		_motorStatus = (_motorStatus & (0b00111111) ) | 0x80;
		analogWrite(PWM_CONTROL_BACK_RIGHT, -nRight);
		_motorStatus = (_motorStatus & (0b11111100) ) | 0x02;
	}
	if(nLeft >= 0){
		analogWrite(PWM_CONTROL_FRONT_LEFT, nLeft);
		_motorStatus = (_motorStatus & (0b11001111) ) | ((nLeft != 0) ? 0x10 : 0x00);
		analogWrite(PWM_CONTROL_BACK_LEFT, nLeft);
		_motorStatus = (_motorStatus & (0b11110011) ) | ((nLeft != 0) ? 0x08 : 0x00);
	}else{
		analogWrite(PWM_CONTROL_FRONT_LEFT, -nLeft);
		_motorStatus = (_motorStatus & (0b11001111) ) | 0x20;
		analogWrite(PWM_CONTROL_BACK_LEFT, -nLeft);
		_motorStatus = (_motorStatus & (0b11110011) ) | 0x04;
	}
	MotorController.write8(_motorStatus);
}

void front(int value, int mode){
  frontRight(value, mode);
  frontLeft(value, mode);
}

void back(int value, int mode){
  backRight(value, mode);
  backLeft(value, mode);
}

void right(int value, int mode){
  frontRight(value, mode);
  backRight(value, mode);
}

void left(int value, int mode){
  frontLeft(value, mode);
  backLeft(value, mode);
}


//* CONTROL DELS SENSORS 
int getFrontSideRight(){//Lateral dret davanter
  return (IRSensors.read8() >> 6) & 0x01;
}

int getFrontSideLeft(){//Lateral esquerra davanter
  return (IRSensors.read8() >> 2) & 0x01;
}

int getFrontRight(){
  return (IRSensors.read8() >> 5) & 0x01;
}

int getFrontLeft(){
  return (IRSensors.read8() >> 3) & 0x01;
}

int getFrontCenter(){
  return (IRSensors.read8() >> 4) & 0x01;
}

int getBackLeft(){
  return (IRSensors.read8() >> 1) & 0x01;
}

int getBackRight(){
  return (IRSensors.read8()) & 0x01;
}

byte byIR(){
	return IRSensors.read8();
}

void vIR(bool *bBR,bool *bBL,bool *bFSL,bool *bFL,bool *bFC,bool *bFR,bool *bFSR){
	byte byIr = byIR();
	
	*bBR = byIr & 0x01;
	*bBL = (byIr >> 1) & 0x01;
	*bFSL = (byIr >> 2) & 0x01;
	*bFL = (byIr >> 3) & 0x01;
	*bFC = (byIr >> 4) & 0x01;
	*bFR = (byIr >> 5) & 0x01;
	*bFSR = (byIr >> 6) & 0x01;
}

void gotoxy(int x,int y){
	char sz[12];
	
    sprintf(sz,"%c[%d;%df",0x1B,y,x);Serial.println(sz);
}

void vShowIR(bool bBR,bool bBL,bool bFSL,bool bFL,bool bFC,bool bFR,bool bFSR){
  char sz[12];int i;

  //for(i = 0; i < 5; i++)
  //  Serial.println();
  gotoxy(1,2);
  Serial.println(" /----/^\\----\\");
  sprintf(sz,    " |%c  %c %c %c  %c|",bFSL?'W':'B',bFL?'W':'B',bFC?'W':'B',bFR?'W':'B',bFSR?'W':'B');Serial.println(sz);
  Serial.println("[ ]    ^    [ ]");
  sprintf(sz,    "[ ]    %c    [ ]",digitalRead(BUTTON_START) ? 'N':'P');Serial.println(sz);
  Serial.println(" |     ^     |");
  Serial.println("[ ]    ^    [ ]");
  Serial.println("[ ]    ^    [ ]");
  sprintf(sz," |%c    ^    %c|",bBL?'W':'B',bBR?'W':'B');Serial.println(sz);
  Serial.println(" +-----------+");
  for(i = 0; i < 5; i++)
    Serial.println();
}

void vShowRobot(bool bBR,bool bBL,bool bFSL,bool bFL,bool bFC,bool bFR,bool bFSR,int nUsDist){
  char sz[12];int i;
  char cFR = (_motorStatus & 0x40) ? '^' : (_motorStatus & 0x80) ? 'v' : ' ';
  char cFL = (_motorStatus & 0x10) ? '^' : (_motorStatus & 0x20) ? 'v' : ' ';
  char cBR = (_motorStatus & 0x01) ? '^' : (_motorStatus & 0x02) ? 'v' : ' ';
  char cBL = (_motorStatus & 0x08) ? '^' : (_motorStatus & 0x04) ? 'v' : ' ';
  
  //for(i = 0; i < 5; i++)
  //  Serial.println();
  gotoxy(1,2);
  Serial.print("    { "); Serial.print(nUsDist,DEC);Serial.println(" cm }");
  Serial.println(" /----/^\\----\\");
  sprintf(sz,    " |%c  %c %c %c  %c|",bFSL?'W':'B',bFL?'W':'B',bFC?'W':'B',bFR?'W':'B',bFSR?'W':'B');Serial.println(sz);
  Serial.println("[ ]         [ ]");
  sprintf(sz,    "[%c]    %c    [%c]",cFL,digitalRead(BUTTON_START) ? 'N':'P',cFR);Serial.println(sz);
  sprintf(sz,    "[ ]  +---+  [ ]");Serial.println(sz);
  Serial.println(" |   | | |   |");
  Serial.println("[ ]  | | |  [ ]");
  sprintf(sz,    "[%c]  +-|-+  [%c]",cBL,cBR);Serial.println(sz);
  Serial.println("[ ]    -    [ ]");
  sprintf(sz," |%c    -    %c|",bBL?'W':'B',bBR?'W':'B');Serial.println(sz);
  Serial.println(" +-----------+");
  for(i = 0; i < 5; i++)
    Serial.println();
}

void stopMotors(){
  front(0, FORWARD);
  back(0, FORWARD);
}

int nUltrasonicSensorDistanceCm(int trigPin, int echoPin){
  long int duration;
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  duration = duration / 59;
  return (int)duration;
}

int getDistance(){
	return nUltrasonicSensorDistanceCm(TRIGGER_PIN,ECHO_PIN);
}

int nUltrasonicCm(){
	int nGd = getDistance();
	
	if(nGd < 2)
		return 2;
	if(nGd > 450)
		return 450;
		
	return nGd;
}
