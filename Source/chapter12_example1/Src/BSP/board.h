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
	#define RTC_CS1_Pin 		 8
	#define RTC_CS1_GPIO_Port GPIOA
	#define RTC_CS2_Pin 		 9
	#define RTC_CS2_GPIO_Port GPIOA

	#define WATER_LOWER_SENSOR_PIN 				13
	#define WATER_LOWER_SENSOR_GPIO_PORT 		GPIOC
	#define WATER_ERROR_LED_PIN 				14
	#define WATER_ERROR_LED_GPIO_PORT 			GPIOC
	#define WATER_MOTOR_CONTROL_PIN 			15
	#define WATER_MOTOR_CONTROL_GPIO_PORT 		GPIOC
	#define WATER_UPPER_SENSOR_PIN 				12
	#define WATER_UPPER_SENSOR_GPIO_PORT 		GPIOC

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
