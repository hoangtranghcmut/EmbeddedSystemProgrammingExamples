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
	#include "stm32f4xx_ll_gpio.h"

	#define CPU_CLOCK_HZ	16000000
	#define LED_ERROR_PORT	GPIOD
	#define LED_ERROR_PIN 	12
	#define CONSOLE_USART 	USART1
	#define NTC_ADC			ADC1
	#define	NTC_ADC_CHANNEL	10

	#define BUTTON_UP_Pin 		LL_GPIO_PIN_0
	#define BUTTON_UP_Port 		GPIOB
	#define BUTTON_DOWN_Pin 	LL_GPIO_PIN_1
	#define BUTTON_DOWN_Port 	GPIOB
	#define BUTTON_SET_Pin 		LL_GPIO_PIN_2
	#define BUTTON_SET_Port 	GPIOB
	#define BUTTON_ONOFF_Pin 	LL_GPIO_PIN_3
	#define BUTTON_ONOFF_Port 	GPIOB

	#define LED7SEG_PORT		GPIOA
	#define LED7SEG0_PIN		LL_GPIO_PIN_8
	#define LED7SEG1_PIN		LL_GPIO_PIN_9

	#define RELAY_PORT			GPIOA
	#define RELAY_PIN			LL_GPIO_PIN_10
	#define STATUS_LED_PORT		GPIOA
	#define STATUS_LED_PIN		LL_GPIO_PIN_11
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
