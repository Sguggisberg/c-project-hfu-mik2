#include "Arduino_h"
#include "Servo1_h"

Servo1::Servo1


void Servo1::begin()
{    
    DDRB    |= 1 << DDB1;                               // PIN 9 als Ausgang setzen
    TCCR1A  = 1 << COM1A1 | 1 << COM1B1 | 1 << WGM11;   // FastPWM Mode mode -- TOP determined by ICR1 - non-inverting Compare Output mode
    TCCR1B  = 1 << WGM13 | 1 << WGM12 | 1 << CS11;      // Prescaler 8, FastPWM Mode mode continued 16MHz / 2^16 / 8 = 32.768ms
    ICR1    = 40000;                                    // 32.768ms/2^16*20.000ms = 40000Setze Periode 20 ms
    OCR1A   = 1500;                                     // 2000 = 1ms, 3000 = 1.500ms 4000 = 2ms
    TCNT1   = 0;                                        // reset timer
}

void Servo1::SetPosition (uint16_t value) {
    if (value <= 180) {
        value = map(value, 0, 180, 1000, 4200);             // Anpassung an SG90 MicroServo
    } else {
        // Alternativ Ausgangssignalauflösung 0,5 us
        value *= 2;
    }
    OCR1A = value; // Pin9
    
}
