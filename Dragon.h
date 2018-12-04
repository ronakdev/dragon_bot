#ifndef DRAGON_H
#define DRAGON_H

#include "Gadgetron.h"


#define DISTANCESENSOR_A A0        
DistanceSensor distanceSensor(DISTANCESENSOR_A);

#define PINCER_DATA 3        
Pincer pincer(PINCER_DATA);

#define SERVO_DATA 4        
ServoMotor TailServo(SERVO_DATA);

#define SERVO_2_DATA 5        
ServoMotor HeadServo(SERVO_2_DATA);

#define DRIVE_STBY 8        
#define DRIVE_PWMA 6        
#define DRIVE_AIN1 10        
#define DRIVE_AIN2 11        
#define DRIVE_PWMB 9        
#define DRIVE_BIN1 12        
#define DRIVE_BIN2 13        
Motor drive(DRIVE_STBY,DRIVE_PWMA,DRIVE_AIN1,DRIVE_AIN2,DRIVE_PWMB,DRIVE_BIN1,DRIVE_BIN2);


#endif
