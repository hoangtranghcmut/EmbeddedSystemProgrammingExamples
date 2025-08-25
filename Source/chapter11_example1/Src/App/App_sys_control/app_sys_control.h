/*
 * app_sys_control.h
 *
 *  Created on: Aug 15, 2025
 *      Author: Admin
 */

#ifndef _APP_SYS_CONTROL_H_
#define _APP_SYS_CONTROL_H_
#include "stdint.h"

typedef struct app_sys_control_t
{
	uint32_t state;
	uint16_t temperature;
	uint16_t setpoint;
	uint16_t shadow_setpoint;
	uint8_t	 relayStatus;

}app_sys_control_t;

typedef enum {
	S_SYS_CONTROL_ROOT = 0 ,
	S_SYS_CONTROL_OPERATION,
	S_SYS_CONTROL_NORMAL ,
	S_SYS_CONTROL_SETTING,
	S_SYS_CONTROL_ERROR,
	S_SYS_CONTROL_OFF,
    NUM_PUMP_STATES  // Tổng số trạng thái
} app_water_state_t;

#define APP_SYS_CONTROL_MAX_PARENT 	2
#define APP_SYS_CONTROL_MAX_EVT		5


#ifndef S_NULL
	#define S_NULL 0xFFFFFFFF
#endif
typedef struct app_sys_control_fsm_evt_t
{
	uint32_t signal;
	union data {
		uint16_t	temperature;
	} data;
}app_sys_control_fsm_evt_t;

typedef uint32_t (* app_sys_control_fsm_update_t)(app_sys_control_fsm_evt_t * evt);
typedef void  (* app_sys_control_fsm_entry_t)(void);
typedef void  (* app_sys_control_fsm_exit_t)(void);

typedef struct app_sys_control_fsm_state_handler_t
{
	uint32_t parent_state;
	uint32_t default_child_state;
	app_sys_control_fsm_update_t update_handler;
	app_sys_control_fsm_entry_t  entry_handler;
	app_sys_control_fsm_exit_t   exit_handler;
}app_sys_control_fsm_state_handler_t;

void app_sys_control_init();
void app_sys_control_update(void);

uint32_t  app_sys_control_evt_push(app_sys_control_fsm_evt_t *evt);
#endif /* APP_APP_SYS_CONTROL_APP_SYS_CONTROL_H_ */
