/*
 * app_main.c
 *
 *  Created on: Aug 2, 2025
 *      Author: Admin
 */
#include "stdint.h"
#include "console.h"
void app_main(void)
{
	uint32_t ui32Index = 0;
	while (1)
	{
		console_printf("Loop number in dec: %d  in hex 0x%x\r\n", ui32Index,ui32Index);
		ui32Index ++;
		for (volatile uint32_t i = 0; i< 1000000;i++);
	}
}
