
#include "ServoMonitor.h"
#include "IRServoController.h"
#include "Arduino.h"
#include "EEPROMManager.h"
#include <Servo.h>

extern "C" {
 #include <stddef.h>
 #include <stdint.h>
 #include <math.h>
}

static unsigned int dutyCycle1Counter = 0;
static unsigned int periodCounter = 0;
static unsigned int dutyCycle2Counter = 0;
static bool relayState = 0;
static unsigned int dutyCycle1 = CENTERED_DUTY;
static unsigned int dutyCycle2 = CENTERED_DUTY;

Servo servo1;
Servo servo2;

void AttachServos()
{
   servo1.attach(10);
   servo2.attach(9);
}

void WriteServoServoPosition(int theServo, int dutyCycle)
{
  if (theServo == FirstServo)
  {
    WriteServo1(dutyCycle);
  }
  else if (theServo == SecondServo)
  {
    WriteServo2(dutyCycle);
  }
}

void WriteServo1(int dutyCycle)
{
    servo1.write(dutyCycle);
}

void WriteServo2(int dutyCycle)
{
    servo2.write(dutyCycle);
}

void MonitorMotorIncrementButton(unsigned int *dutyCycle, unsigned int dutyMax, void (*WriteServo)(int duty))
{
    if(*dutyCycle < dutyMax)
    {
        *dutyCycle += DUTY_DELTA;
        WriteServo(*dutyCycle);
        delay(10);
    }
}

void MonitorMotorDecrementButton(unsigned int *dutyCycle, unsigned int dutyMin, void (*WriteServo)(int duty))
{
    if(*dutyCycle > dutyMin)
    {
        *dutyCycle -= DUTY_DELTA;
        WriteServo(*dutyCycle);
        delay(10);
    }
}

void MonitorCenterButton()
{
        SetSleepFlag(CenterFlag, false);
        dutyCycle1 = CENTERED_DUTY;
        dutyCycle2 = CENTERED_DUTY;
        WriteServo1(dutyCycle1);
        delay(10);
        WriteServo2(dutyCycle2);
        delay(10); 
        SetSleepFlag(CenterFlag, true);   
     if (MicroIsReadyToSleep())
    {
      sleepNow();
    }  
}

void MonitorRelayButton()
{
        relayState = !relayState;
        digitalWrite(RELAY_OUTPUT_PIN, relayState);
           SetSleepFlag(RelayFlag, true);   
     if (MicroIsReadyToSleep())
    {
      sleepNow();
    } 
}

void MotorController(int servoMotor, int option)
{
  if (servoMotor == FirstServo)
  {
    MoveMotor1(option);
  }else
  {
    MoveMotor2(option);
  }
}

void MoveMotor1(int option)
{
  if(option == Increment)
  {
    MonitorMotorIncrementButton(&dutyCycle1, DUTY1_MAX, WriteServo1);
  }else
  {
    MonitorMotorDecrementButton(&dutyCycle1, DUTY1_MIN, WriteServo1);
  }
}

void MoveMotor2(int option)
{
    if(option == Decrement)
    {
    MonitorMotorIncrementButton(&dutyCycle2, DUTY2_MAX, WriteServo2);
    }else
    {
    MonitorMotorDecrementButton(&dutyCycle2, DUTY2_MIN, WriteServo2);
    }
}

unsigned int GetDutyCycle(int servoMotor)
{
  if (servoMotor == FirstServo)
  {
    return dutyCycle1;
  }else
  {
    return dutyCycle2;
  }
}

