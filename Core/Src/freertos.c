/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "usart.h"
#include <string.h>
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
/* Definitions for ledTask */
osThreadId_t ledTaskHandle;
const osThreadAttr_t ledTask_attributes = {
  .name = "ledTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t)osPriorityNormal,
};
/* Definitions for wlanTask */
osThreadId_t wlanTaskHandle;
const osThreadAttr_t wlanTask_attributes = {
  .name = "wlanTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t)osPriorityNormal2,
};
/* Definitions for myLEDQueue */
osMessageQueueId_t myLEDQueueHandle;
const osMessageQueueAttr_t myLEDQueue_attributes = {
  .name = "myLEDQueue"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartLED_Task(void* argument);
void StartWlan_Task(void* argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void)
{
    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* USER CODE BEGIN RTOS_MUTEX */
        /* add mutexes, ... */
    /* USER CODE END RTOS_MUTEX */

    /* USER CODE BEGIN RTOS_SEMAPHORES */
        /* add semaphores, ... */
    /* USER CODE END RTOS_SEMAPHORES */

    /* USER CODE BEGIN RTOS_TIMERS */
        /* start timers, add new ones, ... */
    /* USER CODE END RTOS_TIMERS */

    /* Create the queue(s) */
    /* creation of myLEDQueue */
    myLEDQueueHandle = osMessageQueueNew(16, sizeof(uint16_t), &myLEDQueue_attributes);

    /* USER CODE BEGIN RTOS_QUEUES */
        /* add queues, ... */
    /* USER CODE END RTOS_QUEUES */

    /* Create the thread(s) */
    /* creation of ledTask */
    ledTaskHandle = osThreadNew(StartLED_Task, NULL, &ledTask_attributes);

    /* creation of wlanTask */
    wlanTaskHandle = osThreadNew(StartWlan_Task, NULL, &wlanTask_attributes);

    /* USER CODE BEGIN RTOS_THREADS */
        /* add threads, ... */
    /* USER CODE END RTOS_THREADS */

    /* USER CODE BEGIN RTOS_EVENTS */
        /* add events, ... */
    /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartLED_Task */
/**
* @brief Function implementing the ledTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLED_Task */
void StartLED_Task(void* argument)
{
    /* USER CODE BEGIN StartLED_Task */
      /* Infinite loop */
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
    for (;;) {
        // HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
        osDelay(500);
        // HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
        osDelay(500);
        LOG_D("测试%d\r\n", 1);
    }
    /* USER CODE END StartLED_Task */
}

/* USER CODE BEGIN Header_StartWlan_Task */
/**
* @brief Function implementing the wlanTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartWlan_Task */
void StartWlan_Task(void* argument)
{
    /* USER CODE BEGIN StartWlan_Task */
        /* Infinite loop */
    for (;;) {
        osDelay(1);
    }
    /* USER CODE END StartWlan_Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

