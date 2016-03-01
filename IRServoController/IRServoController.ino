#include <Event.h>
#include <Timer.h>
#include <EEPROM.h>
#include <Servo.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <PinChangeInt.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <avr/sleep.h>
#include "IRServoController.h"
#include "ServoMonitor.h"
#include "IRManager.h"
#include "EEPROMManager.h"


Timer eepromWriteServo1Timer;
Timer eepromWriteServo2Timer;

IRrecv irrecv(RECV_PIN);
decode_results results;

void InitializePins() {
  
    pinMode(RELAY_OUTPUT_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
}

void InitializeEepromTimer(int servoMotor)
{
  if (servoMotor == FirstServo)
  {
  eepromWriteServo1Timer.after(600, CallBack1);
  SetSleepFlag(FirstServo,false);
  }
  else
  {
   eepromWriteServo2Timer.after(600, CallBack2);
   SetSleepFlag(SecondServo,false);
  }
}

void pinInterrupt()
{
  uint8_t latest_interrupted_pin = PCintPort::arduinoPin;
  Serial.println(latest_interrupted_pin);
  Serial.println("Interrupt");
  delay(20);

  detachInterrupt(0);
}

void sleepNow()
{
  set_sleep_mode(SLEEP_MODE_PWR_SAVE);

  attachPinChangeInterrupt(RECV_PIN, pinInterrupt, FALLING);

  sleep_enable();
  Serial.println("Going To sleep");
  sleep_mode();   // Put the device to sleep:

  // Upon waking up, sketch continues from this point.
  sleep_disable();
  Serial.println("Waking Up");
}

void setup() {
   
    AttachServos();
    InitializePins();
    
    Serial.begin(9600);
    irrecv.enableIRIn();

    SetServosToInitialPosition();
    
    wdt_enable(WDTO_1S); //Do we really need this?
    sleepNow();
}

void loop() {
  eepromWriteServo1Timer.update();
  eepromWriteServo2Timer.update();

    if (MicroIsReadyToSleep())
    {
      sleepNow();
    }
    
    if (irrecv.decode(&results)) {

       TranslateIR(&results);
       Serial.println(results.value, HEX);
       irrecv.resume(); // Receive the next value
    }
    delay(100);
    wdt_reset();
}
