#include <EEPROM.h>
#include "ServoMonitor.h"
#include "IRServoController.h"

extern "C" {
 #include <stddef.h>
 #include <stdint.h>
 #include <math.h>
}

int addressFirstServo = 0;
int addressSecondServo = 0;
int valueServo1;
int valueServo2;
bool Servo1ReadyToSleep = true;
bool Servo2ReadyToSleep = true;

bool GetSleepFlag(int servoMotor);

void ReadEeprom()
{
  valueServo1 = EEPROM.read(addressFirstServo);
  valueServo2 = EEPROM.read(addressSecondServo);
}

bool MicroIsReadyToSleep()
{
  return GetSleepFlag(FirstServo) && GetSleepFlag(SecondServo);
}

void WriteEeprom(int servoMotor)
{
  if (servoMotor == FirstServo)
  {
  EEPROM.update(addressFirstServo, GetDutyCycle(FirstServo));
  }
  else
  {
  EEPROM.update(addressSecondServo, GetDutyCycle(SecondServo));
  }
}

void CallBack1()
{
  WriteEeprom(FirstServo);
}

void CallBack2()
{
  WriteEeprom(SecondServo);
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

void SetSleepFlag(int servoMotor, bool value)
{
  if (servoMotor == FirstServo)
  {
  Servo1ReadyToSleep = value;
  }
  else
  {
   Servo2ReadyToSleep = value;
  }
}

bool GetSleepFlag(int servoMotor)
{
  if (servoMotor == FirstServo)
  {
  return Servo1ReadyToSleep;
  }
  else
  {
   return Servo2ReadyToSleep;
  }
}

