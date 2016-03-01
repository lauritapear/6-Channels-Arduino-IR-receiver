#include <IRremote.h>
#include <IRremoteInt.h>
#include "ServoMonitor.h"
#include "IRServoController.h"
#include "EEPROMManager.h"

void TranslateIR(decode_results *results)
{
  switch(results->value)
  {
    case INCREMENT_BUTTON_ONE_SIGNAL:
    MotorController(FirstServo, Increment);
    InitializeEepromTimer(FirstServo);
    break;
    
    case DECREMENT_BUTTON_ONE_SIGNAL:
    MotorController(FirstServo, Decrement);
    InitializeEepromTimer(FirstServo);
    break;

    case INCREMENT_BUTTON_TWO_SIGNAL:
    MotorController(SecondServo, Increment);
    InitializeEepromTimer(SecondServo);
    break;

    case DECREMENT_BUTTON_TWO_SIGNAL:
    MotorController(SecondServo, Decrement);
    InitializeEepromTimer(SecondServo);
    break;

    case CENTER_BUTTON_SIGNAL:
    MonitorCenterButton();
    break;

    case RELAY_BUTTON_SIGNAL:
    MonitorRelayButton();
    break;
  }
  
}

