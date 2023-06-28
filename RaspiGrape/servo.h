#ifndef SERVO_H
#define SERVO_H

#include "grape.h"


#define SERVO_DEV_PATH "/dev/ttyUSB2"
#define SERVO_BAUD 115200


enum SERVO_TAG
{
    SERVO_TAG_YUNTAI = 1,
    SERVO_TAG_L1 = 2,
    SERVO_TAG_L2 = 3,
    SERVO_TAG_L3 = 4,
    SERVO_TAG_ClawL = 5,
    SERVO_TAG_ClawR = 6,
};


struct ServoInfo
{
    uint16_t yuntaiSpeed = 0;
    uint16_t yuntaiPos = 0;
    uint16_t l1Speed = 0;
    uint16_t l1Pos = 0;
    uint16_t l2Speed = 0;
    uint16_t l2Pos = 0;
    uint16_t l3Speed = 0;
    uint16_t l3Pos = 0;
    uint16_t clawLSpeed = 0;
    uint16_t clawLPos = 0;
    uint16_t clawRSpeed = 0;
    uint16_t clawRPos = 0;
};

extern pthread_t servoThreadHandle;
extern int servoSerial;
extern char servoRecvBuff[1024];
extern int servoRecvOffset;

extern volatile struct ServoInfo servoInfo;

void Servo_Init();
void Servo_Start();

void SetServoPos(enum SERVO_TAG servoTag, uint16_t pos, uint16_t speed);
void GetServoPos(enum SERVO_TAG servoTag);
void UpdateServoPos();



#endif