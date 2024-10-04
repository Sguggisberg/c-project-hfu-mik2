#include <stdio.h>
#include <stdbool.h>
#include "functions.h"

// Definition der Zustände
typedef enum {
    TÜR_GESCHLOSSEN,
    TÜR_ÖFFNET,
    TÜR_OFFEN,
    TÜR_SCHLIESST,
} TürZustand;

//---------
// Funktionsprototyp für Zustandsfunktionen
typedef void (*ZustandsFunktion)(void);
typedef bool (*guard)(void);
// Definition der Zustandsstruktur
typedef struct {
    TürZustand from;
    ZustandsFunktion transition;   // Zeiger auf die Zustandsfunktion
    TürZustand to;
} Zustand;


// Zustände als `struct`-Instanzen in einem Array definieren
Zustand zustände[] = {
    {TÜR_GESCHLOSSEN, zustandTürGeschlossen, TÜR_ÖFFNET},
    {TÜR_ÖFFNET,zustandTürÖffnet, TÜR_OFFEN},
    {TÜR_OFFEN, zustandTürOffen, TÜR_SCHLIESST },
    {TÜR_SCHLIESST, zustandTürSchließt, TÜR_GESCHLOSSEN}
};

// Anzahl der Zustände aus dem Array bestimmen
#define ANZAHL_ZUSTÄNDE (sizeof(zustände) / sizeof(Zustand))

int main() {
    // Globale Variable für den aktuellen Zustand
    int aktuellerZustand = TÜR_GESCHLOSSEN; // Start State
    
    for(int i=0; i<ANZAHL_ZUSTÄNDE; i++){
        if(zustände[i].from == aktuellerZustand){
            printf("aktueller state: %d, neuer State: %d\n", aktuellerZustand, zustände[i].to);
            zustände[i].transition();
            aktuellerZustand =  zustände[i].to;
        }
    }
    return 0;
}
