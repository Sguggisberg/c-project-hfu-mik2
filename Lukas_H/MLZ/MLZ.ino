#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <Servo.h>
//#include "libraries/Servo1.h" //Servo Bibliothek mit direktem Pfad einbinden - Arduino IDE verträgt relative Pfade nicht gut.

#define DEBUG_FLAG 1
#define WAIT_TIME_SERVO 2000
#define BAUD 115200

#define START_BUTTON_PIN 2
#define LED_PIN_INDICATOR_OPEN 7
#define LED_PIN_INDICATOR_CLOSED 8
#define PIEZO_PIN 10
#define SERVO_PIN 9

void StateMachine();
uint8_t ReadKeyInput();
uint8_t KeyGeneration();
void WriteLed();
void PlayTone();
bool CheckCode();
int ServoMove();
Servo DoorMotor; //Servo Instanz mit Namen DoorMotor erstellen und mit Pin 9 initialisieren. 
String current_State;


int main(void){
  //Entspricht dem Setup Part der Arduino IDE.
  
  if (DEBUG_FLAG){
    Serial.begin(BAUD); //Wenn schon Serial für Debug dann wenigstens schnell -> von 9600 auf 115200 BAUD gesetzt.
    while (Serial.available() != 1){  } //Warten auf Serielle Verbindung 
    Serial.println("Connected");
  }

  //Hardware INIT
  pinMode(START_BUTTON_PIN, INPUT);
  pinMode(LED_PIN_INDICATOR_OPEN, OUTPUT);
  pinMode(LED_PIN_INDICATOR_CLOSED, OUTPUT);
  pinMode(PIEZO_PIN, OUTPUT);
  
  DoorMotor.attach(SERVO_PIN);
  //DoorMotor.begin();
  //Button Setup
  const int INPUT_BTN[]={2, 3, 4, 5}; //Physische Taster Array erstellen und Pinzuweisen. const sperrt das Array als Readonly
  for (int i = 0; 0<4; i++){
    pinMode(INPUT_BTN[i], INPUT_PULLUP); //Durch Taster Array iterieren und als Input mit Pullup definieren.
  }
  
  while(1){ //Entspricht dem loop Part der Arduino IDE.
    RunStateMachine();
    

  }
  return 0; // Wird nie erreicht
}

void RunStateMachine(){
  //Aktuellen Zeitstempel des System holen.
  static unsigned long LastStateChange = millis();
  
  //class sperrt door_states in den definierten Zahlen ein
  enum class door_states : uint8_t { 
    DOOR_OPEN, // State 0
    DOOR_CLOSED,     // State 1
    DOOR_OPENING,       // State 2
    DOOR_CLOSING    // State 3
  };
  
  //Aktuellen Zustand speichern
  static door_states current_State = door_states::DOOR_OPEN;

  //Abfolge siehe State Diagram
  switch (current_State) {

    //Initial Status Tuere ist offen
    case door_states::DOOR_OPEN:
      //Start Taster abfragen
      //Codegen
      //Startbestätigt
      current_State = door_states::DOOR_CLOSING;
    break;

    //Tuere ist geschlossen
    case door_states::DOOR_CLOSED:
      //Start Taster abfragen
      //USERINPUT CODE
      //CHECKCODE
      //DOORUNLOCK
      current_State = door_states::DOOR_OPENING;
      LastStateChange = millis();
    break;

    //Tuere ist in Bewegung
    case door_states::DOOR_OPENING:
      //Frage Systemzeit ab 
      //WENN Systemzeit - LetzteZeitstempel >= Wartezeit Servo -> dann setze neuen Status und neuen Zeitstempel
      if (millis()-LastStateChange >= WAIT_TIME_SERVO){
        current_State = door_states::DOOR_OPEN;
        LastStateChange = millis();
      }
    break;

    //Tuere ist in Bewegung
    case door_states::DOOR_CLOSING:
      //Frage Systemzeit ab 
      //WENN Letzter Wechsel + Wartezeit Servo < aktuelle Zeit dann setze neuen Status
      if (millis()-LastStateChange >= WAIT_TIME_SERVO){
        current_State = door_states::DOOR_CLOSED;
        LastStateChange = millis();
      }
    break;
    default:
      //Default erreicht - Verbotener Zustand Fehler melden
    if (DEBUG_FLAG){
      Serial.println("ERROR - undefined STATE");
    }
  }
}


uint8_t ReadKeyInput(){};

uint8_t KeyGeneration(){
  uint8_t SystemKey[] = {10,10,10,10};
  for (int i=0; i<=4; i++){
    randomSeed(millis()); 
    SystemKey[i] = random(4);
    delay(random(100));
    if (DEBUG_FLAG){
      Serial.print("Key ");
      Serial.print(i);
      Serial.print("="); 
      Serial.println(SystemKey[i]);
    }
  }

};

void WriteLed(){
  
};

void PlayTone(uint8_t InputVar){
  uint8_t Tondauer = 250; //ms
  switch(InputVar){
    
    //SystemReady
    case 0:
    if (DEBUG_FLAG){
      Serial.println("System bereit");
    }
    tone(PIEZO_PIN,400,Tondauer);
    delay(Tondauer);
    tone(PIEZO_PIN,400,Tondauer);
    break;

    //Taste 1 gedrückt
    case 1:
    if (DEBUG_FLAG){
      Serial.println("Taste 1 betaetigt");
    }
    tone(PIEZO_PIN,400,Tondauer);
    break;

    //Taste 2 gedrückt
    case 2:
    if (DEBUG_FLAG){
      Serial.println("Taste 2 betaetigt");
    }
    tone(PIEZO_PIN,405,Tondauer);
    break;

    //Taste 3 gedrückt
    case 3:
    if (DEBUG_FLAG){
      Serial.println("Taste 3 betaetigt");
    }
    tone(PIEZO_PIN,410,Tondauer);
    break;

    //Taste 4 gedrückt
    case 4:
    if (DEBUG_FLAG){
      Serial.println("Taste 4 betaetigt");
    }
    tone(PIEZO_PIN,415,Tondauer);
    break;
    
    //Taste 5 gedrückt
    case 5:
    if (DEBUG_FLAG){
      Serial.println("Taste 5 betaetigt");
    }
    tone(PIEZO_PIN,420,Tondauer);
    break;

    //Code richtig
    case 6:
    if (DEBUG_FLAG){
      Serial.println("Code korrekt");
    }
    tone(PIEZO_PIN,200,Tondauer);
    delay(Tondauer);
    tone(PIEZO_PIN,300,Tondauer);
    delay(Tondauer);
    tone(PIEZO_PIN,400,Tondauer);
    delay(Tondauer);    
    break;

    //Code falsch
    case 7:
    if (DEBUG_FLAG){
      Serial.println("Code falsch");
    }
    tone(PIEZO_PIN,65,Tondauer);
    delay(Tondauer);
    tone(PIEZO_PIN,80,Tondauer);
    delay(Tondauer);
    tone(PIEZO_PIN,95,Tondauer);
    delay(Tondauer);
    break;
  }
}

bool CheckCode(){};

int ServoMove(int Direction){ //Direction "1" oeffne Tuere, Direction "0" schliesse Tuere
  if (Direction == 0){
    //DoorMotor.SetPosition(180);
    DoorMotor.write(180);
  } else {
    //DoorMotor.SetPosition(0);
    DoorMotor.write(0);
  }
}