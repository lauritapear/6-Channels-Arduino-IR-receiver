#include <EEPROM.h>
#include "ServoMonitor.h"
#include "IRServoController.h"

int addressFirstServo = 0;
int addressSecondServo = 0;
int valueServo1;
int valueServo2;

void ReadEeprom()
{
  valueServo1 = EEPROM.read(addressFirstServo);
  valueServo2 = EEPROM.read(addressSecondServo);
//  Serial.print(valueServo1, DEC);
//  Serial.println("Servo1 value at start:");
//  Serial.print(valueServo2, DEC);
//  Serial.println("Servo2 value at start:");
}

bool PositionValueOutOfRange(int ServoValue)
{
  return (ServoValue < DUTY2_MIN)||(ServoValue > DUTY1_MAX);
}

void SetServosToInitialPosition()
{
   ReadEeprom();
   
   if (PositionValueOutOfRange(valueServo1))
    {
      WriteServoServoPosition(FirstServo,CENTERED_DUTY);
    }
    else
    {
      WriteServoServoPosition(FirstServo, valueServo1);
    }

 if (PositionValueOutOfRange(valueServo2))
    {
      WriteServoServoPosition(SecondServo,CENTERED_DUTY);
    }
    else
    {
      WriteServoServoPosition(SecondServo, valueServo2);
    }
}

