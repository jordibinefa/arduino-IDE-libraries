/*
  RobotController.h
  Library for robot code.
  Released into the public domain.
*/
#ifndef robotcontroller_h
#define robotcontroller_h

#include <stdint.h>
#include "Arduino.h"
#include <Wire.h>
#include "PCF8574.h"

#define VERSION 0.04

#define M_RIGHT_FRONT_1 0x01
#define M_RIGHT_FRONT_2 0x02
#define M_LEFT_FRONT_1 0x04
#define M_LEFT_FRONT_2 0x08
#define M_LEFT_BACK_1 0x10
#define M_LEFT_BACK_2 0x20
#define M_RIGHT_BACK_1 0x40
#define M_RIGHT_BACK_2 0x80

#define FORWARD 0
#define BACKWARD 1

#define INFRA_1 0x01
#define INFRA_2 0x02
#define INFRA_3 0x04
#define INFRA_4 0x08
#define INFRA_5 0x10
#define INFRA_6 0x20
#define INFRA_7 0x40

//#define I2C_INFRA 0x73
//#define I2C_MOTORS 0x70
#define I2C_INFRA 0x39
#define I2C_MOTORS 0x38

#define BUTTON_START 	2

#define TRIGGER_PIN 7
#define ECHO_PIN 8

#define PWM_CONTROL_FRONT_LEFT 9	//490 Hz
#define PWM_CONTROL_BACK_LEFT 6		//980 Hz
#define PWM_CONTROL_FRONT_RIGHT 10	//490 Hz
#define PWM_CONTROL_BACK_RIGHT 3	//490 Hz

void RobotBegin();

//* CONTROL OF MOTORS 
void front(int value, int mode);			//Enable front motors
void right(int value, int mode);			//Enable right motors
void left(int value, int mode);				//Enable left motors
void back(int value, int mode);				//Enable back motors
void frontRight(int value, int mode);		//Enable the front engine on the right
void backRight(int value, int mode);		//Enable the back engine on the right
void frontLeft(int value, int mode);		//Enable the front engine on the left
void backLeft(int value, int mode);			//Enable the back engine on the left
void vMotion(int nLeft,int nRight); // -255 <= nLeft <= 255      -255 <= nRight <= 255

//* INFRARED SENSORS
int getFrontSideRight();	//Read the sensor located on the front right side
int getFrontSideLeft();		//Read the sensor located on the front left side
int getFrontRight();		//Read the sensor located on the front right
int getFrontLeft();			//Read the sensor located on the front left
int getFrontCenter();		//Read the sensor located on the front center
int getBackLeft();			//Read the sensor located on the back left
int getBackRight();			//Read the sensor located on the back right
byte byIR();				//Read all IR sensors at once
void vIR(bool *bBR,bool *bBL,bool *bFSL,bool *bFL,bool *bFC,bool *bFR,bool *bFSR);
void vShowIR(bool bBR,bool bBL,bool bFSL,bool bFL,bool bFC,bool bFR,bool bFSR);
void vShowRobot(bool bBR,bool bBL,bool bFSL,bool bFL,bool bFC,bool bFR,bool bFSR,int nUsDist);

//* ULTRASONIC SENSOR
int getDistance();	//
int nUltrasonicCm();

uint8_t statusMotor();
void stopMotors();

#endif
