/*
 * app_button.h
 *
 *  Created on: Aug 17, 2025
 *      Author: Admin
 */

#ifndef _APP_BUTTON_H_
#define _APP_BUTTON_H_

#include "stdint.h"
typedef struct app_button_t
{
	uint32_t	buttonUpCurrentState;
	uint32_t	buttonDownCurrentState;
	uint32_t	buttonSetCurrentState;
	uint32_t	buttonOnOffCurrentState;
}app_button_t;

void app_button_update();

#endif /* APP_APP_BUTTON_APP_BUTTON_H_ */
