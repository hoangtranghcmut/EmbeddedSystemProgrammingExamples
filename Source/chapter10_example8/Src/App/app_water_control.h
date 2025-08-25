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

#define APP_WATER_NUM_EVENT					(  5)
#define APP_WATER_CONTROL_MAX_PARENT				(2)		// độ sâu lớn nhất của cây trạng thái phân cấp

typedef enum {
	S_ROOT  ,
	S_OPERATION,
	S_PUMP_OFF ,      // Đang tắt bơm
    S_PUMP_ON,         // Đang bơm
	S_SENSOR_ERROR,
    NUM_SYS_CONTROL_STATES  // Tổng số trạng thái
} app_water_state_t;

#define S_NULL 0xFFFFFFFF
typedef struct app_water_control_fsm_evt_t
{
	uint32_t signal;
}app_water_control_fsm_evt_t;

typedef uint32_t (* app_water_control_fsm_state_handler_update)(app_water_control_fsm_evt_t * evt);
typedef void  (* app_water_control_fsm_state_handler_entry)(void);
typedef void  (* app_water_control_fsm_state_handler_exit)(void);

typedef struct app_water_control_fsm_state_handler_t
{
	uint32_t parent_state;
	uint32_t default_child_state;
	app_water_control_fsm_state_handler_update update_handler;
	app_water_control_fsm_state_handler_entry  entry_handler;
	app_water_control_fsm_state_handler_exit   exit_handler;
}app_water_control_fsm_state_handler_t;

void app_water_control_init(void);
void app_water_control_fsm_update(app_water_control_fsm_evt_t *evt);
void app_water_control_update(void);


#endif /* APP_APP_WATER_CONTROL_H_ */
