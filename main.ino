#include <stdio.h>
#include <stdbool.h>
#include <functions.h>


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
