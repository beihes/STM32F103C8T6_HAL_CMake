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
#include "rtc.h"
#include "usart.h"
#include <string.h>
#include <stdlib.h>
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
RTC_DateTypeDef rtcDate;
RTC_TimeTypeDef rtcTime;
AppDevice appDevice;
/* USER CODE END Variables */
/* Definitions for ledTask */
osThreadId_t ledTaskHandle;
const osThreadAttr_t ledTask_attributes = {
  .name = "ledTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal1,
};
/* Definitions for wifiTask */
osThreadId_t wifiTaskHandle;
const osThreadAttr_t wifiTask_attributes = {
  .name = "wifiTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityRealtime,
};
/* Definitions for soundTask */
osThreadId_t soundTaskHandle;
const osThreadAttr_t soundTask_attributes = {
  .name = "soundTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal1,
};
/* Definitions for myLEDQueue */
osMessageQueueId_t myLEDQueueHandle;
const osMessageQueueAttr_t myLEDQueue_attributes = {
  .name = "myLEDQueue"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartLED_Task(void *argument);
void StartWifi_Task(void *argument);
void StartSound_Task(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
    rtcDate = Get_Build_Date();
    rtcTime = Get_Build_TIME();
    Set_RTC_Start_Time(rtcDate, rtcTime);
#ifdef USE_USART1_NORMAL
    HAL_UART_Receive_IT(usart1_rx.huart, &usart1_rx.ch, 1);    // 打开接收等相关中断
#endif 
#ifdef USE_USART2_NORMAL
    HAL_UART_Receive_IT(usart2_rx.huart, &usart2_rx.ch, 1);    // 打开接收等相关中断
#endif 
#ifdef USE_USART3_NORMAL
    HAL_UART_Receive_IT(usart3_rx.huart, &usart3_rx.ch, 1);    // 打开接收等相关中断
#endif 
    Wifi_ConnectComputer();
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
  myLEDQueueHandle = osMessageQueueNew (16, sizeof(uint16_t), &myLEDQueue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
          /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of ledTask */
  ledTaskHandle = osThreadNew(StartLED_Task, NULL, &ledTask_attributes);

  /* creation of wifiTask */
  wifiTaskHandle = osThreadNew(StartWifi_Task, NULL, &wifiTask_attributes);

  /* creation of soundTask */
  soundTaskHandle = osThreadNew(StartSound_Task, NULL, &soundTask_attributes);

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
void StartLED_Task(void *argument)
{
  /* USER CODE BEGIN StartLED_Task */
        /* Infinite loop */
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
    uint32_t ledLightNum = 0;
    for (;;) {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
        ledLightNum++;
        if (osMessageQueuePut(myLEDQueueHandle, &ledLightNum, 0, 0) == osOK) {
            LOG_D("Message sent to LED queue: %ld", ledLightNum);
        } else {
            LOG_D("Failed to send message to LED queue");
        }
        osDelay(500);
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
        osDelay(500);
    }
  /* USER CODE END StartLED_Task */
}

/* USER CODE BEGIN Header_StartWifi_Task */
/**
* @brief Function implementing the wifiTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartWifi_Task */
void StartWifi_Task(void *argument)
{
  /* USER CODE BEGIN StartWifi_Task */
      /* Infinite loop */
    char midStr[64] = "";
    // char midCmd[32] = "";
    uint16_t length = 0;
    uint32_t ledLightNum = 0;
    for (;;) {
#ifdef USE_USART2_NORMAL
        if (usart2_rx.finishFlag == 1) {
            // LOG_D("%s", usart2_rx.rxbuf);
            // if (usart2_rx.rxbuf[0] == '1') {
            //     EspSendData("测试\r\n", sizeof("测试"));
            // }
            // else if (usart2_rx.rxbuf[0] == '2') {
            //     length = sprintf(midStr, "%02d/%02d/%02d%3d\r\n", 2000 + rtcDate.Year, rtcDate.Month, rtcDate.Date, rtcDate.WeekDay);
            //     EspSendData(midStr, length);
            // }
            Set_stu_usart_rx_NULL(&usart2_rx);
        }
#endif
#ifdef USE_USART2_DMA
        if (usart2_dma.recvEndFlag == 1) {
            if (strstr((char*)usart2_dma.recvBuf, "+IPD,") != NULL) {
                int dataLength = 0;
                char* p = strstr((char*)usart2_dma.recvBuf, "+IPD,");
                if (p != NULL) {
                    p += 5; // Skip "+IPD,"
                    dataLength = atoi(p); // Convert to integer
                }
                while (p[0] != ':') {
                    p++;
                }
                p++; // Skip ':'

                if (dataLength > 0) {
                    // LOG_D("[rx]:\t%s[rx](END)", usart2_dma.recvBuf);
                    memcpy(midStr, p, length = dataLength);
                    midStr[length] = '\0'; // Null-terminate the string
                    LOG_D("[rx]:\t%s[rx](END)", midStr);
                    if (strstr(midStr, "[test]") != NULL) {
                        EspSendData("测试\r\n", sizeof("测试\r\n"));
                    }
                    else if (strstr(midStr, "[time]") != NULL) {
                        HAL_RTC_GetTime(&hrtc, &rtcTime, RTC_FORMAT_BIN);
                        HAL_RTC_GetDate(&hrtc, &rtcDate, RTC_FORMAT_BIN);
                        length = sprintf(midStr, "%02d/%02d/%02d%3d%3d:%2d:%2d\r\n", 2000 + rtcDate.Year, rtcDate.Month, rtcDate.Date, rtcDate.WeekDay, rtcTime.Hours, rtcTime.Minutes, rtcTime.Seconds);
                        EspSendData(midStr, length);
                    }
                    else if (strstr(midStr, "[led]") != NULL)
                    {
                        if (osMessageQueueGet(myLEDQueueHandle, &ledLightNum, NULL, osWaitForever) == osOK) {
                            length = sprintf(midStr, "ledlightNum:%ld\r\n", ledLightNum);
                            EspSendData(midStr, length);
                        }
                    }
                    
                }
            }
            usart2_dma.recvEndFlag = 0;
            usart2_dma.recvLength = 0;
        }
#endif
    }
  /* USER CODE END StartWifi_Task */
}

/* USER CODE BEGIN Header_StartSound_Task */
/**
* @brief Function implementing the soundTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartSound_Task */
void StartSound_Task(void* argument)
{
    /* USER CODE BEGIN StartSound_Task */
    /* Infinite loop */
    
    for (;;) {
        osDelay(5000);
        USART3_Printf("测试!\r\n");
    }
    /* USER CODE END StartSound_Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

