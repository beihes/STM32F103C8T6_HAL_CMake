/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f1xx_it.c
  * @brief   Interrupt Service Routines.
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
#include "main.h"
#include "stm32f1xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include "usart.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart2_tx;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef htim1;

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M3 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
   while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles DMA1 channel6 global interrupt.
  */
void DMA1_Channel6_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel6_IRQn 0 */

  /* USER CODE END DMA1_Channel6_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart2_rx);
  /* USER CODE BEGIN DMA1_Channel6_IRQn 1 */

  /* USER CODE END DMA1_Channel6_IRQn 1 */
}

/**
  * @brief This function handles DMA1 channel7 global interrupt.
  */
void DMA1_Channel7_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel7_IRQn 0 */

  /* USER CODE END DMA1_Channel7_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart2_tx);
  /* USER CODE BEGIN DMA1_Channel7_IRQn 1 */

  /* USER CODE END DMA1_Channel7_IRQn 1 */
}

/**
  * @brief This function handles TIM1 update interrupt.
  */
void TIM1_UP_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_UP_IRQn 0 */

  /* USER CODE END TIM1_UP_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
  /* USER CODE BEGIN TIM1_UP_IRQn 1 */

  /* USER CODE END TIM1_UP_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */
#ifdef USE_USART1_DMA_RX
    uint16_t temp;
    if (huart1.Instance == USART1) {
        // 如果串口接收完一帧数据，处于空闲状态（IDLE 中断已置位）
        if (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE) != RESET) {
            // 重置 IDLE 位（读取 SR 和 DR 寄存器后即可重置）
            __HAL_UART_CLEAR_IDLEFLAG(&huart1);
            // 停止 DMA 传输，因为不停止的话拷贝数据起来就会容易造成数据缺失
            HAL_UART_DMAStop(&huart1);
            // 读取 CNDTR 寄存器，获取 DMA 中未传输的数据个数
            temp = __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);
            // 获得接收数据的长度（缓冲区总长度 - 未传输的数据个数）
            usart1_dma.recvLength = BUFFERSIZE - temp;
            // 将已接收到的数据进行拷贝，防止数据覆盖造成丢失
            memcpy(usart1_dma.recvBuf, usart1_dma.dmaBuf, usart1_dma.recvLength);
            // 接收完成标志置位
            usart1_dma.recvEndFlag = 1;
            // 因为前面停止了 DMA 传输，现在要重新打开（这个视个人需求而定要不要重新打开）
            while (HAL_UART_Receive_DMA(&huart1, usart1_dma.dmaBuf, BUFFERSIZE) != HAL_OK);
        }
    }
#endif
  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}

/**
  * @brief This function handles USART2 global interrupt.
  */
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */
#ifdef USE_USART2_DMA
    uint16_t temp;
    if (huart2.Instance == USART2) {
        // 如果串口接收完一帧数据，处于空闲状态（IDLE 中断已置位）
        if (__HAL_UART_GET_FLAG(&huart2, UART_FLAG_IDLE) != RESET) {
            // 重置 IDLE 位（读取 SR 和 DR 寄存器后即可重置）
            __HAL_UART_CLEAR_IDLEFLAG(&huart2);
            // 停止 DMA 传输，因为不停止的话拷贝数据起来就会容易造成数据缺失
            HAL_UART_DMAStop(&huart2);
            // 读取 CNDTR 寄存器，获取 DMA 中未传输的数据个数
            temp = __HAL_DMA_GET_COUNTER(&hdma_usart2_rx);
            // 获得接收数据的长度（缓冲区总长度 - 未传输的数据个数）
            usart2_dma.recvLength = BUFFERSIZE - temp;
            // 将已接收到的数据进行拷贝，防止数据覆盖造成丢失
            memcpy(usart2_dma.recvBuf, usart2_dma.dmaBuf, usart2_dma.recvLength);
            if (usart2_dma.recvLength<BUFFERSIZE)
            {
                usart2_dma.recvBuf[usart2_dma.recvLength] = '\0';
            }
            else {
                usart2_dma.recvBuf[BUFFERSIZE - 1] = '\0';
            }
            
            // 接收完成标志置位
            usart2_dma.recvEndFlag = 1;
            // 因为前面停止了 DMA 传输，现在要重新打开（这个视个人需求而定要不要重新打开）
            while (HAL_UART_Receive_DMA(&huart2, usart2_dma.dmaBuf, BUFFERSIZE) != HAL_OK);
        }
    }
#endif
  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */

  /* USER CODE END USART2_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
