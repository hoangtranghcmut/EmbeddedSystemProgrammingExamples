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


static do_t			ds3234_1_CsPin = {
		.port = RTC_CS1_GPIO_Port,
		.pin = RTC_CS1_Pin,
		.bStatus = true				//after init, cs is set
};

static do_t			ds3234_2_CsPin = {
		.port = RTC_CS2_GPIO_Port,
		.pin = RTC_CS2_Pin,
		.bStatus = true				//after init, cs is set
};

static SPI_Io_t		spi1Dev = {
		.ui32SpiPort = RTC_SPI,
		.busy = false
};

static DS3234_Dev_t ds3234Dev1;
const DS3234_Init_t ds3234Dev1Init=
		{
				.spiBus = &spi1Dev,
				.csPin = &ds3234_1_CsPin,
				.hourMode = DS3234_HOUR_MODE_24H,
				.ui8OutputMode = DS3234_OUTPUT_MODE_INT,
				.ui8SqwFreq = DS3234_SQW_FREQ_1HZ
		};
static DS3234_Dev_t ds3234Dev2;
const DS3234_Init_t ds3234Dev2Init=
		{
				.spiBus = &spi1Dev,
				.csPin = &ds3234_2_CsPin,
				.hourMode = DS3234_HOUR_MODE_24H,
				.ui8OutputMode = DS3234_OUTPUT_MODE_INT,
				.ui8SqwFreq = DS3234_SQW_FREQ_1HZ
		};
void bsp_rtc_init()
{
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
