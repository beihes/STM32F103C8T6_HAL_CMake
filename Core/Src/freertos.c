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
#include "adc.h"
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
uint32_t ledLightNum = 0;
AppDevice appDevice;
float Vrms, Irms, P, PF, F, W;
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
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityRealtime,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartLED_Task(void *argument);
void StartWifi_Task(void *argument);

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

  /* USER CODE BEGIN RTOS_QUEUES */
            /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of ledTask */
  ledTaskHandle = osThreadNew(StartLED_Task, NULL, &ledTask_attributes);

  /* creation of wifiTask */
  wifiTaskHandle = osThreadNew(StartWifi_Task, NULL, &wifiTask_attributes);

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
    for (;;) {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
        ledLightNum++;
        osDelay(500);
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
        osDelay(500);
        HAL_RTC_GetTime(&hrtc, &rtcTime, RTC_FORMAT_BIN);
        HAL_RTC_GetDate(&hrtc, &rtcDate, RTC_FORMAT_BIN);
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
void StartWifi_Task(void* argument)
{
    /* USER CODE BEGIN StartWifi_Task */
          /* Infinite loop */
    char midStr[64] = "";
    // char midCmd[32] = "";
    uint16_t length = 0;
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
                        length = sprintf(midStr, "%02d/%02d/%02d%3d%3d:%2d:%2d\r\n", 2000 + rtcDate.Year, rtcDate.Month, rtcDate.Date, rtcDate.WeekDay, rtcTime.Hours, rtcTime.Minutes, rtcTime.Seconds);
                        EspSendData(midStr, length);
                    }
                    else if (strstr(midStr, "[led]") != NULL) {
                        length = sprintf(midStr, "ledlightNum:%ld\r\n", ledLightNum);
                        EspSendData(midStr, length);
                    }
                    else if (strstr(midStr, "[sound]") != NULL) {
                        USART3_Printf("<G>%c%c%c%c", 0xB2, 0xE2, 0xCA, 0xD4);
                    }
                    else if (strstr(midStr, "[key]") != NULL) {
                        switch (midStr[5]) {
                        case '1':
                            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET == (midStr[6] - '0'));
                            length = sprintf(midStr, "key[1]:OK\r\n");
                            EspSendData(midStr, length);
                            break;
                        case '2':
                            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET == (midStr[6] - '0'));
                            length = sprintf(midStr, "key[2]:OK\r\n");
                            EspSendData(midStr, length);
                            break;
                        default:
                            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
                            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
                            length = sprintf(midStr, "key all close\r\n");
                            EspSendData(midStr, length);
                            break;
                        }
                    }
                    else if (strstr(midStr, "[v]") != NULL) {
                        ADC1_GetValue();
                        length = sprintf(midStr, "adc1IN9:%f\r\n", adc1dmaData.data[0]);
                        EspSendData(midStr, length);
                    }
                    else if (strstr(midStr, "[p]") != NULL) {
                        printf(">>GetVal\r\n");
                        osDelay(10);
                        if (usart1_rx.finishFlag == 1) {
                            if (strstr((char*)usart1_rx.rxbuf, "OK") != NULL) {
                                EspSendData((char*)usart1_rx.rxbuf, usart1_rx.rxBufLength);
                            }
                            usart1_rx.finishFlag = 0;
                            usart1_rx.rxBufLength = 0;
                        }
                    }
                }
            }
            usart2_dma.recvEndFlag = 0;
            usart2_dma.recvLength = 0;
        }
#endif
        osDelay(100);
        ADC1_GetValue();
        if (adc1dmaData.data[0] < 3.0) {
            length = sprintf(midStr, "[blackout]\r\n");
            EspSendData(midStr, length);
        }
        printf(">>GetVal\r\n");
        osDelay(10);
        if (usart1_rx.finishFlag == 1) {
            // EspSendData((char*)usart1_rx.rxbuf, usart1_rx.rxBufLength);
            if (strstr((char*)usart1_rx.rxbuf, "OK") != NULL) {
                //  | Vrms:   0.00000V | Irms:   0.00000A | P:   0.0000W | PF: 0.00000 | F:  0.0000Hz | W:   0.0000KW*H |
                // 使用 sscanf 提取字段值
                char* midPData = strstr((char*)usart1_rx.rxbuf, "W |");
                while (midPData[0] != ':') {
                    midPData--;
                }
                if (midPData != NULL) {
                    P= strtof(midPData + 1, NULL);
                    // EspSendData("Power OK\r\n", sizeof("OK\r\n"));
                    // EspSendData((char*)usart1_rx.rxbuf, usart1_rx.rxBufLength);
                    // length = sprintf(midStr, "P:%f\r\n", P);
                    // EspSendData(midStr, length);
                    if (P > 1000.0) {
                        length = sprintf(midStr, "P:%f\r\n", P);
                        EspSendData(midStr, length);
                        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
                        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
                        EspSendData("ALL CLOSE", sizeof("ALL CLOSE"));
                        USART3_Printf("<G>%c%c%c%c%c%c%c%c",
                            0xB9, 0xA6, // 功
                            0xC2, 0xCA, // 率
                            0xB9, 0xFD, // 过
                            0xB8, 0xDF  // 高
                        );
                    }
                }
            }
            usart1_rx.finishFlag = 0;
            usart1_rx.rxBufLength = 0;
        }
    }
    /* USER CODE END StartWifi_Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

