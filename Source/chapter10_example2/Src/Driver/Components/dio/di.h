/*
 * DI.H
 *
 *  Created on: Aug 8, 2025
 *      Author: Admin
 */

#ifndef DRIVER_COMPONENTS_DIO_DI_H_
#define DRIVER_COMPONENTS_DIO_DI_H_


#include "stdint.h"
#include "stdbool.h"
#include "stm32f4xx.h"

enum {
	DI_RESET = 0,
	DI_SET
};
typedef struct
{
	GPIO_TypeDef * hGPIO;
	uint32_t		ui32PinMask;

}di_t;

typedef struct
{
	GPIO_TypeDef * hGPIOInit;
	uint32_t		ui32PinNumInit;

}diInit_t;

uint32_t di_init(di_t *me, const diInit_t * const init);
uint32_t di_status(di_t *me);


#endif /* DRIVER_COMPONENTS_DIO_DI_H_ */
