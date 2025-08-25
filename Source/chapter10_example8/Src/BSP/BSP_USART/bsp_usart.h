/**
 * @file bsp_usart.h
 * @brief UART console driver interface for STM32F4 using CMSIS.
 *
 * @details
 * This header defines the interface for low-level UART communication functions
 * used by the console system. It assumes the use of CMSIS and direct register
 * access for high performance and low overhead.
 *
 * Typical usage:
 * - Call `console_putchar(char c)` to send a character over UART
 * - Call `console_getchar(char *c)` to receive a character from UART
 * - Define `CONSOLE_USART` to specify which USART instance is used (e.g., USART1)
 *
 * @note You must initialize the USART peripheral (baudrate, GPIO, enable) before calling these functions.
 * @note These functions use blocking I/O; they wait until transmission/reception completes.
 *
 * @section Dependencies Dependencies
 * - STM32F4 CMSIS headers (e.g., stm32f4xx.h)
 * - `error_codes.h` for standardized return codes
 *
 * @author Admin
 * @date 2025-08-02
 * @version 1.0.0
 */

#ifndef __BSP_USART_H__
#define __BSP_USART_H__

#include "board.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void bsp_uart_console_init(void);

/**
 * @brief Transmit a character over the console USART.
 *
 * @param c The character to be transmitted.
 * @return ERROR_OK on success, ERROR_FAIL on failure.
 */
uint32_t console_putchar(char c);

/**
 * @brief Receive a character from the console USART.
 *
 * @param c Pointer to a char where the received character will be stored.
 * @return ERROR_OK on success, ERROR_FAIL if no data or invalid pointer.
 */
uint32_t console_getchar(char *c);

#ifdef __cplusplus
}
#endif

#endif // __BSP_USART_H__
