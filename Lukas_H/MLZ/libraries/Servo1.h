#ifndef Servo1_h
#define Servo1_h
#endif

#include "Arduino.h"
class Servo1
{
	private:
		int _pin;
	
	public:
		Servo1();
		void begin();
		void SetPosition(uint16_t value);
};
