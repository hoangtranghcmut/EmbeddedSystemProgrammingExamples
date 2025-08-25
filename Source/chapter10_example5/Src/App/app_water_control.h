/*
 * app_water_control.h
 *
 *  Created on: Aug 8, 2025
 *      Author: Admin
 */

#ifndef _APP_WATER_CONTROL_H_
#define _APP_WATER_CONTROL_H_

#include "stdint.h"
#include "stdbool.h"

//#define APP_WATER_CONTROL_GUARD_TIMEOUT		(30 * 60 * 1000) //nếu bơm chạy quá 30 phút, báo lỗi
#define APP_WATER_CONTROL_GUARD_TIMEOUT		(  10 * 1000) //lấy giá trị thấp để mô phỏng

#define APP_WATER_BLINK_PERIOD				(  500) //chu kỳ chớp led


typedef enum {

	S_PUMP_OFF = 0 ,      // Đang tắt bơm
    S_PUMP_ON,         // Đang bơm
	S_SENSOR_ERROR,
    NUM_PUMP_STATES   // Tổng số trạng thái
} app_water_state_t;


enum {
	EVT_NONE,
	EVT_WATER_LOW,
	EVT_WATER_NOT_LOW,
	EVT_WATER_HIGH,
	EVT_WATER_NOT_HIGH,
	EVT_WATER_TIMEOUT_TIMER_FIRED,
	EVT_SENSOR_ERROR,
	MAX_NUM_EVT
};

typedef struct app_water_control_fsm_evt_t
{
	uint32_t signal;
}app_water_control_fsm_evt_t;

typedef void (* app_water_control_fsm_state_handler)(app_water_control_fsm_evt_t * evt);


typedef enum {
    S_ERROR_LED_OFF = 0,
	S_ERROR_BLINK_ON ,
	S_ERROR_BLINK_OFF ,

    NUM_ERROR_LED_STATES   // Tổng số trạng thái
} app_water_error_led_state_t;


void app_water_control_init(void);
void app_water_control_fsm_update(app_water_control_fsm_evt_t *evt);
void app_water_control_update(void);


#endif /* APP_APP_WATER_CONTROL_H_ */
