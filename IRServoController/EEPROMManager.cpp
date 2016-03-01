#include <EEPROM.h>
#include "ServoMonitor.h"
#include "IRServoController.h"
#include "EEPROMManager.h"

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
bool CenterReadyToSleep = true;
bool RelayReadyToSleep = true;

bool GetSleepFlag(int servoMotor);

void ReadEeprom()
{
  valueServo1 = EEPROM.read(addressFirstServo);
  valueServo2 = EEPROM.read(addressSecondServo);
}

bool MicroIsReadyToSleep()
{
  return GetSleepFlag(Servo1Flag) && GetSleepFlag(Servo2Flag)
  && GetSleepFlag(CenterFlag)&& GetSleepFlag(RelayFlag);
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

    if (MicroIsReadyToSleep())
    {
      sleepNow();
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

void SetSleepFlag(int flag, bool value)
{
  switch(flag)
  {
  case Servo1Flag:
  Servo1ReadyToSleep = value;
  break;  

  case Servo2Flag:
  Servo1ReadyToSleep = value;
  break;  

  case CenterFlag:
  CenterReadyToSleep = value;
  break; 

  case RelayFlag:
  RelayReadyToSleep = value;
  break; 
  }
}

bool GetSleepFlag(int flag)
{
  switch(flag)
  {
  case Servo1Flag:
  return Servo1ReadyToSleep;
  break;  

  case Servo2Flag:
  return Servo2ReadyToSleep;
  break;  

  case CenterFlag:
  return CenterReadyToSleep;
  break; 

  case RelayFlag:
  return RelayReadyToSleep;
  break; 
  }

}

