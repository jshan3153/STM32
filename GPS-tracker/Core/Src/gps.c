/*
 * gps.c
 *
 *  Created on: Jan 18, 2023
 *      Author: JSHAN3153
 */

#include <stdio.h>
#include "gps.h"
#include "usart.h"

uint32_t GPS_setDrvParam(uint32_t param, uint32_t value)
{
	uint32_t status = 0;

	switch(param)
	{
		case GPS_PWR_CTRL:
			if(value){
				//#define GPS_PWR_ON_Pin GPIO_PIN_12
				//#define GPS_PWR_ON_GPIO_Port GPIOG
				HAL_GPIO_WritePin(GPS_PWR_ON_GPIO_Port, GPS_PWR_ON_Pin, GPIO_PIN_SET);
			}
			else{
				HAL_GPIO_WritePin(GPS_PWR_ON_GPIO_Port, GPS_PWR_ON_Pin, GPIO_PIN_RESET);
			}
			break;

		case GPS_UART_INT_ON:
			HAL_UART_Receive_IT(&huart6, &RxData6, 1);
			break;

	}

	return status;
}
