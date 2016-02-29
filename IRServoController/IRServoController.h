
#ifndef IRSERVOCONTROLLER_H
#define IRSERVOCONTROLLER_H

#define CENTERED_DUTY1 90
#define CENTERED_DUTY2 90
#define DUTY_DELTA 5
#define DUTY1_MAX 160
#define DUTY2_MAX 160
#define DUTY1_MIN 20
#define DUTY2_MIN 20

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

#endif
