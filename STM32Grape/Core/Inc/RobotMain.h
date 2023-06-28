#ifndef ROBOTMAIN_H
#define ROBOTMAIN_H


#include "main.h"
#include "pid.h"
#include "motor.h"
#include "motion.h"
#include "tim.h"
#include "usart.h"

#ifdef __cplusplus
extern "C" {
#endif

    void RobotInit();
    void RobotTick();
    void RobotTest();
    void RobotMoveX(double speed);
    void RobotMoveY(double speed);
    void RobotMoveZ(double speed);
    void RobotStop();


#ifdef __cplusplus
}
#endif



#endif