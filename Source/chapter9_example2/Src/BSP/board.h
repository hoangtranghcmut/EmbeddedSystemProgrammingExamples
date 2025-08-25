/*
 * board.h
 *
 *  Created on: Aug 2, 2025
 *      Author: Admin
 */

#ifndef BSP_BOARD_H_
#define BSP_BOARD_H_


enum{
	LED_GREEN = 0,
	LED_BLUE ,
	LED_RED
};

#define STM32F4_DISCO
//#define MY_HARDWARE

# ifdef STM32F4_DISCO
	#include "stm32f4xx.h"
	#include "stm32f4xx_ll_usart.h"
	#define CONSOLE_USART USART1
	#define LED_GREEN_PORT	GPIOD
	#define LED_GREEN_PIN 	12
	#define LED_BLUE_PORT	GPIOD
	#define LED_BLUE_PIN 	13
	#define LED_RED_PORT	GPIOD
	#define LED_RED_PIN 	14

	#define	RTC_SPI			SPI1
	#define RTC_CS_Pin 		 8
	#define RTC_CS_GPIO_Port GPIOA


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
