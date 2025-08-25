/*
 * board.h
 *
 *  Created on: Aug 2, 2025
 *      Author: Admin
 */

#ifndef BSP_BOARD_H_
#define BSP_BOARD_H_

#define STM32F4_DISCO
//#define MY_HARDWARE

# ifdef STM32F4_DISCO
	#include "stm32f4xx.h"
	#include "stm32f4xx_ll_usart.h"
	#define CONSOLE_USART USART1

#endif

# ifdef MY_HARDWARE_STM32F4
	#include "stm32f4xx.h"
	#include "stm32f4xx_ll_usart.h"
	#define CONSOLE_USART USART2

#endif

# ifdef MY_HARDWARE_STM32F1
	#include "stm32f1xx.h"
	#include "stm32f1xx_ll_usart.h"
	#define CONSOLE_USART USART2

#endif

#define VERSION_MAJOR      (1)
#define VERSION_MINOR      (0)
#define VERSION_PATCH      (0)

#endif /* BSP_BOARD_H_ */
