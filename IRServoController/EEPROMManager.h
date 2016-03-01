#ifndef EEPROMMANAGER_H
#define EEPROMMANAGER_H

void ReadEeprom();
bool MicroIsReadyToSleep();
void SetServosToInitialPosition();
void WriteEeprom(int servoMotor);
void CallBack1();
void CallBack2();

void SetSleepFlag(int servoMotor, bool value);
bool GetSleepFlag(int servoMotor);

#endif
