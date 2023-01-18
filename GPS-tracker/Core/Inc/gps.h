/*
 * gps.h
 *
 *  Created on: Jan 18, 2023
 *      Author: JSHAN3153
 */

#ifndef INC_GPS_H_
#define INC_GPS_H_

typedef enum {
	GPS_PWR_CTRL,
	GPS_UART_INT_ON
}GPS_PARAM_ENUM;

uint32_t GPS_setDrvParam(uint32_t param, uint32_t value);

#endif /* INC_GPS_H_ */
