/*
 * bsp_button.c
 *
 *  Created on: Aug 14, 2025
 *      Author: Admin
 */
#include "board.h"
#include "bsp_button.h"
#include "stm32f4xx_ll_gpio.h"

uint32_t	bsp_button_up_status()
{
	return LL_GPIO_IsInputPinSet(BUTTON_UP_Port, BUTTON_UP_Pin) ? BUTTON_RELEASE:BUTTON_PRESSED;
}
uint32_t	bsp_button_down_status()
{
	return LL_GPIO_IsInputPinSet(BUTTON_DOWN_Port, BUTTON_DOWN_Pin) ? BUTTON_RELEASE:BUTTON_PRESSED;

}
uint32_t	bsp_button_set_status()
{
	return LL_GPIO_IsInputPinSet(BUTTON_SET_Port, BUTTON_SET_Pin) ? BUTTON_RELEASE:BUTTON_PRESSED;
}
uint32_t	bsp_button_onoff_status()
{
	return LL_GPIO_IsInputPinSet(BUTTON_ONOFF_Port, BUTTON_ONOFF_Pin) ? BUTTON_RELEASE:BUTTON_PRESSED;

}
