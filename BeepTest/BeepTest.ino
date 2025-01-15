// Board: Digispark ATtiny85

#include <avr/io.h>
#include <util/delay.h>

// Pin assignment
#define PIEZO_PIN 1  // Pin for the piezo (PB1)

// Test values for beep
unsigned long beepOn = 500;  // Beep duration in milliseconds
unsigned long beepOff = 3000; // Pause duration in milliseconds

void setup() {
    pinMode(PIEZO_PIN, OUTPUT);  // Set piezo pin as output
}

void loop() {
    // Switch on piezo
    digitalWrite(PIEZO_PIN, HIGH);
    delay(beepOn);  // Beep for beepOn Duration
    
    // Switch off piezo
    digitalWrite(PIEZO_PIN, LOW);
    delay(beepOff);  // Pause for beepOff Duration
}
