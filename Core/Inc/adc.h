/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    adc.h
  * @brief   This file contains all the function prototypes for
  *          the adc.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ADC_H__
#define __ADC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern ADC_HandleTypeDef hadc1;

/* USER CODE BEGIN Private defines */
#define TS_CAL1 ((uint16_t *)0x1FFFF7B8)
#define TS_CAL2 ((uint16_t *)0x1FFFF7C2)
#define VREFINT_CAL ((uint16_t *)0x1FFFF7BA)
    #define ADC1_DMA_LENGTH 1 //ADC1的DMA长度
    typedef struct ADC1DMAData
    {
        uint16_t ADC_Value[ADC1_DMA_LENGTH]; //存储ADC值
        float data[ADC1_DMA_LENGTH];              //存储电压值
    }ADC1DMAData;
    extern ADC1DMAData adc1dmaData;
/* USER CODE END Private defines */

void MX_ADC1_Init(void);

/* USER CODE BEGIN Prototypes */
    void ADC1_GetValue();
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __ADC_H__ */

