
#include "bsp_usart.h"
#include "usart_io.h"
#include "ring_buf.h"
#include "stddef.h"
#include "board.h"
#include "board_configs.h"
#include "error_codes.h"
#include "stm32f7xx_ll_usart.h"



void _putchar(char character)
{
    /* Đợi cho đến khi thanh ghi truyền trống (TXE = 1 hoặc TXFNF = 1 tuỳ dòng) */
    while (!LL_USART_IsActiveFlag_TXE(USART1))
    {
    }

    /* Ghi 1 byte vào thanh ghi truyền */
    LL_USART_TransmitData8(USART1, character);
}
