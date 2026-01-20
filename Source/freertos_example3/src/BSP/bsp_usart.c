/*
 * bsp_usart.c
 *
 *  Created on: Dec 14, 2025
 *      Author: Admin
 */

#include "stm32f7xx_ll_usart.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "main.h"
extern QueueHandle_t msg_queue;   // đã tạo: xQueueCreate(5, sizeof(messsage_t))

// _putchar dùng cho printf (polling)
// Yêu cầu: USART đã được init trước (baudrate, word length, stop bits, enable)
void _putchar(char character)
{
    // Chờ TXE = 1 (Transmit Data Register Empty)
    while (!LL_USART_IsActiveFlag_TXE(USART1))
    {
        // polling
    }

    // Ghi dữ liệu vào TDR
    LL_USART_TransmitData8(USART1, (uint8_t)character);


}


void USART1_RX_INT_Callback(void)
{
    uint8_t rx;
    messsage_t message;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    // Đọc byte nhận được (đọc RDR sẽ clear cờ RXNE)
    rx = LL_USART_ReceiveData8(USART1);

    // Đóng gói message
    message.task_src = 1;
    message.data     = (uint16_t)rx;

    // Gửi vào queue trong ISR
    (void)xQueueSendFromISR(msg_queue, &message, &xHigherPriorityTaskWoken);

    // Nếu việc gửi làm thức dậy task ưu tiên cao hơn thì yield ngay
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
