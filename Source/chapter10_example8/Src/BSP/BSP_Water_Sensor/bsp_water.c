/*
 * bsp_water_sensor.c
 *
 *  Created on: Aug 8, 2025
 *      Author: Admin
 */

#include <bsp_water.h>
#include "di.h"
#include "do.h"
#include "board.h"

static di_t waterUpperSensor = {WATER_LOWER_SENSOR_GPIO_PORT,1 << WATER_UPPER_SENSOR_PIN};
static di_t waterLowerSensor = {WATER_UPPER_SENSOR_GPIO_PORT,1 << WATER_LOWER_SENSOR_PIN};
static di_t resumeButton = 		{RESUME_BUTTON_GPIO_PORT,1 << RESUME_BUTTON_PIN};

static do_t	errorLed  = {
		.hGPIO = WATER_ERROR_LED_GPIO_PORT,
		.ui32PinMask = 1 << WATER_ERROR_LED_PIN,
		.bStatus = false
};
static do_t	motorControl  = {
		.hGPIO = WATER_MOTOR_CONTROL_GPIO_PORT,
		.ui32PinMask = 1 << WATER_MOTOR_CONTROL_PIN,
		.bStatus = false
};


void bsp_water_init()
{
	doInit_t init = {
			.hGPIOInit = WATER_ERROR_LED_GPIO_PORT,
			.ui32PinNumInit = WATER_ERROR_LED_PIN,
			.bStatusInit = false
	};
	do_init(&errorLed, &init);

	init.ui32PinNumInit = WATER_MOTOR_CONTROL_PIN;
	init.hGPIOInit = WATER_MOTOR_CONTROL_GPIO_PORT;

	do_init(&motorControl, &init);
}

uint32_t bsp_water_upper_sensor_status(void)
{
	if (di_status(&waterUpperSensor) == DI_RESET) return WATER_OVER;
	else return WATER_UNDER;
}
uint32_t bsp_water_lower_sensor_status(void)
{
	if (di_status(&waterLowerSensor) == DI_RESET) return WATER_OVER;
	else return WATER_UNDER;
}

uint32_t bsp_resume_button_status(void)
{
	if (di_status(&resumeButton) == DI_RESET) return BUTTON_PRESSED;
	else return BUTTON_RELEASE;
}

void bsp_water_error_led_on()
{
	do_set(&errorLed);
}
void bsp_water_error_led_off()
{
	do_reset(&errorLed);
}

void bsp_water_motor_on()
{
	do_set(&motorControl);
}
void bsp_water_motor_off()
{
	do_reset(&motorControl);
}
