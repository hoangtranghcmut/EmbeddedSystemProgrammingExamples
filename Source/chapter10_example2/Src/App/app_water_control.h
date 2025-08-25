/*
 * app_water_control.h
 *
 *  Created on: Aug 8, 2025
 *      Author: Admin
 */

#ifndef _APP_WATER_CONTROL_H_
#define _APP_WATER_CONTROL_H_

#include <stdint.h>


typedef enum {
    S_PUMP_CHECK = 0,
	S_PUMP_OFF ,      // Đang tắt bơm
    S_PUMP_ON,         // Đang bơm
	S_SENSOR_ERROR,
    NUM_PUMP_STATES   // Tổng số trạng thái
} app_water_state_t;


void app_water_control_init(void);
void app_water_control_fsm_update(void);
void app_water_control_update(void);


#endif /* APP_APP_WATER_CONTROL_H_ */
