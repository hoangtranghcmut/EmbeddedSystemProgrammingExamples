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
#include "console_dbg.h"
void app_main(void)
{

	bsp_uart_console_init();
	bsp_led_init();
	while (1)
	{
		char c;
		while (console_getchar(&c) != ERROR_OK);
		if (c == 'O') bsp_led_on(LED_GREEN);
		else if (c == 'F') bsp_led_off(LED_GREEN);;
		DBG(DBG_LEVEL_INFO,"received %c \r\n",c);
	}
}
