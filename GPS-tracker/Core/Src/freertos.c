/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "gnss_parser.h"
#include "teseo.h"
#include "teseo_io.h"
#include "teseo_queue.h"
#include "gnss_data_if.h"
#include "gps.h"
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
GNSSParser_Data_t GNSSParser_Data;
GNSS_HandleTypeDef pGNSS;
/* USER CODE END Variables */
/* Definitions for GPS_Task */
osThreadId_t GPS_TaskHandle;
const osThreadAttr_t GPS_Task_attributes = {
  .name = "GPS_Task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for gnssDataMutex */
osMutexId_t gnssDataMutexHandle;
const osMutexAttr_t gnssDataMutex_attributes = {
  .name = "gnssDataMutex"
};

osMutexId_t consoleMutexHandle;
const osMutexAttr_t consolMutex_attributes ={
	.name = "contsolWriteMutex"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartGPSTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
//	evtGrpHandle = xEventGroupCreate();

	GPS_TaskHandle = osThreadNew(StartGPSTask, NULL, &GPS_Task_attributes);

  /* USER CODE END Init */
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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

/**
  * @}
  */

/**
  * @}
  */
}

/* USER CODE BEGIN Header_StartGPSTask */
/**
  * @brief  Function implementing the GPS_Task thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartGPSTask */
void StartGPSTask(void *argument)
{
  /* USER CODE BEGIN StartGPSTask */
	GNSSParser_Status_t status, check;
	const GNSS_MsgTypeDef *gnssMsg;

	gnssDataMutexHandle = osMutexNew(&gnssDataMutex_attributes);

	consoleMutexHandle = osMutexNew(&consolMutex_attributes);

	printf("Teseo Consumer Task running\r\n");
	GNSS_PARSER_Init(&GNSSParser_Data);

	for(;;){
	    gnssMsg = teseo_queue_claim_rd_buffer(GPS.pQueue);

	    check = GNSS_PARSER_CheckSanity((uint8_t *)gnssMsg->buf, gnssMsg->len);

#if 0
	    printf("got ");
	    (check == GNSS_PARSER_OK) ? printf("Good sentence: ") : printf("!!!Bad sentence: ");
	    printf((uint8_t *)gnssMsg->buf);
	    printf("\n\r");
#endif

	    if(check != GNSS_PARSER_ERROR){

	      for(int m = 0; m < NMEA_MSGS_NUM; m++) {

#ifndef USE_STM32L0XX_NUCLEO
	    	osMutexAcquire(gnssDataMutexHandle, osWaitForever);
	        status = GNSS_PARSER_ParseMsg(&GNSSParser_Data, (eNMEAMsg)m, (uint8_t *)gnssMsg->buf);
	        osMutexRelease(gnssDataMutexHandle);

//	        if((status != GNSS_PARSER_ERROR) && ((eNMEAMsg)m == PSTMVER)) {
//	          GNSS_DATA_IF_GetPSTMVerInfo(&GNSSParser_Data);
//	        }
	        if((status != GNSS_PARSER_ERROR) && ((eNMEAMsg)m == GPRMC)) {
	        	GNSS_DATA_IF_GetGPRMCInfo(&GNSSParser_Data);
	        }
#else
	        status = GNSS_PARSER_ParseMsg(&GNSSParser_Data, (eNMEAMsg)m, (uint8_t *)gnssMsg->buf);

	        if((status != GNSS_PARSER_ERROR) && ((eNMEAMsg)m == GPGGA)) {
	            GNSS_DATA_IF_GetValidInfo(&GNSSParser_Data);
	        }
#endif /* USE_STM32L0XX_NUCLEO */


#if (configUSE_GEOFENCE == 1)
	        if((status != GNSS_PARSER_ERROR) && ((eNMEAMsg)m == PSTMGEOFENCE)) {
	          GNSS_DATA_IF_GetGeofenceInfo(&pGNSS, &GNSSParser_Data);
	        }
#endif /* configUSE_GEOFENCE */

#if (configUSE_ODOMETER == 1)
	        if((status != GNSS_PARSER_ERROR) && ((eNMEAMsg)m == PSTMODO)) {
	          GNSS_DATA_IF_GetOdometerInfo(&pGNSS, &GNSSParser_Data);
	        }
#endif /* configUSE_ODOMETER */

#if (configUSE_DATALOG == 1)
	        if((status != GNSS_PARSER_ERROR) && ((eNMEAMsg)m == PSTMDATALOG)) {
	          GNSS_DATA_IF_GetDatalogInfo(&pGNSS, &GNSSParser_Data);
	        }
#endif /* configUSE_DATALOG */

#ifndef USE_STM32L0XX_NUCLEO
	        if((status != GNSS_PARSER_ERROR) && ((eNMEAMsg)m == PSTMSGL)) {
	          GNSS_DATA_IF_GetMsglistAck(&pGNSS, &GNSSParser_Data);
	        }

	        if((status != GNSS_PARSER_ERROR) && ((eNMEAMsg)m == PSTMSAVEPAR)) {
	          GNSS_DATA_IF_GetGNSSAck(&pGNSS, &GNSSParser_Data);
	        }
#endif /* USE_STM32L0XX_NUCLEO */
	      }
	    }
	    //Teseo_Release_Buffer(&pGNSS, gnssMsg);
	    teseo_queue_release_rd_buffer(GPS.pQueue, gnssMsg);

	    //osDelay(100);
	}
  /* USER CODE END StartGPSTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

