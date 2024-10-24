/****************************************************************
MLZ Programm MC1 - Elektronisches Schloss
Datum 03.07.2024
Klasse E24, Andreas Rosenkranz, Kilian Langhans, Leon Rhoweder, Lukas Kageyama, Lukas Hollauer, Steffan Gugisberger, Thoma Grob, Wilmar Rodriguez, 

Projekt Beschreibung:
Elektronisches Schloss. Das Elektronische schloss soll mit 5 Taster 6 LED, optionalem Piezo und
Motor,Anzeigen können ob ein schloss zu oder offen ist.
Das Schloss wird mit einer Kombination durch 4 Taster mit 4 Anzeige LED eingegeben.Anzahl
Eingaben 4.Das Passwort, soll nach drücken von Start generiert werden.
Die 4 LED zeigen die Reihenfolge der zu drückenden tasten.
Nachdem die Tasten wie gezeigt richtig betätigt wurden, wechselt das schloss auf zu.mit dem
erneuten betätigen von Start, wird das öffnen begonnen.
Mit der richtigen Kombination öffnet das schloss wieder.

Infos zu den Funktionen:
*Input: Einlesen und Weitergabe Taster mit Entprellung, Schalterentprellung: 30 ms
Präfix, Sufix:
v=Variable, i=Intern
****************************************************************/

//Bibliotheken
#include <stdint.h>
#include <Servo1.h> // Bibliothek für Servo einbinden


//Funktionsinitialisierung
uint8_t ReadKey   (); //Eingabe Einlesen
void    KeyGen    (); //Code Generieren
void    WriteLED  (); //Code Ausgeben
void    OutputTone(); //Piezo Tound Ausgabe
bool    CodeCheck (); //Code Abfolge Prüfen
bool    CheckKey  (); //Einzelne Code Eingaben Prüfen
void    SchlossAufTrue();  //Servo steuerung


//Variabeln Global
//Konstanten
const int Switch5     = 2;     //Variable Schalter Start
const int LED_Switch4 = 3;     //Variable Led zu
const int LED_Switch3 = 4;     //Variable Led zu
const int LED_Switch2 = 5;     //Variable Led zu
const int LED_Switch1 = 6;     //Variable Led zu
const int LED_Open    = 7;     //Variable Led zu
const int LED_Closed  = 8;     //Variable Led zu
const int Piezo      = 10;     //Variable Led zu
//Variabeln
bool vClosed       = false;    //"Save" Zustand Offen/Zu
bool vKeyStatus    = false;    //Prüfung einzeleingabe
bool vCodeRichtig  = false;    //Prüfung Cesamt Code
uint8_t vEingabe;              // User Eingabewert
uint8_t vKeyNr1    = 10;       // Code Wert1
uint8_t vKeyNr2    = 10;       // Code Wert2
uint8_t vKeyNr3    = 10;       // Code Wert3
uint8_t vKeyNr4    = 10;       // Code Wert4
Servo1 Schloss(9);     //Servo deklarieren mit Pin   //<-/////Marker/////////////////////////////////////////////////////

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//Grundcode
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

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
 Schloss.begin();     //<-/////Marker///////////////////////////////////////////////////////////////
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
  if (vClosed == false){
      vEingabe = ReadKey();
      switch (vEingabe){
      case 4:
      KeyGen();          //Code generieren
      //Ausgabe des Codes
      delay(500);        //Verhindert soundüberschneidung
      WriteLED(vKeyNr1);
      WriteLED(vKeyNr2);
      WriteLED(vKeyNr3);
      WriteLED(vKeyNr4);
      //Code eingabe und Prüfung
      vCodeRichtig = CodeCheck();   //Prüfung Code
        if (vCodeRichtig == true) { //Bei Richtig
        vClosed = true;             //"Save" Schliessen
        OutputTone(6);              //Sound für Richtige eingabe
        SchlossAufTrue(true);                     //<-/////Marker//////////////////////////////////////////////////
        }else{                        //Bei Falsch
        OutputTone(7);                //Sound für Falsch
        }
      break; }
  }else{  //Wenn bereits Zu
    vEingabe = ReadKey();
      switch (vEingabe){
      case 4:
      delay(250);
      //Code eingabe und Prüfung
      vCodeRichtig = CodeCheck();   //Prüfung Code
        if (vCodeRichtig == true) { //Bei Richtig
        vClosed = false;             //"Save" Oeffnen
        OutputTone(6);              //Sound für Richtige eingabe
        SchlossAufTrue(false);                     //<-/////Marker////////////////////////////////////////////////////
        }else{                        //Bei Falsch
        OutputTone(7);                //Sound für Falsch
        }
      break; }
   }
}


//Funktionen
//Einlesen User Eingabe
uint8_t ReadKey (){
      uint8_t viEingabe = 10; // Variable Intern Usereingabe

      //Tasterwahl Int 0-4, mit Tonausgabe.
      while (viEingabe == 10){
        if (digitalRead(LED_Switch1)==0){
          viEingabe = 0;
          OutputTone(1);
          }   
        if (digitalRead(LED_Switch2)==0){
        viEingabe = 1;
        OutputTone(2);
          } 
        if (digitalRead(LED_Switch3)==0){
        viEingabe = 2;
        OutputTone(3);
          }
        if (digitalRead(LED_Switch4)==0){
        viEingabe = 3;
        OutputTone(4);
          } 
        if (digitalRead(Switch5)==0){
        viEingabe = 4;
        OutputTone(5);
        } }

        return(viEingabe);  //Rückgabe des Taster Wertes
}

//Key Generierung
void KeyGen() {
//4x Generierung von Codes 0-3, als Tastenwerte.
vKeyNr1 = random(4);    
vKeyNr2 = random(4);    
vKeyNr3 = random(4);    
vKeyNr4 = random(4);  
//Zum Debuggen Code Werte
Serial.println(vKeyNr1);
Serial.println(vKeyNr2);
Serial.println(vKeyNr3);
Serial.println(vKeyNr4); 
}

//Ausgabe LED Code
void WriteLED(uint8_t viKeyNr){
  //Interne Variable
  uint8_t viDauer = 2000;        //Dauer LED Leuchten

  //Umstellung zu Output
  digitalWrite(LED_Switch1, HIGH);   // turn the LED off by making the voltage LOW
  digitalWrite(LED_Switch2, HIGH);   // turn the LED off by making the voltage LOW
  digitalWrite(LED_Switch3, HIGH);   // turn the LED off by making the voltage LOW
  digitalWrite(LED_Switch4, HIGH);   // turn the LED off by making the voltage LOW
  pinMode(LED_Switch1,OUTPUT);
  pinMode(LED_Switch2,OUTPUT);
  pinMode(LED_Switch3,OUTPUT);
  pinMode(LED_Switch4,OUTPUT);
  //LED Abgrenzung
  delay(viDauer); 
  //LED Ansteuerung
  switch(viKeyNr){
  case 0:
  OutputTone(1);
  digitalWrite(LED_Switch1, LOW);  // turn the LED on (HIGH is the voltage level)
  delay(viDauer);                         // wait for a second
  digitalWrite(LED_Switch1, HIGH);   // turn the LED off by making the voltage LOW
  break; 

  case 1:
  OutputTone(2);
  digitalWrite(LED_Switch2, LOW);  // turn the LED on (HIGH is the voltage level)
  delay(viDauer);                          // wait for a second
  digitalWrite(LED_Switch2, HIGH);   // turn the LED off by making the voltage LOW
  break; 
          
  case 2:
  OutputTone(3);
  digitalWrite(LED_Switch3, LOW);  // turn the LED on (HIGH is the voltage level)
  delay(viDauer);                          // wait for a second
  digitalWrite(LED_Switch3, HIGH);   // turn the LED off by making the voltage LOW
  break; 
          
  case 3:
  OutputTone(4);
  digitalWrite(LED_Switch4, LOW);  // turn the LED on (HIGH is the voltage level)
  delay(viDauer);                          // wait for a second
  digitalWrite(LED_Switch4, HIGH);   // turn the LED off by making the voltage LOW
  break; 
  }
 //Zurückstellung zu Input   
 pinMode(LED_Switch1,INPUT);
 pinMode(LED_Switch2,INPUT);
 pinMode(LED_Switch3,INPUT);
 pinMode(LED_Switch4,INPUT);
}

//Piezo Sound Output
//Output Möglichkeiten: 0=Rdy, 1=Schalter1, 2=Schalter2, 3=Schalter3, 4 =Schalter4, 5=Schalter5, 6=Eingabe Richtig, 7=Eingabe Falsch
void OutputTone(uint8_t vTonNr){
uint8_t viDauer = 250;              //Variable um Dauer Allgemein einzustellen, Länge sowie Pause
switch (vTonNr) {
case 0: //Ready
tone(Piezo, 400, viDauer);
delay(viDauer);
tone(Piezo, 450, viDauer);
break;
case 1: //Taste1
tone(Piezo, 400, viDauer);
break;
case 2:  //Taste2
tone(Piezo, 405, viDauer);
break;
case 3:  //Taste3
tone(Piezo, 410, viDauer);
break;
case 4:  //Taste4
tone(Piezo, 415, viDauer);
break;
case 5:  //Taste5
tone(Piezo, 400, viDauer);
break;
case 6:  //Richtig
tone(Piezo, 200, viDauer);
delay(viDauer);
tone(Piezo, 300, viDauer);
delay(viDauer);
tone(Piezo, 400, viDauer);
break;
case 7:  //Falsch
tone(Piezo, 65, viDauer);
delay(viDauer);
tone(Piezo, 80, viDauer);
delay(viDauer);
tone(Piezo, 95, viDauer);
break;}
}

//Prufung Code Eingabe
bool CodeCheck() {

  vEingabe = ReadKey ();                      //Einlesen User Eingabe
  vKeyStatus = CheckKey(vKeyNr1, vEingabe);   //Prüfen User Eingabe
  if(vKeyStatus==true){
    Serial.println("Nr1");
    delay(500);
    vEingabe = ReadKey ();
    vKeyStatus = CheckKey(vKeyNr2, vEingabe);
    if(vKeyStatus==true){
      Serial.println("Nr2");
      delay(500);
      vEingabe = ReadKey ();
      vKeyStatus = CheckKey(vKeyNr3, vEingabe);
      if(vKeyStatus==true){
        Serial.println("Nr3");
        delay(500);
        vEingabe = ReadKey ();
        vKeyStatus = CheckKey(vKeyNr4, vEingabe);
        if(vKeyStatus==true){
        Serial.println("Nr4");
        return (true);

     }else{ //Falsches PW
     return (false);
     }}else{ //Falsches PW
     return (false);
     }}else{ //Falsches PW
     return (false);
     }}else{ //Falsches PW
     return (false);
    }
}

//Einzel Prufung Code Eingabe
bool CheckKey(uint8_t viKeyNr,uint8_t viUserEingabe){
bool viKeyStat = viKeyNr==viUserEingabe;
return (viKeyStat);
}



//Motoransteuerung                                                           //<-/////Marker////////////////////
void    SchlossAufTrue(bool Auf){
  if (Auf == true){  //Schloss Auf
    for (long i = 0; i <= 180; i =i+1) {
      Schloss.SetPosition(i); // Commando zum servo auf position (winkel in grad) schicken.
      Serial.println(i);
     delay(20);
    } 
  }
  if(Auf==false){    //Schloss Zu
    for (long i = 180; i >= 0; i =i-1) {
      Schloss.SetPosition(i);
      Serial.println(i);
      delay(20);
    }
  }
}
