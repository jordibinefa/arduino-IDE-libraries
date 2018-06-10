#ifndef ecat_h
#define ecat_h

#define ECAT_VERSION 0.25f

#define NIBBLE_H_P1	11
#define NIBBLE_L_P1	10
#define NIBBLE_H_P2	21
#define NIBBLE_L_P2	20

#define lcdP1_init(); LiquidCrystal lcdP1(16, 17, 4,5, 6, 7);
#define lcdP2_init(); LiquidCrystal lcdP2(8,9,10,11,12,13);

#ifndef BYTE
	#define BYTE unsigned char
#endif

class Ecat{
  public:
    Ecat();
    
	BYTE nPinP1B7,nPinP1B6,nPinP1B5,nPinP1B4;
	BYTE nPinP1B3,nPinP1B2,nPinP1B1,nPinP1B0;
	BYTE nPinP2B7,nPinP2B6,nPinP2B5,nPinP2B4;
	BYTE nPinP2B3,nPinP2B2,nPinP2B1,nPinP2B0;
	BYTE modeHighNibbleP1,modeLowNibbleP1;
	BYTE modeHighNibbleP2,modeLowNibbleP2;

	void setupNibbleMode(BYTE nibble,BYTE mode);

	void setupHighNibbleP1(BYTE mode);
	void setupLowNibbleP1(BYTE mode);
	void setupHighNibbleP2(BYTE mode);
	void setupLowNibbleP2(BYTE mode);

	void vWriteLowNibbleP1(BYTE b);
	void vWriteHighNibbleP1Raw(BYTE b);
	void vWriteHighNibbleP1(BYTE b);
	void vWriteP1(BYTE b);

	BYTE byReadNibble(BYTE byNibble);
	BYTE byReadLowNibbleP1();
	BYTE byReadHighNibbleP1();
	BYTE byReadHighNibbleP1Raw();
	BYTE byReadP1();
	BYTE byReadLowNibbleP2();
	BYTE byReadHighNibbleP2();
	BYTE byReadHighNibbleP2Raw();
	BYTE byReadP2();

	void vWriteLowNibbleP2(BYTE b);
	void vWriteHighNibbleP2Raw(BYTE b);
	void vWriteHighNibbleP2(BYTE b);
	void vWriteP2(BYTE b);
	
	void vUltrasonicSensorP1b0b1_init();
	void vUltrasonicSensorP1b2b3_init();
	void vUltrasonicSensorP2b0b1_init();
	void vUltrasonicSensorP2b2b3_init();
	int nUltrasonicSensorDistanceCm(int trigPin, int echoPin);
	int nUsDistanceCmP1b0b1();
	int nUsDistanceCmP1b2b3();
	int nUsDistanceCmP2b0b1();
	int nUsDistanceCmP2b2b3();
	
	float fVersion();
	
  private:
    void _vPinAssignment();
};

#endif
