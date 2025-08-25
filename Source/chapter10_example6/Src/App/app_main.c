/*
 * app_main.c
 *
 *  Created on: Aug 2, 2025
 *      Author: Admin
 */
#include "stdint.h"
#include "error_codes.h"
#include "console.h"
#include "bsp_usart.h"
#include "app_water_control.h"
#include "soft_timer.h"
#include "console_dbg.h"



void app_main(void)
{
#ifdef DEBUG_ENABLE
	bsp_uart_console_init();
#endif
	soft_timer_init();
	app_water_control_init();
	while (1)
	{
		app_water_control_update();
	}
}


