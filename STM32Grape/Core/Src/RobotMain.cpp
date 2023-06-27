#include "RobotMain.h"


RDK::PID motor1(RDK::PIDType::Inc, 4, 0.4, 0);
RDK::PID motor2(RDK::PIDType::Inc, 4, 0.4, 0);
RDK::PID motor3(RDK::PIDType::Inc, 4, 0.4, 0);
RDK::PID motor4(RDK::PIDType::Inc, 4, 0.4, 0);

void RobotInit()
{
    motor1.SetOutputRange(-1000, 1000);
    motor1.SetTarget(10);

    motor2.SetOutputRange(-1000, 1000);
    motor2.SetTarget(10);

    motor3.SetOutputRange(-1000, 1000);
    motor3.SetTarget(10);

    motor4.SetOutputRange(-1000, 1000);
    motor4.SetTarget(10);
}

void RobotTick()
{
    short speed = (short) __HAL_TIM_GET_COUNTER(&htim2);
    __HAL_TIM_SET_COUNTER(&htim2, 0);
    motor1.SetInput(speed);
    motor1.Tick();
    int output = motor1.GetOutput();
    if (output > 0) {
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, output);
        HAL_GPIO_WritePin(MOTOR1_DIRECTION_GPIO_Port, MOTOR1_DIRECTION_Pin, GPIO_PIN_RESET);
    } else if (output < 0) {
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 1000 + output);
        HAL_GPIO_WritePin(MOTOR1_DIRECTION_GPIO_Port, MOTOR1_DIRECTION_Pin, GPIO_PIN_SET);
    } else {
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
        HAL_GPIO_WritePin(MOTOR1_DIRECTION_GPIO_Port, MOTOR1_DIRECTION_Pin, GPIO_PIN_RESET);
    }

    speed = (short) __HAL_TIM_GET_COUNTER(&htim3);
    __HAL_TIM_SET_COUNTER(&htim3, 0);
    motor2.SetInput(speed);
    motor2.Tick();
    output = motor2.GetOutput();
    if (output > 0) {
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, output);
        HAL_GPIO_WritePin(MOTOR2_DIRECTION_GPIO_Port, MOTOR2_DIRECTION_Pin, GPIO_PIN_RESET);
    } else if (output < 0) {
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 1000 + output);
        HAL_GPIO_WritePin(MOTOR2_DIRECTION_GPIO_Port, MOTOR2_DIRECTION_Pin, GPIO_PIN_SET);
    } else {
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
        HAL_GPIO_WritePin(MOTOR2_DIRECTION_GPIO_Port, MOTOR2_DIRECTION_Pin, GPIO_PIN_RESET);
    }

    speed = (short) __HAL_TIM_GET_COUNTER(&htim4);
    __HAL_TIM_SET_COUNTER(&htim4, 0);
    motor3.SetInput(speed);
    motor3.Tick();
    output = motor3.GetOutput();
    if (output > 0) {
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, output);
        HAL_GPIO_WritePin(MOTOR3_DIRECTION_GPIO_Port, MOTOR3_DIRECTION_Pin, GPIO_PIN_RESET);
    } else if (output < 0) {
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 1000 + output);
        HAL_GPIO_WritePin(MOTOR3_DIRECTION_GPIO_Port, MOTOR3_DIRECTION_Pin, GPIO_PIN_SET);
    } else {
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
        HAL_GPIO_WritePin(MOTOR3_DIRECTION_GPIO_Port, MOTOR3_DIRECTION_Pin, GPIO_PIN_RESET);
    }

    speed = (short) __HAL_TIM_GET_COUNTER(&htim8);
    __HAL_TIM_SET_COUNTER(&htim8, 0);
    motor4.SetInput(speed);
    motor4.Tick();
    output = motor4.GetOutput();
    if (output > 0) {
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, output);
        HAL_GPIO_WritePin(MOTOR4_DIRECTION_GPIO_Port, MOTOR4_DIRECTION_Pin, GPIO_PIN_RESET);
    } else if (output < 0) {
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 1000 + output);
        HAL_GPIO_WritePin(MOTOR4_DIRECTION_GPIO_Port, MOTOR4_DIRECTION_Pin, GPIO_PIN_SET);
    } else {
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);
        HAL_GPIO_WritePin(MOTOR4_DIRECTION_GPIO_Port, MOTOR4_DIRECTION_Pin, GPIO_PIN_RESET);
    }
}

void RobotTest()
{
    char message[64] = {0};
    short speed = (short) __HAL_TIM_GET_COUNTER(&htim2);
    snprintf(message, 64, "speed:%d\r\n", speed);
    HAL_UART_Transmit(&huart1, (uint8_t*)message, strlen(message), 100);

}