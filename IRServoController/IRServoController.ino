#include <EEPROM.h>
#include <Servo.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <avr/wdt.h>
#include "IRServoController.h"
#include "ServoMonitor.h"
#include "IRManager.h"
#include "EEPROMManager.h"

int RECV_PIN = 11;
int ledPin = 13;
int relayOutputPin = 8;

IRrecv irrecv(RECV_PIN);
decode_results results;

void InitializePins() {
  
    pinMode(relayOutputPin, OUTPUT);
    pinMode(ledPin, OUTPUT);
}

void setup() {
   
    AttachServos();
    InitializePins();
    
    Serial.begin(9600);
    irrecv.enableIRIn();

    SetServosToInitialPosition();
    
    wdt_enable(WDTO_1S); //Do we really need this?
}

void loop() {
    
    if (irrecv.decode(&results)) {

       TranslateIR(&results);
        Serial.println(results.value, HEX);
        irrecv.resume(); // Receive the next value
    }
    delay(100);
    wdt_reset();
}
