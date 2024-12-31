// Board: Digispark ATtiny85

#include <avr/sleep.h>
#include <avr/interrupt.h>


// PB3 ist ungeeignet als DOOR_PIN, er wird als RESET Pin genutzt und ruft beim start unvorhersehbare Zustände vor.
#define DOOR1_PIN 2  // Pin für den Magnetschalter Tür 1 (PB2)
#define DOOR2_PIN 0  // Pin für den Magnetschalter Tür 2 (PB0)
#define PIEZO_PIN 1  // Pin für den Piezo und die Platinen LED (PB1)

const unsigned long delayTime = 3000; // Wartezeit bis Türalarm los geht
const unsigned long beepDurationOn = 1000;  // Piepton-Dauer
const unsigned long beepDurationOff = 1000; // Pause-Dauer zwischen Pieptönen

volatile bool doorOpen = false;  // Wird durch Interrupt gesetzt
unsigned long lastActionMillis = 0; // Letzte Aktivität
unsigned long beepMillis = 0;       // Letzter Piepton
bool piezoActive = false;

void setup() {

    lastActionMillis = millis();
  
    pinMode(DOOR1_PIN, INPUT_PULLUP);
    pinMode(DOOR2_PIN, INPUT_PULLUP);
    pinMode(PIEZO_PIN, OUTPUT);

    ADCSRA &= ~(1 << ADEN); // ADC dauerhaft deaktivieren, da er nicht benötigt wird

    PCMSK |= (1 << DOOR1_PIN) | (1 << DOOR2_PIN); // Überwachung von PB2 und PB0
    GIMSK |= (1 << PCIE); // Pin-Change-Interrupts aktivieren

    sei(); // Globale Interrupts aktivieren

}

void loop() {
    // Zustände der Türen prüfen
    doorOpen = (digitalRead(DOOR1_PIN) == HIGH) || (digitalRead(DOOR2_PIN) == HIGH);

    // Piezo aktivieren, wenn eine Tür offen ist und die Verzögerung abgelaufen ist
    if (doorOpen) {
        if (!piezoActive && millis() - lastActionMillis >= delayTime) {
            piezoActive = true; // Piezo nach Verzögerung aktivieren
            beepMillis = millis(); // Startzeitpunkt speichern
        }
    } else {
        piezoActive = false; // Piezo deaktivieren
    }

    // Piezo-Logik
    if (piezoActive) {
        // Piepton erzeugen
        if (millis() - beepMillis < beepDurationOn) {
            digitalWrite(PIEZO_PIN, HIGH); // Piezo einschalten
        }
        // Pause nach Piepton
        else if (millis() - beepMillis < beepDurationOn + beepDurationOff) {
            digitalWrite(PIEZO_PIN, LOW); // Piezo ausschalten
        }
        // Zyklus abschließen
        else {
            beepMillis = millis(); // Nächster Zyklus starten
        }
    } else {
        digitalWrite(PIEZO_PIN, LOW); // Piezo sicher deaktivieren
    }

    // Schlafmodus aktivieren, wenn keine Tür offen ist und der Piezo inaktiv ist
    if (!doorOpen && !piezoActive) {
        enterSleepMode();
    }
}

// Interrupt Service Routine (ISR) für Pin-Change
ISR(PCINT0_vect) {
    lastActionMillis = millis(); // Zeit der letzten Aktivität speichern
}

// Schlafmodus aktivieren
void enterSleepMode() {
    set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Stromsparmodus wählen
    sleep_enable();                      // Schlafmodus aktivieren
    sleep_cpu();                         // In den Schlafmodus wechseln
    sleep_disable();                     // Nach dem Aufwachen deaktivieren
}
