#ifndef ROBOT_H
#define ROBOT_H

#include "grape.h"

#define ROBOT_DEV_PATH "/dev/ttyUSB3"
#define ROBOT_BAUD 115200
#define ROBOT_MM_TO_PULSE 438 //1毫米对应的脉冲数



extern int robotSerial;
extern pthread_t robotThreadHandle;
extern char robotRecvBuff[1024];
extern int robotRecvOffset;

void Robot_Init();
void Robot_Start();


void Robot_Test();
void Robot_MoveX(double speed);
void Robot_MoveY(double speed);
void Robot_MoveZ(double speed);
void Robot_Stop();





#endif