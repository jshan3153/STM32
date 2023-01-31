/*
 * gps.h
 *
 *  Created on: Jan 18, 2023
 *      Author: JSHAN3153
 */

#ifndef INC_GPS_H_
#define INC_GPS_H_

#include "teseo.h"
#include "teseo_queue.h"

typedef enum {
	GPS_PWR_CTRL,
	GPS_UART_INT_ON
}GPS_PARAM_ENUM;

/*
 * Enumeration structure that contains the UART FSM states
 */
typedef enum
{
  fsm_discard,
  fsm_synch,
  fsm_stop
} Teseo_UART_FsmTypeDef;

/*
 * UART private data handler
 */
typedef struct
{
  volatile Teseo_UART_FsmTypeDef fsm_state;
  volatile Teseo_UART_FsmTypeDef fsm_next_state;
  uint8_t dummy_char;
  GNSS_MsgTypeDef *wr_msg;
  volatile int8_t fsm_restart;

  //GNSS_HandleTypeDef *pGNSS;

  Teseo_QueueTypeDef *pQueue;
}GPS_DrvTypeDef;

extern GPS_DrvTypeDef GPS;

uint32_t GPS_setDrvParam(uint32_t param, uint32_t value);

#endif /* INC_GPS_H_ */
