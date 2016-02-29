
#ifndef SERVOMONITOR_H
#define SERVOMONITOR_H
#include <Servo.h>

void AttachServos();
void WriteServoServoPosition(int theServo, int dutyCycle);
void WriteServo1(int dutyCycle);
void WriteServo2(int dutyCycle);
void MonitorMotorIncrementButton(unsigned int *dutyCycle, unsigned int dutyMax, void (*WriteServo)(int duty));
void MonitorMotorDecrementButton(unsigned int *dutyCycle, unsigned int dutyMin, void (*WriteServo)(int duty));
void MonitorCenterButton();
void MonitorRelayButton();

void MotorController(int servoMotor, int option);
void MoveMotor1(int option);
void MoveMotor2(int option);
//void MonitorMotor1Buttons();
//void MonitorMotor2Buttons();

#endif
