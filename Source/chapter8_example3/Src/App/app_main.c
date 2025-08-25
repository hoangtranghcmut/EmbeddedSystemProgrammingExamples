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
#include "console_dbg.h"
void app_main(void)
{

	bsp_uart_console_init();
	while (1)
	{
		char c;
		while (console_getchar(&c) != ERROR_OK);
		console_printf("received character with ASCII code = %d\r\n", c);
		DBG(DBG_LEVEL_INFO,"received %c \r\n",c);
	}
}
