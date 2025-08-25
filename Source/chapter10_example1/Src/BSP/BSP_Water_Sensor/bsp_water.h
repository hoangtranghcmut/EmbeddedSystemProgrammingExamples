/*
 * bsp_water_sensor.h
 *
 *  Created on: Aug 8, 2025
 *      Author: Admin
 */

#ifndef _BSP_WATER_H_
#define _BSP_WATER_H_

#include "board.h"

enum {
	WATER_UNDER = 0,
	WATER_OVER
};
void bsp_water_init(void);
uint32_t bsp_water_upper_sensor_status(void);
uint32_t bsp_water_lower_sensor_status(void);
void bsp_water_error_led_on(void);
void bsp_water_error_led_off(void);
void bsp_water_motor_on(void);
void bsp_water_motor_off(void);
#endif /* BSP_BSP_WATER_SENSOR_BSP_WATER_H_ */
