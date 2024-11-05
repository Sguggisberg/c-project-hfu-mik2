#ifndef __Servo1_h
#define __Servo1_h

#include "Arduino.h"


class Servo1
{
  public:
    Servo1(int pin);
    void begin();
    void SetPosition(uint16_t value);
  private:
    int _pin;
};

#endif __Servo1_h