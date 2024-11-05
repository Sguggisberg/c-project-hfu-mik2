//Funktionen

#include "functions.h"

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