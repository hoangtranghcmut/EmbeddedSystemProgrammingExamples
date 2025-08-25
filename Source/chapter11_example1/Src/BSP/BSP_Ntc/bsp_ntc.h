/*
 * bsp_ntc.h
 *
 *  Created on: Aug 14, 2025
 *      Author: Admin
 */

#ifndef _BSP_NTC_H_
#define _BSP_NTC_H_

#include "stdint.h"


#define ADC_RES_BITS    12          // Độ phân giải ADC (ví dụ: 12-bit)
#define VREF_V          3.3f        // Vref ADC (Volt)
#define R_SER_OHM       10000.0f    // Điện trở nối GND trong cầu phân áp
#define NTC_R25_OHM     10000.0f    // R25 của NTC
#define NTC_BETA        4050.0f     // Hằng số Beta của NTC
#define TEMP_ERR_CODE   ((int16_t)0x8000) // Lỗi

int32_t bsp_ntc_temperature_conv(void);

#endif /* BSP_BSP_NTC_BSP_NTC_H_ */
