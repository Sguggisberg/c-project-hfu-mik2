#ifndef __Variabeln_h
#define __Variabeln_h

#include "Arduino.h"

//Variabeln Global
//Konstanten
const int Switch5 = 2;     //Variable Schalter Start
const int LED_Switch4 = 3;     //Variable Led zu
const int LED_Switch3 = 4;     //Variable Led zu
const int LED_Switch2 = 5;     //Variable Led zu
const int LED_Switch1 = 6;     //Variable Led zu
const int LED_Open = 7;     //Variable Led zu
const int LED_Closed = 8;     //Variable Led zu
const int Piezo = 10;     //Variable Led zu
//Variabeln
bool vClosed = false;    //"Save" Zustand Offen/Zu
bool vKeyStatus = false;    //Prüfung einzeleingabe
bool vCodeRichtig = false;    //Prüfung Cesamt Code
uint8_t vEingabe;              // User Eingabewert
uint8_t vKeyNr1 = 10;       // Code Wert1
uint8_t vKeyNr2 = 10;       // Code Wert2
uint8_t vKeyNr3 = 10;       // Code Wert3
uint8_t vKeyNr4 = 10;       // Code Wert4
Servo1 Schloss(9);     //Servo deklarieren mit Pin   //<-/////Marker/////////////////////////////////////////////////////

// Definition der Zustände
typedef enum {
	TÜR_GESCHLOSSEN,
	TÜR_OFFEN,
} TürZustand;

typedef void (*ZustandsFunktion)(void);
typedef bool (*guard)(void);
// Definition der Zustandsstruktur
typedef struct {
	TürZustand from;
	ZustandsFunktion transition;  // Zeiger auf die Zustandsfunktion
	TürZustand to;
} Zustand;

// Zustände als `struct`-Instanzen in einem Array definieren
Zustand zustände[] = {
  { TÜR_GESCHLOSSEN, zustandTürÖffnet, TÜR_OFFEN },
  { TÜR_OFFEN, zustandTürSchließt, TÜR_GESCHLOSSEN },
};




#endif
