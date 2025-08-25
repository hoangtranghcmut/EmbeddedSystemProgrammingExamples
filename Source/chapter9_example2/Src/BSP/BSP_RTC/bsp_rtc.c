/*
 * bsp_rtc.c
 *
 *  Created on: Aug 6, 2025
 *      Author: Admin
 */


#include "do.h"
#include "spi_io.h"
#include "ds3234.h"
#include "bsp_rtc.h"

static do_t			ds3234CsPin;
const doInit_t ds3234CsPinInit= {
				.hGPIOInit = RTC_CS_GPIO_Port,
				.ui32PinNumInit =  RTC_CS_Pin,
				.bStatusInit = true}	;
static SPI_Io_t		spi1Dev;
const SPI_IoInit_t spi1DevInit = {
		.hSpi = RTC_SPI,
		.bitOrder = SPI_BIT_ORDER_MSB_FIRST,
		.lanes = SPI_SINGLE_LANE,
		.mode = SPI_MODE_3,
		.ui32MaxSpeedHz = 50000000
		};
static DS3234_Dev_t ds3234Dev;
const DS3234_Init_t ds3234DevInit=
		{
				.spiBus = &spi1Dev,
				.csPin = &ds3234CsPin,
				.hourMode = DS3234_HOUR_MODE_24H,
				.ui8OutputMode = DS3234_OUTPUT_MODE_INT,
				.ui8SqwFreq = DS3234_SQW_FREQ_1HZ
		};

void bsp_rtc_init()
{
	do_init(&ds3234CsPin, &ds3234CsPinInit);
	spi_io_init(&spi1Dev, &spi1DevInit);
	DS3234_Init(&ds3234Dev, &ds3234DevInit);

}

void bsp_rtc_set_time(DS3234_Time_t* time)
{
	DS3234_SetTime(&ds3234Dev, time);
}
void bsp_rtc_get_time(DS3234_Time_t* time)
{
	DS3234_GetTime(&ds3234Dev, time);
}
