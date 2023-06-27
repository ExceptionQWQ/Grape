#include "RobotMain.h"


RDK::PID pid(RDK::PIDType::Inc, 4, 0.4, 0);

void RobotInit()
{
    pid.SetOutputRange(-1000, 1000);
    pid.SetTarget(10);
}

void RobotTick()
{
    short speed = (short) __HAL_TIM_GET_COUNTER(&htim4);
    __HAL_TIM_SET_COUNTER(&htim4, 0);
    pid.SetInput(speed);
    pid.Tick();
    int output = pid.GetOutput();
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
}

void RobotTest()
{
    char message[64] = {0};
    short speed = (short) __HAL_TIM_GET_COUNTER(&htim2);
    snprintf(message, 64, "speed:%d\r\n", speed);
    HAL_UART_Transmit(&huart1, (uint8_t*)message, strlen(message), 100);

}