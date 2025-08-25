/*
 * bsp_led.c
 *
 *  Created on: Aug 5, 2025
 *      Author: Admin
 */

#include "bsp_led.h"
#include "do.h"

//static do_t ledGreen = {
//		.hGPIO = LED_GREEN_PORT,
//		.ui32PinMask = 1 << LED_GREEN_PIN,
//		.bStatus = false
//};

static do_t ledGreen;
static do_t ledBlue;
static do_t ledRed;

void bsp_led_init()
{
	doInit_t initLedGStruct = {
			.hGPIOInit = LED_GREEN_PORT,
			.ui32PinNumInit = LED_GREEN_PIN,
			.bStatusInit = false
	};
	doInit_t initLedBStruct = {
			.hGPIOInit = LED_BLUE_PORT,
			.ui32PinNumInit = LED_BLUE_PIN,
			.bStatusInit = false
	};
	doInit_t initLedRStruct = {
			.hGPIOInit = LED_RED_PORT,
			.ui32PinNumInit = LED_RED_PIN,
			.bStatusInit = false
	};
  do_init(&ledGreen, &initLedGStruct);
  do_init(&ledBlue, &initLedBStruct);
  do_init(&ledRed, &initLedRStruct);

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
