#include <IRremote.h>
#include <IRremoteInt.h>
#include "ServoMonitor.h"
#include "IRServoController.h"

void TranslateIR(decode_results *results)
{

  switch(results->value)
  {
    case 0x01:
    MotorController(FirstServo, Increment);
    break;
    
    case 0x02:
    MotorController(FirstServo, Decrement);
    break;

    case 0x03:
    MotorController(SecondServo, Increment);
    break;

    case 0x04:
    MotorController(SecondServo, Decrement);
    break;

    case 0x05:
    MonitorCenterButton();
    break;

    case 0x06:
    MonitorRelayButton();
    break;
  }
  
}


//if (irrecv.decode(&results)) {
//        //    digitalWrite(13, HIGH);
//        if(results.value == 0xC40BD816)
//        {
//            digitalWrite(13, HIGH);
//        }
//        else if(results.value == 0x4AB0F7B5)
//        {
//            digitalWrite(13, LOW);
//        }
//        Serial.println(results.value, HEX);
//        irrecv.resume(); // Receive the next value
//    }
//    delay(100);
