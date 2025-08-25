/*
 * app_temperature.h
 *
 *  Created on: Aug 15, 2025
 *      Author: Admin
 */

#ifndef APP_TEMPERATURE_H_
#define APP_TEMPERATURE_H_

#include "bsp_ntc.h"

typedef struct app_temperature_t
{
	int32_t temperature;
}app_temperature_t;

void app_temperature_update(void);

#endif /* APP_APP_TEMPERATURE_APP_TEMPERATURE_H_ */
