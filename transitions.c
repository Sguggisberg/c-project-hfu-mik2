#include <stdio.h>
#include <stdbool.h>
#include "functions.h"

void zustandTürÖffnet() {
  if (türOffenSensor()) {
    motorAus();
  }
}

void zustandTürSchließt() {
  if (türGeschlossenSensor()) {
    motorAus();
  }
}