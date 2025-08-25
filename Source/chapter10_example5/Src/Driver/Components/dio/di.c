/*
 * di.c
 *
 *  Created on: Aug 8, 2025
 *      Author: Admin
 */

#include "stdint.h"
#include "stddef.h"
#include "stdbool.h"
#include "error_codes.h"
#include "stm32f4xx.h"
#include "di.h"


uint32_t di_init(di_t *me, const diInit_t * const init)
{
	if (me == NULL) return ERROR_INVALID_PARAM;
	me->hGPIO = init->hGPIOInit;
	me->ui32PinMask = (1 << init->ui32PinNumInit);
	return ERROR_OK;
}

uint32_t di_status(di_t *me)
{
	if (me == NULL) return ERROR_INVALID_PARAM;

	    // Check the pin state in the GPIO Input Data Register (IDR)
	    return (me->hGPIO->IDR & me->ui32PinMask) ? DI_SET : DI_RESET;
}
