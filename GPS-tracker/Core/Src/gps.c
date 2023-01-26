/*
 * gps.c
 *
 *  Created on: Jan 18, 2023
 *      Author: JSHAN3153
 */

#include <stdio.h>
#include "gps.h"
#include "usart.h"

/*
 * Instance of UART private data handler
 */
GPS_DrvTypeDef GPS;

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
			if ((GPS.fsm_state == fsm_discard) && (value == 0U)){
			    break;
			}

			if (value == 0U){
			    GPS.fsm_next_state = fsm_stop;

			    while (GPS.fsm_state != fsm_stop) {};
			    break;
			}

			GPS.pQueue = teseo_queue_init();
			GPS.wr_msg = NULL;
			GPS.fsm_state = fsm_discard;
			GPS.fsm_next_state = fsm_discard;

			(void)HAL_UART_Receive_IT(&huart6, &GPS.dummy_char, 1);

			break;

	}

	return status;
}
