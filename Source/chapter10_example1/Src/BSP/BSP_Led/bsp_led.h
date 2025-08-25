/*
 * bsp_led.h
 *
 *  Created on: Aug 5, 2025
 *      Author: Admin
 */

#ifndef _BSP_LED_H_
#define _BSP_LED_H_

#include "board.h"

void bsp_led_init();

void bsp_led_on(uint32_t ui32LedNum);

void bsp_led_off(uint32_t ui32LedNum);

void bsp_led_toggle(uint32_t ui32LedNum);

#endif /* BSP_BSP_LED_BSP_LED_H_ */
