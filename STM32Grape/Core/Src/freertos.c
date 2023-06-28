/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "message_buffer.h"
#include "robot.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for robotMotion */
osThreadId_t robotMotionHandle;
const osThreadAttr_t robotMotion_attributes = {
  .name = "robotMotion",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for debugUartMutex */
osMutexId_t debugUartMutexHandle;
const osMutexAttr_t debugUartMutex_attributes = {
  .name = "debugUartMutex"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */


int startsWith(const char* str1, const char* str2)
{
    int len1 = strlen(str1), len2 = strlen(str2);
    if (len1 < len2) return 0;
    for (int i = 0; i < len2; ++i) {
        if (str1[i] != str2[i]) return 0;
    }
    return 1;
}

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void RobotMotion(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* creation of debugUartMutex */
  debugUartMutexHandle = osMutexNew(&debugUartMutex_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  messageBufferHandle = xMessageBufferCreate(1024);
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of robotMotion */
  robotMotionHandle = osThreadNew(RobotMotion, NULL, &robotMotion_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(int cnt = 0;;++cnt)
  {
      xSemaphoreTake(debugUartMutexHandle, portMAX_DELAY);
      char buff[128] = {};
      snprintf(buff, 128, "cnt:%d\r\n", cnt);
      HAL_UART_Transmit(&huart1, buff, strlen(buff), 100);
      xSemaphoreGive(debugUartMutexHandle);

    osDelay(1000);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_RobotMotion */
/**
* @brief Function implementing the robotMotion thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_RobotMotion */
void RobotMotion(void *argument)
{
  /* USER CODE BEGIN RobotMotion */
  /* Infinite loop */

    osDelay(1000);


    /* Infinite loop */
    for(;;)
    {
        if (HAL_UART_STATE_READY == HAL_UART_GetState(&huart1)) {
            HAL_UART_Receive_IT(&huart1, robotRecvBuff + robotRecvOffset, 1);
        }
        char message[128] = {0};
        xMessageBufferReceive(messageBufferHandle, message, 128, portMAX_DELAY);

        if (startsWith(message, "[MoveX]")) {
            double speed;
            sscanf(message, "[MoveX]speed=%lf", &speed);
            RobotMoveX(speed);
        } else if (startsWith(message, "[MoveY]")) {
            double speed;
            sscanf(message, "[MoveY]speed=%lf", &speed);
            RobotMoveY(speed);
        } else if (startsWith(message, "[MoveZ]")) {
            double speed;
            sscanf(message, "[MoveZ]speed=%lf", &speed);
            RobotMoveZ(speed);
        } else if (startsWith(message, "[Stop]")) {
            RobotStop();
        }

        osDelay(1);
    }

  /* USER CODE END RobotMotion */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

