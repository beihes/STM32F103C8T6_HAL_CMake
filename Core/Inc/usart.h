/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
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
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;

extern UART_HandleTypeDef huart2;

extern UART_HandleTypeDef huart3;

/* USER CODE BEGIN Private defines */
#define USE_USART1_NORMAL
#define USE_USART2_NORMAL
// #define USE_USART3_NORMAL
typedef struct __USART_RX
{
    uint8_t rxbuf[128];    // 数据缓冲区
    uint8_t sendBuf[255];   //发送缓冲区
    uint8_t ch;            // 中断接收缓冲区
	bool finishFlag;       // 接收完成标志
	int rxBufLength;        // 缓冲区索引
	UART_HandleTypeDef *huart;    // 串口指针
} stu_usart_rx;
#ifdef USE_USART1_NORMAL
extern stu_usart_rx usart1_rx;
#endif 
#ifdef USE_USART2_NORMAL
extern stu_usart_rx usart2_rx;
#endif 
#ifdef USE_USART3_NORMAL
extern stu_usart_rx usart3_rx;
#endif 
// #define USE_USART1_DMA_RX
// #define USE_USART2_DMA_RX
// #define USE_USART3_DMA_RX
#define BUFFERSIZE 		255				// 缓冲区大小
typedef struct _USART_DMA_
{
    bool 	 recv_end_flag;				// 接收完成标志
    uint8_t  send_buf[BUFFERSIZE];		// 发送缓冲区
    uint8_t  recv_buf[BUFFERSIZE];		// 接收缓冲区
    uint8_t  dma_buf[BUFFERSIZE];		// dma缓冲区
    uint16_t recv_len;					// 接收数据的长度
} stu_usart_DMA;

#ifdef USE_USART1_DMA_RX
extern stu_usart_DMA usart1_dma;
#endif

#ifdef USE_USART3_DMA_RX
extern stu_usart_DMA usart3_dma;
#endif

#ifdef USE_USART3_DMA_RX
extern stu_usart_DMA usart3_dma;
#endif

/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);
void MX_USART3_UART_Init(void);

/* USER CODE BEGIN Prototypes */
#ifdef USE_USART1_DMA_RX
void USART1_DMA_Send(uint8_t* buffer, uint16_t length);
void Debug_printf(const char* format, ...);
#endif

void Esp_Printf(const char* format, ...);

uint8_t EspSendCmdAndCheckRecvData(const char* cmd, const char* recCmd, uint32_t outTime);

 /**
   * @brief  连接电脑
   * @param  
   * @retval 
   */
void Wifi_ConnectComputer();

uint8_t EspSendData(const char* data, uint32_t length);

uint8_t EspOutCIPMODE();
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

