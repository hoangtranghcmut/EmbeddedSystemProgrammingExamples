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
#include "bsp_led.h"
#include "bsp_rtc.h"
#include "ds3234.h"
#include "console_dbg.h"
DS3234_Time_t time = {
		.seconds = 0,
		.minutes = 1,
		.hours = 2,
		.day = 3,
		.date = 4,
		.month = 5,
		.year = 25,
		.is_pm = 0
};
void app_main(void)
{

	bsp_uart_console_init();
	bsp_led_init();
	bsp_rtc_init();

	bsp_rtc_set_time((DS3234_Time_t *)&time);
	while (1)
	{
		bsp_rtc_get_time(&time);
		console_printf("h: %d m: %d s %d \r\n",time.hours,time.minutes,time.seconds);
		for (uint32_t i = 0; i<500000; i++);
	}
}


