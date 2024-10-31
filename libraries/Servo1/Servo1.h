#ifndef Servo1_h
#define Servo1_h

#include "Arduino.h"
#endif

class Servo1
{
  public:
    Servo1(int pin);
    void begin();
    void SetPosition(uint16_t value);
  private:
    int _pin;
};