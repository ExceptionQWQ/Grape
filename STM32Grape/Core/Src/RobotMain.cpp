#include "RobotMain.h"


RDK::EncodingMotor encodingMotor1;
RDK::EncodingMotor encodingMotor2;
RDK::EncodingMotor encodingMotor3;
RDK::EncodingMotor encodingMotor4;



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
    encodingMotor1.SetSpeed(10);
    encodingMotor1.SetCallback(Motor1Callback);

    encodingMotor2.SetPID(4, 0.4, 0);
    encodingMotor2.SetOutputRange(-1000, 1000);
    encodingMotor2.SetSpeed(10);
    encodingMotor2.SetCallback(Motor2Callback);

    encodingMotor3.SetPID(4, 0.4, 0);
    encodingMotor3.SetOutputRange(-1000, 1000);
    encodingMotor3.SetSpeed(10);
    encodingMotor3.SetCallback(Motor3Callback);

    encodingMotor4.SetPID(4, 0.4, 0);
    encodingMotor4.SetOutputRange(-1000, 1000);
    encodingMotor4.SetSpeed(10);
    encodingMotor4.SetCallback(Motor4Callback);
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
    char message[64] = {0};
    short speed = (short) __HAL_TIM_GET_COUNTER(&htim2);
    snprintf(message, 64, "speed:%d\r\n", speed);
    HAL_UART_Transmit(&huart1, (uint8_t*)message, strlen(message), 100);

}