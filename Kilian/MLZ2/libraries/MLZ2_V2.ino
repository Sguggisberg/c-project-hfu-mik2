/****************************************************************
MLZ Programm MC2 - Elektronisches Schloss 2.0
Datum 05.11.2024
Klasse E24, Andreas Rosenkranz, Kilian Langhans, Leon Rhoweder, Lukas Kageyama, Lukas Hollauer, Steffan Gugisberger, Thoma Grob,

Projekt Beschreibung:
Elektronisches Schloss. Das Elektronische schloss soll mit 5 Taster 6 LED, optionalem Piezo und
Motor,Anzeigen können ob ein schloss zu oder offen ist.
Das Schloss wird mit einer Kombination durch 4 Taster mit 4 Anzeige LED eingegeben. 
Anzahl Eingaben 4. Das Passwort, soll nach drücken von Start generiert werden.
Die 4 LED zeigen die Reihenfolge der zu drückenden tasten.
Nachdem die Tasten wie gezeigt richtig betätigt wurden, wechselt das schloss auf zu.mit dem
erneuten betätigen von Start, wird das öffnen begonnen.
Mit der richtigen Kombination öffnet das schloss wieder.

Neu gegenüber der ersten version ist:
Aufbau mit Statemachine.
Weitere verbeserungen....

Infos zu den Funktionen:
*Input: Einlesen und Weitergabe Taster mit Entprellung, Schalterentprellung: 30 ms
Präfix, Sufix:
v=Variable, i=Intern
****************************************************************/

//Bibliotheken
#include <stdint.h>
#include <Servo1.h> // Bibliothek für Servo einbinden
#include <Variabeln.h>
#include <Functions.h>

//Inizialisierung, Setzen Ein/Ausgänge
void setup() {
 //Inizialisierung
 pinMode(Switch5,   INPUT);
 pinMode(LED_Open,  OUTPUT);
 pinMode(LED_Closed,OUTPUT);
 pinMode(Piezo,     OUTPUT);
 //Normalisierung
 pinMode(LED_Switch1,INPUT);
 pinMode(LED_Switch2,INPUT);
 pinMode(LED_Switch3,INPUT);
 pinMode(LED_Switch4,INPUT);
 //Serielle verbindung zum Debugen
 Serial.begin(9600);
 //Inizialisierung Motor
 Schloss.begin();                             //<-/////Marker///////////////////////////////////////////////////////////////

 // Anzahl der Zustände aus dem Array bestimmen                                 ???????????????????????????????????????????????????????????
#define ANZAHL_ZUSTÄNDE (sizeof(zustände) / sizeof(Zustand))
int main() {
  init();
  bool initFinishd = false;

 //Inizialisierung des Anfang States
 int aktuellerZustand = TÜR_GESCHLOSSEN;
 runStateMchine();
 //Meldung Bereit
 OutputTone(0);  //Tone Bereit "0"
}

//Main Programm Schleife
void loop() {
  // Zustandsprüfung "Save" Offen/Zu
  if (vClosed == false){
  digitalWrite(LED_Open,   HIGH);
  digitalWrite(LED_Closed, LOW);
  }else{
  digitalWrite(LED_Open,   LOW);
  digitalWrite(LED_Closed, HIGH);
  }
  
  //Programm Ablauf
      switch (aktuellerZustand) {
      case TÜR_OFFEN:
      //Aufrecht erhaltung LED Anzeige - offen Zu
      digitalWrite(LED_Open,   HIGH);
      digitalWrite(LED_Closed, LOW);
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
            }}
            break;

          case TÜR_GESCHLOSSEN:
          //Aufrecht erhaltung LED Anzeige - offen Zu
            digitalWrite(LED_Open,   LOW);
            digitalWrite(LED_Closed, HIGH);
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
                }}
                break;
            }
} //Ende Void Loop
