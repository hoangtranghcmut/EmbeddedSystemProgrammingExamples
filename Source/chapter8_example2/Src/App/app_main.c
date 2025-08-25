/*
 * app_main.c
 *
 *  Created on: Aug 2, 2025
 *      Author: Admin
 */
#include "stdint.h"
#include "console.h"
#include "error_codes.h"
void app_main(void)
{

	while (1)
	{
		char c;
		while (console_getchar(&c) != ERROR_OK);

		console_printf("received character with ASCII code = %d\r\n", c);

	}
}
