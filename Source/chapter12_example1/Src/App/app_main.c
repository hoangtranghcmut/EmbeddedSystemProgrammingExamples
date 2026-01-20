/*
 * app_main.c
 *
 *  Created on: Aug 2, 2025
 *      Author: Admin
 */
#include "stdint.h"
#include "error_codes.h"
#include "console.h"
#include "bsp_usart.h"
#include "bsp_led.h"
#include "console_dbg.h"
#include "FreeRTOS.h"
#include "task.h"

void ledRTask(void * parameter);
void ledGTask(void * parameter);


void app_main(void)
{
#ifdef DEBUG_ENABLE
	bsp_uart_console_init();
#endif

    BaseType_t xReturned;
    TaskHandle_t xHandle = NULL;

    /* Create the task, storing the handle. */
    xReturned = xTaskCreate(
    				ledRTask,       /* Function that implements the task. */
                    "ledRTask",          /* Text name for the task. */
					configMINIMAL_STACK_SIZE,      /* Stack size in words, not bytes. */
                    ( void * ) 0,    /* Parameter passed into the task. */
                    1,/* Priority at which the task is created. */
                    &xHandle );      /* Used to pass out the created task's handle. */

    if( xReturned == pdPASS )
    {
        /* The task was created. Use the task's handle to delete the task. */
        vTaskDelete( xHandle );
    }
    xReturned = xTaskCreate(
    				ledGTask,       /* Function that implements the task. */
                    "ledGTask",          /* Text name for the task. */
					configMINIMAL_STACK_SIZE,      /* Stack size in words, not bytes. */
                    ( void * ) 0,    /* Parameter passed into the task. */
                    1,/* Priority at which the task is created. */
                    NULL );      /* Used to pass out the created task's handle. */

    if( xReturned == pdPASS )
    {
        /* The task was created. Use the task's handle to delete the task. */
        vTaskDelete( xHandle );
    }

    vTaskStartScheduler();
	while (1)
	{

	}
}

void ledRTask(void * parameter)
{
	for (;;)
	{
		bsp_led_toggle(LED_RED);
		for (uint32_t i = 0; i< 100000; i++);
	}
}

void ledGTask(void * parameter)
{
	for (;;)
	{
		bsp_led_toggle(LED_GREEN);
		for (uint32_t i = 0; i< 100000; i++);
	}
}
