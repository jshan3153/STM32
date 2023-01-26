/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
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
#include "usart.h"

/* USER CODE BEGIN 0 */
#include "gps.h"
/* USER CODE END 0 */

UART_HandleTypeDef huart2;
UART_HandleTypeDef huart6;

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
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}
/* USART6 init function */

void MX_USART6_UART_Init(void)
{

  /* USER CODE BEGIN USART6_Init 0 */

  /* USER CODE END USART6_Init 0 */

  /* USER CODE BEGIN USART6_Init 1 */

  /* USER CODE END USART6_Init 1 */
  huart6.Instance = USART6;
  huart6.Init.BaudRate = 9600;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART6_Init 2 */

  /* USER CODE END USART6_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART2)
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
    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN USART2_MspInit 1 */

  /* USER CODE END USART2_MspInit 1 */
  }
  else if(uartHandle->Instance==USART6)
  {
  /* USER CODE BEGIN USART6_MspInit 0 */

  /* USER CODE END USART6_MspInit 0 */
    /* USART6 clock enable */
    __HAL_RCC_USART6_CLK_ENABLE();

    __HAL_RCC_GPIOG_CLK_ENABLE();
    /**USART6 GPIO Configuration
    PG9     ------> USART6_RX
    PG14     ------> USART6_TX
    */
    GPIO_InitStruct.Pin = GPS_RXD_3V3_Pin|GPS_TXD_3V3_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF8_USART6;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    /* USART6 interrupt Init */
    HAL_NVIC_SetPriority(USART6_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(USART6_IRQn);
  /* USER CODE BEGIN USART6_MspInit 1 */

  /* USER CODE END USART6_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART2)
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

  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART6)
  {
  /* USER CODE BEGIN USART6_MspDeInit 0 */

  /* USER CODE END USART6_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART6_CLK_DISABLE();

    /**USART6 GPIO Configuration
    PG9     ------> USART6_RX
    PG14     ------> USART6_TX
    */
    HAL_GPIO_DeInit(GPIOG, GPS_RXD_3V3_Pin|GPS_TXD_3V3_Pin);

    /* USART6 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART6_IRQn);
  /* USER CODE BEGIN USART6_MspDeInit 1 */

  /* USER CODE END USART6_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
/**
  * @brief  Rx Transfer completed callbacks.
  * @param  huart  Pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
	if(huart->Instance == USART6){

//		Teseo_IO_DataTypeDef *teseo_io_data = (Teseo_IO_DataTypeDef *)(GPS.pGNSS->pData);
//
//		if (huart != teseo_io_data->huart)
//		{
//		return;
//		}

		GPS.fsm_restart = 1;

		while(GPS.fsm_restart == 1)
		{

			GPS.fsm_state = GPS.fsm_next_state;

			switch (GPS.fsm_state)
			{

			case fsm_discard:
			  GPS.fsm_restart = 0;
			  GPS.fsm_next_state = fsm_discard;

			  if (GPS.dummy_char != (uint8_t)'$')
			  {
				//Console_Debug((uint8_t *)".");
				(void)HAL_UART_Receive_IT(&huart6, &GPS.dummy_char, 1);
				break;
			  }

			  if (GPS.wr_msg == NULL)
			  {
				GPS.wr_msg = teseo_queue_claim_wr_buffer(GPS.pQueue);
			  }

			  if (GPS.wr_msg == NULL)
			  {
				//Console_Debug((uint8_t *)".");
				(void)HAL_UART_Receive_IT(&huart6, &GPS.dummy_char, 1);
				break;
			  }
			  //Console_Debug((uint8_t *)"S");

			  /* save '$' */
			  GPS.wr_msg->buf[GPS.wr_msg->len] = GPS.dummy_char;
			  GPS.wr_msg->len++;
			  GPS.fsm_next_state = fsm_synch ;
			  (void)HAL_UART_Receive_IT(&huart6,(uint8_t *)&GPS.wr_msg->buf[GPS.wr_msg->len], 1);
			   break;

			case fsm_synch:
			  GPS.fsm_restart = 0;

			  if (GPS.wr_msg->buf[GPS.wr_msg->len] == (uint8_t)'$')
			  {
				GPS.dummy_char = (uint8_t)'$';
				GPS.wr_msg->buf[GPS.wr_msg->len] = (uint8_t)'\0';
				teseo_queue_release_wr_buffer(GPS.pQueue, GPS.wr_msg);
				GPS.wr_msg = NULL;
				GPS.fsm_next_state = fsm_discard ;
				/* check if we can resynch the new sentence */
				GPS.fsm_restart = 1;
				break;
			  }

			  //Console_Debug((uint8_t *)"+");
			  GPS.wr_msg->len++;
			#if 0
			  if (GPS.wr_msg->len == (uint32_t)MAX_MSG_BUF)
			  {
				Console_Debug("MESSAGE TOO LONG\n\r");
				/* it seems we lost some char and the sentence is too much long...
				* reset the msg->len and discand all teh buffer and wait a new '$' sentence
				*/
				GPS.fsm_next_state = fsm_discard;
				GPS.wr_msg->len = 0;
				GPS.fsm_restart = 1;
				break;
			  }
			#endif
			  GPS.fsm_next_state = fsm_synch;
			  (void)HAL_UART_Receive_IT(&huart6,(uint8_t *)&GPS.wr_msg->buf[GPS.wr_msg->len],1);
			  break;

			case fsm_stop:
			default:
			  GPS.fsm_restart = 0;
			  break;
			}
		}

	}
	/* NOTE: This function should not be modified, when the callback is needed,
           the HAL_UART_RxCpltCallback could be implemented in the user file
   */
}


/* USER CODE END 1 */
