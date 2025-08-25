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
const DS3234_Time_t rtc1TimeInit = {
		.seconds = 0,
		.minutes = 1,
		.hours = 2,
		.day = 3,
		.date = 4,
		.month = 5,
		.year = 25,
		.is_pm = 0
};

const DS3234_Time_t rtc2TimeInit = {
		.seconds = 6,
		.minutes = 7,
		.hours = 8,
		.day = 9,
		.date = 10,
		.month = 11,
		.year = 26,
		.is_pm = 1
};

DS3234_Time_t rtc1Time = {
		0
};





void app_main(void)
{

	bsp_uart_console_init();
	bsp_led_init();
	bsp_rtc_init();


	bsp_rtc1_set_time((DS3234_Time_t *)&rtc1TimeInit);
	bsp_rtc2_set_time((DS3234_Time_t *)&rtc2TimeInit);
	while (1)
	{
		bsp_rtc1_get_time(&rtc1Time);
		console_printf("RTC1 Time h: %d m: %d s %d \r\n",rtc1Time.hours,rtc1Time.minutes,rtc1Time.seconds);

		for (uint32_t i = 0; i<500000; i++);
	}
}


