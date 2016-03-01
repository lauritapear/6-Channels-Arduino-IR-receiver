
#ifndef IRSERVOCONTROLLER_H
#define IRSERVOCONTROLLER_H

#include <Event.h>
#include <Timer.h>

#define RELAY_OUTPUT_PIN  8
#define RECV_PIN  11
#define LED_PIN  13

#define CENTERED_DUTY 90
#define DUTY_DELTA 5
#define DUTY1_MAX 160
#define DUTY2_MAX 160
#define DUTY1_MIN 20
#define DUTY2_MIN 20

#define INCREMENT_BUTTON_ONE_SIGNAL (0xA90)
#define DECREMENT_BUTTON_ONE_SIGNAL (0xF50)
#define INCREMENT_BUTTON_TWO_SIGNAL (0xC20)
#define DECREMENT_BUTTON_TWO_SIGNAL (0xE78)
#define CENTER_BUTTON_SIGNAL (0xD12)
#define RELAY_BUTTON_SIGNAL (0xB33)

enum
{
   FirstServo = 0,
   SecondServo,
   MaxNumberOFServos 
};

enum
{
   Increment = 0,
   Decrement,
   MaxOption 
};

void InitializeEepromTimer(int servoMotor);
void sleepNow();

#endif
