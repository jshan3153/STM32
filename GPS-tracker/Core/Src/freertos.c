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
#include "event_groups.h"
#include "gnss_parser.h"
#include "gnss1a1_gnss.h"
//#include "NMEA_parser.h"
//#include "gnss_geofence.h"
//#include "gnss_datalog.h"
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
static GNSSParser_Data_t GNSSParser_Data;
/* USER CODE END Variables */
/* Definitions for GPS_Task */
osThreadId_t GPS_TaskHandle;
const osThreadAttr_t GPS_Task_attributes = {
  .name = "GPS_Task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
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
	/* Mutex for GNSS data access */
	static osMutexId gnssDataMutexHandle;
	GNSSParser_Status_t status, check;
	const GNSS1A1_GNSS_Msg_t *gnssMsg;

//	osMutexDef(mutex1);
//	gnssDataMutexHandle = osMutexCreate(osMutex(mutex1));

	printf("\n\rStartGPSTask running\n\r");

	GNSS_PARSER_Init(&GNSSParser_Data);
  /* Infinite loop */
  for(;;)
  {

	gnssMsg = GNSS1A1_GNSS_GetMessage(GNSS1A1_TESEO_LIV3F);

	if(gnssMsg == NULL){
	  continue;
	}
#if 0
	check = GNSS_PARSER_CheckSanity(gnssMsg->buf, gnssMsg->len);

	//    PRINT_OUT("got ");
	//    (check == GNSS_PARSER_OK) ? PRINT_OUT("Good sentence: ") : PRINT_OUT("!!!Bad sentence: ");
	//    PRINT_OUT((char *)gnssMsg->buf);

	if(check != GNSS_PARSER_ERROR){
	  for(int m = 0; m < NMEA_MSGS_NUM; m++){
		osMutexWait(gnssDataMutexHandle, osWaitForever);
		status = GNSS_PARSER_ParseMsg(&GNSSParser_Data, (eNMEAMsg)m, (uint8_t *)gnssMsg->buf);
		osMutexRelease(gnssDataMutexHandle);

		/* Info about FW version. */
		if((status != GNSS_PARSER_ERROR) && ((eNMEAMsg)m == PSTMVER)) {
		  GNSS_DATA_GetPSTMVerInfo(&GNSSParser_Data);
		}

		/* Info about Password generation for A-GNSS. */
		if((status != GNSS_PARSER_ERROR) && ((eNMEAMsg)m == PSTMPASSRTN)) {
		  GNSS_DATA_GetPSTMPassInfo(&GNSSParser_Data);
		}

		/* STAGPS related info for A-GNSS. */
		if((status != GNSS_PARSER_ERROR) && ((eNMEAMsg)m == PSTMAGPSSTATUS)) {
		  GNSS_DATA_GetPSTMAGPSInfo(&GNSSParser_Data);
		}

		/* Confirmation of an updated message list. */
		if((status != GNSS_PARSER_ERROR) && ((eNMEAMsg)m == PSTMSGL)) {
		  GNSS_DATA_GetMsglistAck(&GNSSParser_Data);
		}

		/* Confirmation after saving params. */
		if((status != GNSS_PARSER_ERROR) && ((eNMEAMsg)m == PSTMSAVEPAR)) {
		  GNSS_DATA_GetGNSSAck(&GNSSParser_Data);
		}
	  }
	}
	//    else
	//    {
	//      PRINT_OUT("*****check error!!!!*****\n ");
	//    }

	GNSS1A1_GNSS_ReleaseMessage(GNSS1A1_TESEO_LIV3F, gnssMsg);
#endif
    osDelay(1);
  }
  /* USER CODE END StartGPSTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

