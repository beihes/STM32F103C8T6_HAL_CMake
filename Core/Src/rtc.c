/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    rtc.c
  * @brief   This file provides code for the configuration
  *          of the RTC instances.
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
#include "rtc.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

RTC_HandleTypeDef hrtc;

/* RTC init function */
void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef DateToUpdate = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_NONE;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 0x0;
  sTime.Minutes = 0x0;
  sTime.Seconds = 0x0;

  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  DateToUpdate.WeekDay = RTC_WEEKDAY_THURSDAY;
  DateToUpdate.Month = RTC_MONTH_MAY;
  DateToUpdate.Date = 0x1;
  DateToUpdate.Year = 0x19;

  if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

void HAL_RTC_MspInit(RTC_HandleTypeDef* rtcHandle)
{

  if(rtcHandle->Instance==RTC)
  {
  /* USER CODE BEGIN RTC_MspInit 0 */

  /* USER CODE END RTC_MspInit 0 */
    HAL_PWR_EnableBkUpAccess();
    /* Enable BKP CLK enable for backup registers */
    __HAL_RCC_BKP_CLK_ENABLE();
    /* RTC clock enable */
    __HAL_RCC_RTC_ENABLE();
  /* USER CODE BEGIN RTC_MspInit 1 */

  /* USER CODE END RTC_MspInit 1 */
  }
}

void HAL_RTC_MspDeInit(RTC_HandleTypeDef* rtcHandle)
{

  if(rtcHandle->Instance==RTC)
  {
  /* USER CODE BEGIN RTC_MspDeInit 0 */

  /* USER CODE END RTC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_RTC_DISABLE();
  /* USER CODE BEGIN RTC_MspDeInit 1 */

  /* USER CODE END RTC_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
// 把字符串月份转成数字
int Get_Month_Number(const char *monthStr) {
    static const char *months[] = {
        "Jan","Feb","Mar","Apr","May","Jun",
        "Jul","Aug","Sep","Oct","Nov","Dec"
    };
    for (int i = 0; i < 12; i++) {
        if (strncmp(monthStr, months[i], 3) == 0) {
            return i; // 0-based for struct tm
        }
    }
    return -1;
}

int Get_WeekDay(int y, int m, int d)
{
    if (m < 3) { m += 12; y -= 1; }
    return (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7 + 1;
}

RTC_DateTypeDef Get_Build_Date()
{
    RTC_DateTypeDef midDate = { 0 };
    int year, day;
    char monthStr[4];
    // 解析 __DATE__
    sscanf(BUILD_DATE, "%3s %d %d", monthStr, &day, &year);
    midDate.Year = year % 100;
    midDate.Month = Get_Month_Number(monthStr) + 1;
    midDate.Date = day;
    midDate.WeekDay = Get_WeekDay(midDate.Year, midDate.Month, midDate.Date);
    return midDate;
}

// 解析构建时间
RTC_TimeTypeDef Get_Build_TIME()
{
    RTC_TimeTypeDef midTime = {0};
    int hour, min, sec;
    // 解析 __TIME__
    sscanf(BUILD_TIME, "%d:%d:%d", &hour, &min, &sec);
    midTime.Hours = hour;
    midTime.Minutes  = min;
    midTime.Seconds = sec;
    return midTime;
}

void Set_RTC_Start_Time(RTC_DateTypeDef midDate, RTC_TimeTypeDef midTime)
{
    HAL_RTC_SetTime(&hrtc, &midTime, RTC_FORMAT_BIN);
    HAL_RTC_SetDate(&hrtc, &midDate, RTC_FORMAT_BIN);
}
/* USER CODE END 1 */
