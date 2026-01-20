/*
 * bsp_led.c
 *
 *  Created on: Aug 5, 2025
 *      Author: Admin
 */

#include "bsp_led.h"
#include "do.h"


static do_t ledGreen = {
		.port = LED_GREEN_PORT,
		.pin  = LED_GREEN_PIN,
		.bStatus =  false
};
static do_t ledBlue= {
		.port = LED_BLUE_PORT,
		.pin  = LED_BLUE_PIN,
		.bStatus =  false
};
static do_t ledRed= {
		.port = LED_RED_PORT,
		.pin  = LED_RED_PIN,
		.bStatus =  false
};

void bsp_led_init()
{
	do_reset(&ledRed);
	do_reset(&ledBlue);
	do_reset(&ledGreen);

}
void bsp_led_on(uint32_t ui32LedNum)
{
	switch (ui32LedNum)
	{
	case LED_GREEN:
		do_set(&ledGreen);
		break;
	case LED_BLUE:
		do_set(&ledBlue);
		break;
	case LED_RED:
		do_set(&ledRed);
		break;
	default:
		break;
	}
}

void bsp_led_off(uint32_t ui32LedNum)
{
	switch (ui32LedNum)
	{
	case LED_GREEN:
		do_reset(&ledGreen);
		break;
	case LED_BLUE:
		do_reset(&ledBlue);
		break;
	case LED_RED:
		do_reset(&ledRed);
		break;
	default:
		break;
	}
}

void bsp_led_toggle(uint32_t ui32LedNum)
{
	switch (ui32LedNum)
	{
	case LED_GREEN:
		do_toggle(&ledGreen);
		break;
	case LED_BLUE:
		do_toggle(&ledBlue);
		break;
	case LED_RED:
		do_toggle(&ledRed);
		break;
	default:
		break;
	}
}

void bsp_led_green_toggle()
{
	do_toggle(&ledGreen);
}
