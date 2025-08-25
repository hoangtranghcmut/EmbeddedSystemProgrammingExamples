/*
 * app_temperature.c
 *
 *  Created on: Aug 15, 2025
 *      Author: Admin
 */


#include "app_temperature.h"
#include "app_signals.h"
#include "app_sys_control.h"

static app_sys_control_fsm_evt_t evt = {0};


/*
 * Ta coi như nhiệt độ đọc được ra khỏi tầm 0-60 độ thì là lỗi
 */
void app_temperature_update(void)
{
	uint16_t ui16Temperature;
	ui16Temperature = bsp_ntc_temperature_conv();

	//Kiểm tra xem nhiệt độ có trong tầm không
	if ((ui16Temperature >= 0) && (ui16Temperature <=60))
	{
		evt.signal = EVT_SYS_CONTROL_TEMPERATURE_UPDATE;
		evt.data.temperature = ui16Temperature;
	}
	else evt.signal = EVT_SYS_CONTROL_TEMPERATURE_ERROR;
	app_sys_control_evt_push(&evt);
}
