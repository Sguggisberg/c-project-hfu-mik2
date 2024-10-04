#include <stdio.h>
#include <stdbool.h>
#include "functions.h"

// Funktion zur Steuerung des Motors
static void motorAn(bool öffnen) {
    if (öffnen) {
        printf("Motor: Tür öffnet\n");
    } else {
        printf("Motor: Tür schließt\n");
    }
}

void motorAus() {
    printf("Motor: Stopp\n");
}
// Simulierte Funktionen für Taster und Sensoren
bool tasterGedrückt() {
    return true; // Beispielwert
}

bool türGeschlossenSensor() {
    return true; // Beispielwert
}

bool türOffenSensor() {
    return true; // Beispielwert
}
// Zustandsfunktionen
void zustandTürGeschlossen() {
    if (tasterGedrückt()) {
        motorAn(true);  // Tür öffnet
    }
}

void zustandTürÖffnet() {
    if (türOffenSensor()) {
        motorAus();
    }
}

void zustandTürOffen() {
    if (tasterGedrückt()) {
        motorAn(false);  // Tür schließt
    }
}

void zustandTürSchließt() {
    if (türGeschlossenSensor()) {
        motorAus();
    }
}

