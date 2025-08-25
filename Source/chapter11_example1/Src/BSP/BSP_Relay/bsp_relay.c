/*
 * bsp_relay.c
 *
 *  Created on: Aug 16, 2025
 *      Author: Admin
 */
#include "board.h"

void bsp_relay_on()
{
	LL_GPIO_SetOutputPin(RELAY_PORT, RELAY_PIN);
}

void bsp_relay_off()
{
	LL_GPIO_ResetOutputPin(RELAY_PORT, RELAY_PIN);
}
