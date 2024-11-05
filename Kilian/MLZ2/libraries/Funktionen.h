#ifndef __Funktionen_h
#define __Funktionen_h

#include "Arduino.h"
//Funktionsinitialisierung
uint8_t ReadKey(); //Eingabe Einlesen
void    KeyGen(); //Code Generieren
void    WriteLED(); //Code Ausgeben
void    OutputTone(); //Piezo Tound Ausgabe
bool    CodeCheck(); //Code Abfolge Prüfen
bool    CheckKey(); //Einzelne Code Eingaben Prüfen
void    SchlossAufTrue();  //Servo steuerung

//Funktionsaufruf (Funktionen in funktionen.c gespeichert)
extern uint8_t ReadKey();
extern void KeyGen();
extern void WriteLED();
extern void OutputTone();
extern bool CodeCheck();
extern bool CheckKey();
extern void SchlossAufTrue();

extern void zustandTürGeschlossen();
extern void zustandTürOffen();
#endif

