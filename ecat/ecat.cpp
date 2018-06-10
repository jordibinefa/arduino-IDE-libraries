#include "Arduino.h"
#include "ecat.h"

Ecat::Ecat(){
	_vPinAssignment();
}

void Ecat::setupNibbleMode(BYTE nibble,BYTE nibbleMode){
	switch(nibble){
		case NIBBLE_H_P1: setupHighNibbleP1(nibbleMode);
			break;
		case NIBBLE_L_P1: setupLowNibbleP1(nibbleMode);
			break;
		case NIBBLE_H_P2: setupHighNibbleP2(nibbleMode);
			break;
		case NIBBLE_L_P2: setupLowNibbleP2(nibbleMode);
			break;
	}
}

void Ecat::_vPinAssignment(){
	nPinP1B7=7;nPinP1B6=6;nPinP1B5=5;nPinP1B4=4;
	nPinP1B3=A3;nPinP1B2=A2;nPinP1B1=A1;nPinP1B0=A0;
	nPinP2B7=13;nPinP2B6=12;nPinP2B5=11;nPinP2B4=10;
	nPinP2B3=9;nPinP2B2=8;nPinP2B1=A4;nPinP2B0=A5;
}

void Ecat::setupHighNibbleP1(BYTE mode){
  modeHighNibbleP1 = mode;
  pinMode(nPinP1B4, mode);
  pinMode(nPinP1B5, mode);
  pinMode(nPinP1B6, mode);
  pinMode(nPinP1B7, mode);
}

void Ecat::setupLowNibbleP1(BYTE mode){
  modeLowNibbleP1 = mode;
  pinMode(nPinP1B0, mode);
  pinMode(nPinP1B1, mode);
  pinMode(nPinP1B2, mode);
  pinMode(nPinP1B3, mode);
}

void Ecat::setupHighNibbleP2(BYTE mode){
  modeHighNibbleP2 = mode;
  pinMode(nPinP2B4, mode);
  pinMode(nPinP2B5, mode);
  pinMode(nPinP2B6, mode);
  pinMode(nPinP2B7, mode); // By default P2B7 can't be input. (It should be removed Led or resistor on Arduino board)
}

void Ecat::setupLowNibbleP2(BYTE mode){
  modeLowNibbleP2 = mode;
  pinMode(nPinP2B0, mode);
  pinMode(nPinP2B1, mode);
  pinMode(nPinP2B2, mode);
  pinMode(nPinP2B3, mode);
}

void Ecat::vWriteLowNibbleP1(BYTE b){
  digitalWrite(nPinP1B0, b & 0x1);
  digitalWrite(nPinP1B1, b & 0x2);
  digitalWrite(nPinP1B2, b & 0x4);
  digitalWrite(nPinP1B3, b & 0x8);
}

void Ecat::vWriteHighNibbleP1Raw(BYTE b){
  digitalWrite(nPinP1B4, b & 0x10);
  digitalWrite(nPinP1B5, b & 0x20);
  digitalWrite(nPinP1B6, b & 0x40);
  digitalWrite(nPinP1B7, b & 0x80);
}

BYTE Ecat::byReadNibble(BYTE byNibble){
	switch(byNibble){
		case NIBBLE_L_P1 :
			return byReadLowNibbleP1();
			break;
		case NIBBLE_H_P1 :
			return byReadHighNibbleP1();
			break;
		case NIBBLE_L_P2 :
			return byReadLowNibbleP2();
			break;
		case NIBBLE_H_P2 :
			return byReadHighNibbleP2();
			break;
		default : return 0xFF; // It shouldn't arrive here
	}
}

BYTE Ecat::byReadLowNibbleP1(){
	BYTE byNibble = 0x00;
	
	if(digitalRead(nPinP1B0))
		byNibble |= 0x01;
	if(digitalRead(nPinP1B1))
		byNibble |= 0x02;
	if(digitalRead(nPinP1B2))
		byNibble |= 0x04;
	if(digitalRead(nPinP1B3))
		byNibble |= 0x08;
		
	return byNibble;
}

BYTE Ecat::byReadHighNibbleP1(){
	return byReadHighNibbleP1Raw() >> 4;
}

BYTE Ecat::byReadHighNibbleP1Raw(){
	BYTE byNibble = 0x00;
	
	if(digitalRead(nPinP1B4))
		byNibble |= 0x10;
	if(digitalRead(nPinP1B5))
		byNibble |= 0x20;
	if(digitalRead(nPinP1B6))
		byNibble |= 0x40;
	if(digitalRead(nPinP1B7))
		byNibble |= 0x80;
		
	return byNibble;
}

BYTE Ecat::byReadP1(){
	return byReadLowNibbleP1() | byReadHighNibbleP1Raw();
}

BYTE Ecat::byReadLowNibbleP2(){
	BYTE byNibble = 0x00;
	
	if(digitalRead(nPinP2B0))
		byNibble |= 0x01;
	if(digitalRead(nPinP2B1))
		byNibble |= 0x02;
	if(digitalRead(nPinP2B2))
		byNibble |= 0x04;
	if(digitalRead(nPinP2B3))
		byNibble |= 0x08;
		
	return byNibble;
}

BYTE Ecat::byReadHighNibbleP2(){
	// Be aware, P2B7 is write only. To read it should removed Led or resistor on Arduino board
	return byReadHighNibbleP2Raw() >> 4;
}

BYTE Ecat::byReadHighNibbleP2Raw(){
	// Be aware, P2B7 is write only. To read it should removed Led or resistor on Arduino board
	BYTE byNibble = 0x00;
	
	if(digitalRead(nPinP2B4))
		byNibble |= 0x10;
	if(digitalRead(nPinP2B5))
		byNibble |= 0x20;
	if(digitalRead(nPinP2B6))
		byNibble |= 0x40;
	if(digitalRead(nPinP2B7))
		byNibble |= 0x80;
		
	return byNibble;
}

BYTE Ecat::byReadP2(){
	// Be aware, P2B7 is write only. To read it should removed Led or resistor on Arduino board
	return byReadLowNibbleP2() | byReadHighNibbleP2Raw();
}

void Ecat::vWriteHighNibbleP1(BYTE b){
  b <<= 4;
  vWriteHighNibbleP1Raw(b);
}

void Ecat::vWriteP1(BYTE b){
  vWriteLowNibbleP1(b);
  vWriteHighNibbleP1Raw(b);
}

void Ecat::vWriteLowNibbleP2(BYTE b){
  digitalWrite(nPinP2B0, b & 0x1);
  digitalWrite(nPinP2B1, b & 0x2);
  digitalWrite(nPinP2B2, b & 0x4);
  digitalWrite(nPinP2B3, b & 0x8);
}

void Ecat::vWriteHighNibbleP2Raw(BYTE b){
  digitalWrite(nPinP2B4, b & 0x10);
  digitalWrite(nPinP2B5, b & 0x20);
  digitalWrite(nPinP2B6, b & 0x40);
  digitalWrite(nPinP2B7, b & 0x80);
}

void Ecat::vWriteHighNibbleP2(BYTE b){
  b <<= 4;
  vWriteHighNibbleP2Raw(b);
}

void Ecat::vWriteP2(BYTE b){
  vWriteLowNibbleP2(b);
  vWriteHighNibbleP2Raw(b);
}

void Ecat::vUltrasonicSensorP1b0b1_init(){
	digitalWrite( nPinP1B0 , LOW );
}

void Ecat::vUltrasonicSensorP1b2b3_init(){
	digitalWrite( nPinP1B3 , LOW );
}

void Ecat::vUltrasonicSensorP2b0b1_init(){
	digitalWrite( nPinP2B0 , LOW );
}

void Ecat::vUltrasonicSensorP2b2b3_init(){
	digitalWrite( nPinP2B3 , LOW );
}

int Ecat::nUltrasonicSensorDistanceCm(int trigPin, int echoPin){
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

int Ecat::nUsDistanceCmP1b0b1(){
	return nUltrasonicSensorDistanceCm(nPinP1B0,nPinP1B1);
}

int Ecat::nUsDistanceCmP1b2b3(){
	return nUltrasonicSensorDistanceCm(nPinP1B3,nPinP1B2);
}

int Ecat::nUsDistanceCmP2b0b1(){
	return nUltrasonicSensorDistanceCm(nPinP2B0,nPinP2B1);
}

int Ecat::nUsDistanceCmP2b2b3(){
	return nUltrasonicSensorDistanceCm(nPinP2B3,nPinP2B2);
}

float Ecat::fVersion(){
	return ECAT_VERSION;
}
