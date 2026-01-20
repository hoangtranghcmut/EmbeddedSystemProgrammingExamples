/*
 * bsp_rtc.h
 *
 *  Created on: Aug 6, 2025
 *      Author: Admin
 */

#ifndef BSP_BSP_RTC_BSP_RTC_H_
#define BSP_BSP_RTC_BSP_RTC_H_

#include "board.h"
#include "ds3234.h"

void bsp_rtc_init();
void bsp_rtc1_set_time(DS3234_Time_t* time);
void bsp_rtc1_get_time(DS3234_Time_t* time);
void bsp_rtc2_set_time(DS3234_Time_t* time);
void bsp_rtc2_get_time(DS3234_Time_t* time);
#endif /* BSP_BSP_RTC_BSP_RTC_H_ */
