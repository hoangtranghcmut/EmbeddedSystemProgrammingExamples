/*
 * bsp_rtc.c
 *
 *  Created on: Aug 6, 2025
 *      Author: Admin
 */

#include "board.h"
#include "stm32f4xx_ll_exti.h"
#include "do.h"
#include "spi_io.h"
#include "ds3234.h"
#include "bsp_rtc.h"
#include "console.h"

static do_t			ds3234Cs1Pin;
const doInit_t ds3234Cs1PinInit= {
				.hGPIOInit = RTC_CS1_GPIO_Port,
				.ui32PinNumInit =  RTC_CS1_Pin,
				.bStatusInit = true}	;

static do_t			ds3234Cs2Pin;
const doInit_t ds3234Cs2PinInit= {
				.hGPIOInit = RTC_CS2_GPIO_Port,
				.ui32PinNumInit =  RTC_CS2_Pin,
				.bStatusInit = true}	;

static SPI_Io_t		spi1Dev;
const SPI_IoInit_t spi1DevInit = {
		.hSpi = RTC_SPI,
		.bitOrder = SPI_BIT_ORDER_MSB_FIRST,
		.lanes = SPI_SINGLE_LANE,
		.mode = SPI_MODE_3,
		.ui32MaxSpeedHz = 50000000
		};
static DS3234_Dev_t ds3234Dev1;
const DS3234_Init_t ds3234Dev1Init=
		{
				.spiBus = &spi1Dev,
				.csPin = &ds3234Cs1Pin,
				.hourMode = DS3234_HOUR_MODE_24H,
				.ui8OutputMode = DS3234_OUTPUT_MODE_INT,
				.ui8SqwFreq = DS3234_SQW_FREQ_1HZ
		};

static DS3234_Dev_t ds3234Dev2;
const DS3234_Init_t ds3234Dev2Init=
		{
				.spiBus = &spi1Dev,
				.csPin = &ds3234Cs2Pin,
				.hourMode = DS3234_HOUR_MODE_24H,
				.ui8OutputMode = DS3234_OUTPUT_MODE_INT,
				.ui8SqwFreq = DS3234_SQW_FREQ_1HZ
		};

void bsp_rtc_init()
{
	do_init(&ds3234Cs1Pin, &ds3234Cs1PinInit);
	do_init(&ds3234Cs2Pin, &ds3234Cs2PinInit);
	spi_io_init(&spi1Dev, &spi1DevInit);
	DS3234_Init(&ds3234Dev1, &ds3234Dev1Init);
	DS3234_Init(&ds3234Dev2, &ds3234Dev2Init);

}

void bsp_rtc1_set_time(DS3234_Time_t* time)
{
	DS3234_SetTime(&ds3234Dev1, time);
}
void bsp_rtc1_get_time(DS3234_Time_t* time)
{
	DS3234_GetTime(&ds3234Dev1, time);
}
void bsp_rtc2_set_time(DS3234_Time_t* time)
{
	DS3234_SetTime(&ds3234Dev2, time);
}
void bsp_rtc2_get_time(DS3234_Time_t* time)
{
	DS3234_GetTime(&ds3234Dev2, time);
}

static DS3234_Time_t rtc2Time = {
		0
};
void bsp_rtc_RTC2_trigger_callback()
{
	bsp_rtc2_get_time(&rtc2Time);
	console_printf("RTC2 Time h: %d m: %d s %d \r\n",rtc2Time.hours,rtc2Time.minutes,rtc2Time.seconds);
}
void EXTI0_IRQHandler(void)
{
  if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_0) != RESET)
  {
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_0);

    bsp_rtc_RTC2_trigger_callback();
  }
}
