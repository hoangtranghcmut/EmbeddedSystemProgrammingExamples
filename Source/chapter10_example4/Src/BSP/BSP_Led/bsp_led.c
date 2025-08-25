/*
 * bsp_led.c
 *
 *  Created on: Aug 5, 2025
 *      Author: Admin
 */

#include "bsp_led.h"
#include "do.h"


static do_t ledError;

void bsp_led_error_init()
{

	doInit_t initErrorStruct = {
			.hGPIOInit = LED_ERROR_PORT,
			.ui32PinNumInit = LED_ERROR_PIN,
			.bStatusInit = false
	};
  do_init(&ledError, &initErrorStruct);

}

void bsp_led_error_on()
{

		do_set(&ledError);

}

void bsp_led_error_off(uint32_t ui32LedNum)
{
	do_reset(&ledError);
}



void bsp_led_error_toggle()
{
	do_toggle(&ledError);
}
