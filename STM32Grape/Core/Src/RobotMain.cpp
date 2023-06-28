#include "RobotMain.h"


RDK::EncodingMotor encodingMotor1;
RDK::EncodingMotor encodingMotor2;
RDK::EncodingMotor encodingMotor3;
RDK::EncodingMotor encodingMotor4;
RDK::MecanumMotion mecanumMotion;


void Motor1Callback(double pwm)
{
    if (pwm > 0) {
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, pwm);
        HAL_GPIO_WritePin(MOTOR1_DIRECTION_GPIO_Port, MOTOR1_DIRECTION_Pin, GPIO_PIN_RESET);
    } else if (pwm < 0) {
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 1000 + pwm);
        HAL_GPIO_WritePin(MOTOR1_DIRECTION_GPIO_Port, MOTOR1_DIRECTION_Pin, GPIO_PIN_SET);
    } else {
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
        HAL_GPIO_WritePin(MOTOR1_DIRECTION_GPIO_Port, MOTOR1_DIRECTION_Pin, GPIO_PIN_RESET);
    }
}

void Motor2Callback(double pwm)
{
    if (pwm > 0) {
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, pwm);
        HAL_GPIO_WritePin(MOTOR2_DIRECTION_GPIO_Port, MOTOR2_DIRECTION_Pin, GPIO_PIN_RESET);
    } else if (pwm < 0) {
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 1000 + pwm);
        HAL_GPIO_WritePin(MOTOR2_DIRECTION_GPIO_Port, MOTOR2_DIRECTION_Pin, GPIO_PIN_SET);
    } else {
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
        HAL_GPIO_WritePin(MOTOR2_DIRECTION_GPIO_Port, MOTOR2_DIRECTION_Pin, GPIO_PIN_RESET);
    }
}

void Motor3Callback(double pwm)
{
    if (pwm > 0) {
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, pwm);
        HAL_GPIO_WritePin(MOTOR3_DIRECTION_GPIO_Port, MOTOR3_DIRECTION_Pin, GPIO_PIN_RESET);
    } else if (pwm < 0) {
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 1000 + pwm);
        HAL_GPIO_WritePin(MOTOR3_DIRECTION_GPIO_Port, MOTOR3_DIRECTION_Pin, GPIO_PIN_SET);
    } else {
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
        HAL_GPIO_WritePin(MOTOR3_DIRECTION_GPIO_Port, MOTOR3_DIRECTION_Pin, GPIO_PIN_RESET);
    }
}

void Motor4Callback(double pwm)
{
    if (pwm > 0) {
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, pwm);
        HAL_GPIO_WritePin(MOTOR4_DIRECTION_GPIO_Port, MOTOR4_DIRECTION_Pin, GPIO_PIN_RESET);
    } else if (pwm < 0) {
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 1000 + pwm);
        HAL_GPIO_WritePin(MOTOR4_DIRECTION_GPIO_Port, MOTOR4_DIRECTION_Pin, GPIO_PIN_SET);
    } else {
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);
        HAL_GPIO_WritePin(MOTOR4_DIRECTION_GPIO_Port, MOTOR4_DIRECTION_Pin, GPIO_PIN_RESET);
    }
}

void RobotInit()
{
    encodingMotor1.SetPID(4, 0.4, 0);
    encodingMotor1.SetOutputRange(-1000, 1000);
    encodingMotor1.SetSpeed(0);
    encodingMotor1.SetCallback(Motor1Callback);
    encodingMotor1.SetReverse(true);

    encodingMotor2.SetPID(4, 0.4, 0);
    encodingMotor2.SetOutputRange(-1000, 1000);
    encodingMotor2.SetSpeed(0);
    encodingMotor2.SetCallback(Motor2Callback);

    encodingMotor3.SetPID(4, 0.4, 0);
    encodingMotor3.SetOutputRange(-1000, 1000);
    encodingMotor3.SetSpeed(0);
    encodingMotor3.SetCallback(Motor3Callback);
    encodingMotor3.SetReverse(true);

    encodingMotor4.SetPID(4, 0.4, 0);
    encodingMotor4.SetOutputRange(-1000, 1000);
    encodingMotor4.SetSpeed(0);
    encodingMotor4.SetCallback(Motor4Callback);

    mecanumMotion.SetEncodingMotor1(&encodingMotor1);
    mecanumMotion.SetEncodingMotor2(&encodingMotor2);
    mecanumMotion.SetEncodingMotor3(&encodingMotor3);
    mecanumMotion.SetEncodingMotor4(&encodingMotor4);
}

void RobotTick()
{
    short speed = 0;

    speed = (short) __HAL_TIM_GET_COUNTER(&htim2);
    __HAL_TIM_SET_COUNTER(&htim2, 0);
    encodingMotor1.AddPulse(speed);
    encodingMotor1.Tick();

    speed = (short) __HAL_TIM_GET_COUNTER(&htim3);
    __HAL_TIM_SET_COUNTER(&htim3, 0);
    encodingMotor2.AddPulse(speed);
    encodingMotor2.Tick();

    speed = (short) __HAL_TIM_GET_COUNTER(&htim4);
    __HAL_TIM_SET_COUNTER(&htim4, 0);
    encodingMotor3.AddPulse(speed);
    encodingMotor3.Tick();

    speed = (short) __HAL_TIM_GET_COUNTER(&htim8);
    __HAL_TIM_SET_COUNTER(&htim8, 0);
    encodingMotor4.AddPulse(speed);
    encodingMotor4.Tick();

}

void RobotTest()
{
    mecanumMotion.ClearSpeed();
    mecanumMotion.AddXSpeed(30);
    mecanumMotion.CommitSpeed();
    HAL_Delay(2000);
    mecanumMotion.ClearSpeed();
    mecanumMotion.AddYSpeed(30);
    mecanumMotion.CommitSpeed();
    HAL_Delay(2000);
    mecanumMotion.ClearSpeed();
    mecanumMotion.AddZSpeed(30);
    mecanumMotion.CommitSpeed();
    HAL_Delay(2000);
    mecanumMotion.ClearSpeed();
    mecanumMotion.CommitSpeed();
}