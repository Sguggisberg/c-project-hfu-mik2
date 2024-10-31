#include <stdint.h>;
#include "libraries/Servo1/Servo1.h"

extern void zustandTürGeschlossen();
extern void zustandTürOffen();

extern uint8_t ReadKey();
extern void KeyGen();
extern void WriteLED();
extern void OutputTone();
extern bool CodeCheck();
extern bool CheckKey();
extern void SchlossAufTrue();

