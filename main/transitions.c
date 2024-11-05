#include <stdio.h>
#include <stdbool.h>
#include "functions.h"

void zustandTuerOeffnet() {
  if (tuerOffenSensor()) {
    motorAus();
  }
}

void zustandTuerSchliesst() {
  if (tuerGeschlossenSensor()) {
    motorAus();
  }
}