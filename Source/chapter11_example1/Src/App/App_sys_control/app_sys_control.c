/*
 * app_sys_control.c
 *
 *  Created on: Aug 15, 2025
 *      Author: Admin
 */

#include "app_sys_control.h"
#include "hsm.h"
#include "fifo.h"
#include "stdint.h"
#include "stddef.h"

#include "app_led7seg.h"
#include "bsp_relay.h"
#include "app_signals.h"
#include "error_codes.h"
#define DEBUG_ENABLE

#include "console_dbg.h"

static void 	app_sys_control_s_operation_entry();
static void 	app_sys_control_s_operation_exit();
static uint32_t app_sys_control_s_operation_update(app_sys_control_fsm_evt_t * evt);
static void 	app_sys_control_s_normal_entry();
static void 	app_sys_control_s_normal_exit();
static uint32_t app_sys_control_s_normal_update(app_sys_control_fsm_evt_t * evt);

static void 	app_sys_control_s_setting_entry();
static void 	app_sys_control_s_setting_exit();
static uint32_t app_sys_control_s_setting_update(app_sys_control_fsm_evt_t * evt);

static void 	app_sys_control_s_error_entry();
static void 	app_sys_control_s_error_exit();
static uint32_t app_sys_control_s_error_update(app_sys_control_fsm_evt_t * evt);

static void 	app_sys_control_s_off_entry();
static void 	app_sys_control_s_off_exit();
static uint32_t app_sys_control_s_off_update(app_sys_control_fsm_evt_t * evt);


void static app_sys_control_fsm_transition(uint32_t ui32TargetState, uint32_t ui32CurrentState);
// khai báo mảng con trỏ hàm handler tương ứng với trạng thái
static const app_sys_control_fsm_state_handler_t appSysControlStateHandlers[NUM_PUMP_STATES] = {
		{
//ROOT
				S_NULL,
				S_SYS_CONTROL_OPERATION,
				NULL,
				NULL,
				NULL
		},
//S_SYS_CONTROL_OPERATION
		{
				S_SYS_CONTROL_ROOT,
				S_SYS_CONTROL_NORMAL,
				app_sys_control_s_operation_update,
				app_sys_control_s_operation_entry,
				app_sys_control_s_operation_exit,

		},
//S_SYS_CONTROL_NORMAL
		{		S_SYS_CONTROL_OPERATION,
				S_NULL,
				app_sys_control_s_normal_update,
				app_sys_control_s_normal_entry,
				app_sys_control_s_normal_exit,
		},
//S_SYS_CONTROL_SETTING
		{		S_SYS_CONTROL_OPERATION,
				S_NULL,
				app_sys_control_s_setting_update,
				app_sys_control_s_setting_entry,
				app_sys_control_s_setting_exit,
				},
//S_SYS_CONTROL_ERROR
		{		S_SYS_CONTROL_ROOT,
				S_NULL,
				app_sys_control_s_error_update,
				app_sys_control_s_error_entry,
				app_sys_control_s_error_exit
		},
//S_SYS_CONTROL_ONOFF
		{		S_SYS_CONTROL_ROOT,
				S_NULL,
				app_sys_control_s_off_update,
				app_sys_control_s_off_entry,
				app_sys_control_s_off_exit
		},
};

#ifdef DEBUG_ENABLE
static const  char * app_water_state_name[] = {
			"S_ROOT","S_SYS_CONTROL_OPERATION","S_SYS_CONTROL_NORMAL","S_SYS_CONTROL_SETTING",
			"S_SYS_CONTROL_ERROR", "S_SYS_CONTROL_OFF"};

#endif

static app_sys_control_t app_sys_control = {
		.state = S_SYS_CONTROL_NORMAL,
		.setpoint = 25,
		.shadow_setpoint = 25,
		.relayStatus = 0,
		.temperature = 25
};
//lkhai báo bộ đệm chứa dữ liệu cho event FIFO
static app_sys_control_fsm_evt_t appSysControlEvtBuffer[APP_SYS_CONTROL_MAX_EVT];



//khởi tạo FIFO ngay lúc khai báo
Fifo_t appSysControlEvtFifo = {
		.p_vBuf = appSysControlEvtBuffer,
		.ui32Head = 0,
		.ui32Tail = 0,
		.ui32End = APP_SYS_CONTROL_MAX_EVT,
		.uiElementSize = sizeof(app_sys_control_fsm_evt_t)
};

void app_sys_control_init()
{
	DBG(DBG_LEVEL_INFO,"app_sys_control_init \r\n");
	app_led7seg_set_normal_mode();
}
static uint32_t 	app_sys_control_s_operation_update(app_sys_control_fsm_evt_t * evt)
{
	DBG(DBG_LEVEL_INFO,"app_sys_control_s_operation_update \r\n");
	switch (evt->signal)
	{
	case EVT_SYS_CONTROL_TEMPERATURE_ERROR:
		app_sys_control.state = S_SYS_CONTROL_ERROR;
		return HSM_EVENT_HANDLED;
	case EVT_SYS_CONTROL_ONOFF_BUTTON_PRESSED:
		app_sys_control.state = S_SYS_CONTROL_OFF;
		return HSM_EVENT_HANDLED;
	default:
		return HSM_EVENT_IGNORED;
	}
}
static void 	app_sys_control_s_operation_entry()
{
	DBG(DBG_LEVEL_INFO,"app_sys_control_s_operation_entry \r\n");
}
static void 	app_sys_control_s_operation_exit()
{
	DBG(DBG_LEVEL_INFO,"app_sys_control_s_operation_entry \r\n");

}

static void 	app_sys_control_s_normal_entry()
{
	DBG(DBG_LEVEL_INFO,"app_sys_control_s_normal_entry \r\n");
	app_led7seg_set_normal_mode();
	app_led7seg_display_temperature(app_sys_control.temperature);
}
static void 	app_sys_control_s_normal_exit()
{
	DBG(DBG_LEVEL_INFO,"app_sys_control_s_normal_exit \r\n");
}
static uint32_t app_sys_control_s_normal_update(app_sys_control_fsm_evt_t * evt)
{
//	DBG(DBG_LEVEL_INFO,"app_sys_control_s_normal_update \r\n");
	switch (evt->signal)
	{
	case	EVT_SYS_CONTROL_TEMPERATURE_UPDATE:
		uint16_t temperature = evt->data.temperature;
		app_sys_control.temperature = temperature;
		if (temperature > app_sys_control.setpoint)
			{
				bsp_relay_off();
				app_sys_control.relayStatus = RELAY_OFF;
			}
		else
			{
				bsp_relay_on();
				app_sys_control.relayStatus = RELAY_ON;
			}
		app_led7seg_display_temperature(temperature);
		return HSM_EVENT_HANDLED;

	case EVT_SYS_CONTROL_DOWN_BUTTON_PRESSED:
	case EVT_SYS_CONTROL_UP_BUTTON_PRESSED:
	case EVT_SYS_CONTROL_SET_BUTTON_PRESSED:
		app_sys_control.state = S_SYS_CONTROL_SETTING;
		return HSM_EVENT_HANDLED;
	case EVT_SYS_CONTROL_ONOFF_BUTTON_PRESSED:
		return HSM_EVENT_SUPER;
	case EVT_SYS_CONTROL_TEMPERATURE_ERROR:
		return HSM_EVENT_SUPER;
	default:
		return HSM_EVENT_IGNORED;
	}
}

static void 	app_sys_control_s_setting_entry()
{
	DBG(DBG_LEVEL_INFO,"app_sys_control_s_setting_entry \r\n");
	app_sys_control.shadow_setpoint = app_sys_control.setpoint;
	app_led7seg_display_temperature(app_sys_control.shadow_setpoint);
	app_led7seg_set_blink_mode();
}
static void 	app_sys_control_s_setting_exit()
{
	DBG(DBG_LEVEL_INFO,"app_sys_control_s_setting_exit \r\n");

}
static uint32_t app_sys_control_s_setting_update(app_sys_control_fsm_evt_t * evt)
{
//	DBG(DBG_LEVEL_INFO,"app_sys_control_s_setting_update \r\n");
	switch (evt->signal)
	{
	case EVT_SYS_CONTROL_UP_BUTTON_PRESSED:
		app_sys_control.shadow_setpoint ++;
		app_led7seg_display_temperature(app_sys_control.shadow_setpoint);
		return HSM_EVENT_HANDLED;
	case EVT_SYS_CONTROL_DOWN_BUTTON_PRESSED:
		app_sys_control.shadow_setpoint --;
		app_led7seg_display_temperature(app_sys_control.shadow_setpoint);
		return HSM_EVENT_HANDLED;
	case EVT_SYS_CONTROL_SET_BUTTON_PRESSED:
		app_sys_control.setpoint = app_sys_control.shadow_setpoint;
		app_sys_control.state = S_SYS_CONTROL_NORMAL;
		return HSM_EVENT_HANDLED;
	case EVT_SYS_CONTROL_ONOFF_BUTTON_PRESSED:
		DBG(DBG_LEVEL_INFO,"received EVT_SYS_CONTROL_ONOFF_BUTTON_PRESSED \r\n");
		return HSM_EVENT_SUPER;
	default:
		return HSM_EVENT_IGNORED;
	}

}

static void 	app_sys_control_s_error_entry()
{
	uint8_t errorCode[2] = {0x86, 0x97};
	DBG(DBG_LEVEL_INFO,"app_sys_control_s_error_entry \r\n");
	bsp_relay_off();
	app_led7seg_set_data(errorCode);
	app_led7seg_set_blink_mode();
}
static void 	app_sys_control_s_error_exit()
{
	DBG(DBG_LEVEL_INFO,"app_sys_control_s_error_exit \r\n");

}
static uint32_t app_sys_control_s_error_update(app_sys_control_fsm_evt_t * evt)
{
	DBG(DBG_LEVEL_INFO,"app_sys_control_s_error_update \r\n");
	switch (evt->signal)
	{

	case EVT_SYS_CONTROL_ONOFF_BUTTON_PRESSED:
		app_sys_control.state = S_SYS_CONTROL_OFF;
		return HSM_EVENT_SUPER;
	default:
		return HSM_EVENT_IGNORED;
	}
}

static void 	app_sys_control_s_off_entry()
{ uint8_t offCode[2 ] = {0xA3, 0x87};
	DBG(DBG_LEVEL_INFO,"app_sys_control_s_error_entry \r\n");
	bsp_relay_off();
	app_led7seg_set_data(offCode);
	app_led7seg_set_blink_mode();
}
static void 	app_sys_control_s_off_exit()
{
	DBG(DBG_LEVEL_INFO,"app_sys_control_s_off_exit \r\n");

}
static uint32_t app_sys_control_s_off_update(app_sys_control_fsm_evt_t * evt)
{
	DBG(DBG_LEVEL_INFO,"app_sys_control_s_off_update \r\n");
	switch (evt->signal)
	{

	case EVT_SYS_CONTROL_ONOFF_BUTTON_PRESSED:
		app_sys_control.state = S_SYS_CONTROL_OPERATION;
		return HSM_EVENT_HANDLED;
	default:
		return HSM_EVENT_IGNORED;
	}
}

void app_sys_control_fsm_dispatch(app_sys_control_fsm_evt_t *evt) {
	uint32_t preState = app_sys_control.state;
	uint32_t ui32Ret = HSM_EVENT_SUPER;
	app_sys_control_fsm_state_handler_t stateHandler = appSysControlStateHandlers[preState];

	while ((NULL != stateHandler.update_handler ) && (HSM_EVENT_SUPER == ui32Ret))
	{
		ui32Ret = stateHandler.update_handler(evt);

		if (HSM_EVENT_SUPER == ui32Ret)
			{
				DBG(DBG_LEVEL_INFO,"super state = %d \r\n", stateHandler.parent_state);
				stateHandler = appSysControlStateHandlers[stateHandler.parent_state];

			}
	}
	uint32_t currentState = app_sys_control.state;

		if (currentState != preState) //có chuyển trạng thái
		{
			//cập nhật trạng thái mặc định sâu nhất của trạng thái đích
			while (appSysControlStateHandlers[currentState].default_child_state != S_NULL)
				currentState = appSysControlStateHandlers[currentState].default_child_state;

			app_sys_control_fsm_transition(currentState,preState);

		}
}

void static app_sys_control_fsm_transition(uint32_t ui32TargetState, uint32_t ui32CurrentState)
{
	uint32_t currentAncestor[APP_SYS_CONTROL_MAX_PARENT] = {0};
	uint32_t targetAncestor[APP_SYS_CONTROL_MAX_PARENT] = {0};

	uint32_t state = ui32TargetState;
	uint32_t ui32TargetCount = 0;

	// lấy danh sách trạng thái cha của target state
	for ( ui32TargetCount = 0; ui32TargetCount < APP_SYS_CONTROL_MAX_PARENT; ui32TargetCount++)
	{
		targetAncestor[ui32TargetCount] = state;
		state = appSysControlStateHandlers[state].parent_state;
		if (S_NULL == state)	break;
	}
	// lấy danh sách trạng thái cha của current state
	state = ui32CurrentState;
	uint32_t ui32CurrentCount = 0;
	for ( ui32CurrentCount = 0; ui32CurrentCount < APP_SYS_CONTROL_MAX_PARENT; ui32CurrentCount++)
	{
		currentAncestor[ui32CurrentCount] = state;
		state = appSysControlStateHandlers[state].parent_state;
		if (S_NULL == state)	break;
	}

	// tìm vị trí LCA

    for (uint32_t i = 0; i < ui32CurrentCount; i++) {
        for (uint32_t j = 0; j < ui32TargetCount; j++) {
            if (currentAncestor[i] == targetAncestor[j]) {
                ui32CurrentCount = i;			//vị trí LCA
                ui32TargetCount = j;
                break; // Thoát vòng lặp khi tìm thấy LCA
            }
        }
    }

    //thực hiện các hàm exit từ trong ra ngoài
    for (int32_t i = 0; i < ui32CurrentCount; i++)
    {
    	if (appSysControlStateHandlers[currentAncestor[i]].exit_handler) {

    		appSysControlStateHandlers[currentAncestor[i]].exit_handler(); }
    }
    //thực hiện các hàm entry từ ngoài vào trong
    for (int32_t i = ui32TargetCount-1; i >= 0; i--)
    {
    	if (appSysControlStateHandlers[targetAncestor[i]].entry_handler){

    		appSysControlStateHandlers[targetAncestor[i]].entry_handler();
    	}
    }
    app_sys_control.state = ui32TargetState;
}

void app_sys_control_update(void)
{
	app_sys_control_fsm_evt_t evt;

	if (ERROR_OK == fifo_get(&appSysControlEvtFifo, &evt))
	{
//		DBG(DBG_LEVEL_INFO," %s \r\n", "Got event");

		app_sys_control_fsm_dispatch(&evt);
	}
}

uint32_t  app_sys_control_evt_push(app_sys_control_fsm_evt_t *evt)
{
	return fifo_put(&appSysControlEvtFifo, evt);
}
