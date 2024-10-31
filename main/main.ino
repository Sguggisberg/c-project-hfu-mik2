#include <stdint.h>;
#include "Servo1.h";
#include <stdio.h>
#include <stdbool.h>
#include <functions.h>


//Variabeln Global
//Konstanten
const int Switch5 = 2;      //Variable Schalter Start
const int LED_Switch4 = 3;  //Variable Led zu
const int LED_Switch3 = 4;  //Variable Led zu
const int LED_Switch2 = 5;  //Variable Led zu
const int LED_Switch1 = 6;  //Variable Led zu
const int LED_Open = 7;     //Variable Led zu
const int LED_Closed = 8;   //Variable Led zu
const int Piezo = 10;       //Variable Led zu
//Variabeln
bool vClosed = false;       //"Save" Zustand Offen/Zu
bool vKeyStatus = false;    //Prüfung einzeleingabe
bool vCodeRichtig = false;  //Prüfung Cesamt Code
uint8_t vEingabe;           // User Eingabewert
uint8_t vKeyNr1 = 10;       // Code Wert1
uint8_t vKeyNr2 = 10;       // Code Wert2
uint8_t vKeyNr3 = 10;       // Code Wert3
uint8_t vKeyNr4 = 10;       // Code Wert4
Servo1 Schloss(9);          //Servo deklarieren mit Pin   //<-/////Marker/////////////////////////////////////////////////////

// Definition der Zustände
typedef enum {
  TÜR_GESCHLOSSEN,
  TÜR_OFFEN,
} TürZustand;

//---------
// Funktionsprototyp für Zustandsfunktionen
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

void init() {
  int aktuellerZustand = TÜR_GESCHLOSSEN;
  runStateMchine();
  initHardware();

  //Inizialisierung
  pinMode(Switch5, INPUT);
  pinMode(LED_Open, OUTPUT);
  pinMode(LED_Closed, OUTPUT);
  pinMode(Piezo, OUTPUT);
  //Normalisierung
  pinMode(LED_Switch1, INPUT);
  pinMode(LED_Switch2, INPUT);
  pinMode(LED_Switch3, INPUT);
  pinMode(LED_Switch4, INPUT);
  //Serielle verbindung zum Debugen
  Serial.begin(9600);
  //Inizialisierung Motor
  Schloss.begin();  //<-/////Marker///////////////////////////////////////////////////////////////
  //Meldung Bereit
  OutputTone(0);  //Tone Bereit "0"
}

void codeCheck() {
}

// Anzahl der Zustände aus dem Array bestimmen
#define ANZAHL_ZUSTÄNDE (sizeof(zustände) / sizeof(Zustand))
int main() {
  init();
  bool initFinishd = false;

  while (true) {
    switch (aktuellerZustand) {
      case TÜR_OFFEN:
        vEingabe = ReadKey();
        switch (vEingabe) {
          case 4:
            KeyGen();  //Code generieren
            //Ausgabe des Codes
            delay(500);  //Verhindert soundüberschneidung
            WriteLED(vKeyNr1);
            WriteLED(vKeyNr2);
            WriteLED(vKeyNr3);
            WriteLED(vKeyNr4);
            //Code eingabe und Prüfung
            vCodeRichtig = codeCheck();  //Prüfung Code
            if (vCodeRichtig == true) {
              OutputTone(6);
              runStateMchine();
            } else {          //Bei Falsch
              OutputTone(7);  //Sound für Falsch
            }
            break;

          case TÜR_GESCHLOSSEN:
            vEingabe = ReadKey();
            switch (vEingabe) {
              case 4:
                delay(250);
                //Code eingabe und Prüfung
                vCodeRichtig = CodeCheck();  //Prüfung Code
                if (vCodeRichtig == true) {  //Bei Richtig
                  OutputTone(6);
                  runStateMchine();
                } else {          //Bei Falsch
                  OutputTone(7);  //Sound für Falsch
                }
                break;
            }
        }
    }
  }
  return 0;
}

void runStateMchine() {
  for (int i = 0; i < ANZAHL_ZUSTÄNDE; i++) {
    if (zustände[i].from == aktuellerZustand) {
      printf("aktueller state: %d, neuer State: %d\n", aktuellerZustand, zustände[i].to);
      zustände[i].transition();

      aktuellerZustand = zustände[i].to;
    }
  }
}
