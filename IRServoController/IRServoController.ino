#include <Event.h>
#include <Timer.h>
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

Timer eepromWriteServo1Timer;
Timer eepromWriteServo2Timer;

IRrecv irrecv(RECV_PIN);
decode_results results;

void InitializePins() {
  
    pinMode(relayOutputPin, OUTPUT);
    pinMode(ledPin, OUTPUT);
}

void InitializeEepromTimer(int servoMotor)
{
  if (servoMotor == FirstServo)
  {
  eepromWriteServo1Timer.after(600, CallBack1);
  }
  else
  {
   eepromWriteServo2Timer.after(600, CallBack2);
  }
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
  eepromWriteServo1Timer.update();
  eepromWriteServo2Timer.update();
    
    if (irrecv.decode(&results)) {

       TranslateIR(&results);
        Serial.println(results.value, HEX);
        irrecv.resume(); // Receive the next value
    }
    delay(100);
    wdt_reset();
}
