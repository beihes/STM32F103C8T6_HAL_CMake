/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
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
#include "usart.h"

/* USER CODE BEGIN 0 */
#ifdef USE_USART1_NORMAL
stu_usart_rx usart1_rx;
#endif 
#ifdef USE_USART2_NORMAL
stu_usart_rx usart2_rx;
#endif 
#ifdef USE_USART3_NORMAL
stu_usart_rx usart3_rx;
#endif 
#ifdef USE_USART1_DMA_RX
stu_usart_DMA usart1_dma;
#endif

#ifdef USE_USART3_DMA_RX
stu_usart_DMA usart3_dma;
#endif

#ifdef USE_USART3_DMA_RX
stu_usart_DMA usart3_dma;
#endif
/* USER CODE END 0 */

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

    /* USER CODE BEGIN USART1_Init 0 */

    /* USER CODE END USART1_Init 0 */

    /* USER CODE BEGIN USART1_Init 1 */

    /* USER CODE END USART1_Init 1 */
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart1) != HAL_OK) {
        Error_Handler();
    }
    /* USER CODE BEGIN USART1_Init 2 */
    #ifdef USE_USART1_NORMAL
    usart1_rx.huart = &huart1;
    usart1_rx.finishFlag = false;
    usart1_rx.ch = 0;
    usart1_rx.rxBufLength = 0;
#endif 
#ifdef USE_USART1_DMA_RX
    // 开启空闲中断
    __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
    // 打开DMA接收中断
    HAL_UART_Receive_DMA(&huart1, usart1_dma.dma_buf, BUFFERSIZE);
#endif
    /* USER CODE END USART1_Init 2 */

}
/* USART2 init function */

void MX_USART2_UART_Init(void)
{

    /* USER CODE BEGIN USART2_Init 0 */

    /* USER CODE END USART2_Init 0 */

    /* USER CODE BEGIN USART2_Init 1 */

    /* USER CODE END USART2_Init 1 */
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart2) != HAL_OK) {
        Error_Handler();
    }
    /* USER CODE BEGIN USART2_Init 2 */
#ifdef USE_USART2_NORMAL
    usart2_rx.huart = &huart2;
    usart2_rx.finishFlag = false;
    usart2_rx.ch = 0;
    usart2_rx.rxBufLength = 0;
#endif 
#ifdef USE_USART2_DMA_RX
    // 开启空闲中断
    __HAL_UART_ENABLE_IT(&huart2, UART_IT_IDLE);
    // 打开DMA接收中断
    HAL_UART_Receive_DMA(&huart2, usart2_dma.dma_buf, BUFFERSIZE);
#endif
    /* USER CODE END USART2_Init 2 */

}
/* USART3 init function */

void MX_USART3_UART_Init(void)
{

    /* USER CODE BEGIN USART3_Init 0 */

    /* USER CODE END USART3_Init 0 */

    /* USER CODE BEGIN USART3_Init 1 */

    /* USER CODE END USART3_Init 1 */
    huart3.Instance = USART3;
    huart3.Init.BaudRate = 115200;
    huart3.Init.WordLength = UART_WORDLENGTH_8B;
    huart3.Init.StopBits = UART_STOPBITS_1;
    huart3.Init.Parity = UART_PARITY_NONE;
    huart3.Init.Mode = UART_MODE_TX_RX;
    huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart3.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart3) != HAL_OK) {
        Error_Handler();
    }
    /* USER CODE BEGIN USART3_Init 2 */
#ifdef USE_USART3_NORMAL
    usart3_rx.huart = &huart3;
    usart3_rx.finishFlag = false;
    usart3_rx.ch = 0;
    usart3_rx.rxBufLength = 0;
#endif 
#ifdef USE_USART3_DMA_RX
    // 开启空闲中断
    __HAL_UART_ENABLE_IT(&huart3, UART_IT_IDLE);
    // 打开DMA接收中断
    HAL_UART_Receive_DMA(&huart3, usart3_dma.dma_buf, BUFFERSIZE);
#endif
    /* USER CODE END USART3_Init 2 */
}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */
    /* USART2 clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART2 interrupt Init */
    HAL_NVIC_SetPriority(USART2_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspInit 1 */

  /* USER CODE END USART2_MspInit 1 */
  }
  else if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspInit 0 */

  /* USER CODE END USART3_MspInit 0 */
    /* USART3 clock enable */
    __HAL_RCC_USART3_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**USART3 GPIO Configuration
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN USART3_MspInit 1 */

  /* USER CODE END USART3_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();

    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);

    /* USART2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspDeInit 0 */

  /* USER CODE END USART3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART3_CLK_DISABLE();

    /**USART3 GPIO Configuration
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10|GPIO_PIN_11);

  /* USER CODE BEGIN USART3_MspDeInit 1 */

  /* USER CODE END USART3_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
int __io_putchar(int ch)
{
    HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
    return ch;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
    	usart1_rx.rxbuf[usart1_rx.rxBufLength++] = usart1_rx.ch;
 
        if(usart1_rx.rxbuf[usart1_rx.rxBufLength - 1] == '\n')    // 接收完毕标志判断
        {
        	usart1_rx.finishFlag = true;
        }
        HAL_UART_Receive_IT(usart1_rx.huart, &usart1_rx.ch, 1);    // 接收成功后还要重新打开中断
    }
    else if (huart->Instance == USART2)
    {
        usart2_rx.rxbuf[usart2_rx.rxBufLength++] = usart2_rx.ch;
 
        if(usart2_rx.rxbuf[usart2_rx.rxBufLength - 1] == '\n')    // 接收完毕标志判断
        {
        	usart2_rx.finishFlag = true;
        }
        HAL_UART_Receive_IT(usart2_rx.huart, &usart2_rx.ch, 1);    // 接收成功后还要重新打开中断
    }
}

#ifdef USE_USART1_DMA
void USART1_DMA_Send(uint8_t *buffer, uint16_t length)
{
    //等待DMA发送通道处于准备状态
	while(HAL_DMA_GetState(&hdma_usart1_tx) != HAL_DMA_STATE_READY);
 
    //关闭DMA
    //__HAL_DMA_DISABLE(&hdma_usart1_tx);
 
    //发送数据
    HAL_UART_Transmit_DMA(&huart1, buffer, length);
}
 
// 重写printf函数
void Debug_printf(const char *format, ...)
{
	uint32_t length = 0;
	va_list args;
 
	va_start(args, format);
	length = vsnprintf((char*)usart1_dma.send_buf, sizeof(usart1_dma.send_buf), (char*)format, args);
	USART1_DMA_Send(usart1_dma.send_buf, length);
}
#endif

void Esp_Printf(const char* format, ...)
{
    uint32_t length = 0;
    va_list args;

    va_start(args, format);
#ifdef USE_USART2_NORMAL
    length = vsnprintf((char*)usart2_rx.sendBuf, sizeof(usart2_rx.sendBuf), (char*)format, args);
    LOG_D("发送：%s", usart2_rx.sendBuf);
    HAL_UART_Transmit_IT(usart2_rx.huart, (uint8_t*)&usart2_rx.sendBuf, length);
#endif
#ifdef USE_USART1_DMA
    length = vsnprintf((char*)usart1_dma.send_buf, sizeof(usart1_dma.send_buf), (char*)format, args);
    USART1_DMA_Send(usart1_dma.send_buf, length);
#endif
}

void Set_stu_usart_rx_NULL(stu_usart_rx* data)
{
    data->finishFlag = 0;
    data->rxBufLength = 0;
    memset(data->rxbuf, 0, sizeof(data->rxbuf));
}

uint8_t EspSendCmdAndCheckRecvData(const char* cmd, const char* recCmd, uint32_t outTime)
{
    uint8_t midData = 0;
    Esp_Printf("%s", cmd);
    while (outTime) {
        if (usart2_rx.finishFlag == 1) {
            LOG_D("接收：%s", usart2_rx.rxbuf);
            if (strstr((char*)usart2_rx.rxbuf, recCmd) != NULL) {
                midData = 1;
                Set_stu_usart_rx_NULL(&usart2_rx);
                break;
            }
            Set_stu_usart_rx_NULL(&usart2_rx);
        }
        HAL_Delay(1);
        outTime--;
    }
    return midData;
}

 /**
   * @brief  连接电脑
   * @param  
   * @retval 
   */
void Wifi_ConnectComputer()
{
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
    if (EspSendCmdAndCheckRecvData("AT+RST\r\n", "ready", 10000) == 1)
    {
    }
    
    if (EspSendCmdAndCheckRecvData("AT\r\n", "OK", 1000) == 1) {
        if (EspSendCmdAndCheckRecvData("AT+CWMODE=1\r\n", "OK", 1000) == 1) {
            if (EspSendCmdAndCheckRecvData("AT+CWJAP=\"TP-LINK_0436\",\"436436436\"\r\n", "OK", 100000) == 1) {
                if (EspSendCmdAndCheckRecvData("AT+CIPSTART=\"TCP\",\"192.168.1.107\",7788\r\n", "OK", 10000) == 1)
                {
                    EspSendCmdAndCheckRecvData("AT+CIPMODE=1\r\n","OK",1000);//开启透传
                }
            }
        }
    }
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
}

uint8_t EspSendData(const char* data, uint32_t length)
{
    uint8_t midSuccess = 0;
    char midStr[32] = "";
    sprintf(midStr, "AT+CIPSEND=%ld\r\n", length);
    if (EspSendCmdAndCheckRecvData(midStr, ">", 1000) == 1) {
        Esp_Printf("%s", data);
        Set_stu_usart_rx_NULL(&usart2_rx);
    }
    return midSuccess;
}

uint8_t EspOutCIPMODE()
{
    return EspSendCmdAndCheckRecvData("+++", "OK", 1000);
}
/* USER CODE END 1 */
