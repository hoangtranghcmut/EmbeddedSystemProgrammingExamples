/*
 * bsp_led7seg.c
 *
 *  Created on: Aug 14, 2025
 *      Author: Admin
 */

#include "board.h"
#include "bsp_led7seg.h"
#include "stm32f4xx_ll_gpio.h"

void bsp_led7seg_display(uint16_t ui16LedIdx, uint8_t ui8LedCode)
{
//	bsp_led7seg_turn_off_all();
	LED7SEG_PORT->ODR = (LED7SEG_PORT->ODR & 0xFF00) | (ui8LedCode & 0x00FF);
	bsp_led7seg_turn_on_single(ui16LedIdx);
}

void bsp_led7seg_turn_off_all()
{
	LL_GPIO_ResetOutputPin(LED7SEG_PORT, LED7SEG0_PIN);
	LL_GPIO_ResetOutputPin(LED7SEG_PORT, LED7SEG1_PIN);
}

void bsp_led7seg_turn_on_single(uint16_t ui16LedIdx)
{
	if (ui16LedIdx == 0) 	LL_GPIO_SetOutputPin(LED7SEG_PORT, LED7SEG0_PIN);
	else if(ui16LedIdx == 1) LL_GPIO_SetOutputPin(LED7SEG_PORT, LED7SEG1_PIN);

}
