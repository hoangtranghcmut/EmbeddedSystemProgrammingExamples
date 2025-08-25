/*
 * app_button.c
 *
 *  Created on: Aug 17, 2025
 *      Author: Admin
 */
#include "app_button.h"
#include "bsp_button.h"
#include "app_sys_control.h"
#include "app_signals.h"
#define DEBUG_ENABLE

#include "console_dbg.h"
static app_button_t app_button = {
		.buttonDownCurrentState = BUTTON_RELEASE,
		.buttonUpCurrentState = BUTTON_RELEASE,
		.buttonSetCurrentState = BUTTON_RELEASE,
		.buttonOnOffCurrentState = BUTTON_RELEASE,
};

void app_button_update()
{
	app_sys_control_fsm_evt_t evt = {0};
	uint32_t buttonStatus;
	buttonStatus = bsp_button_up_status();
	if (buttonStatus != app_button.buttonUpCurrentState)
	{
		if (BUTTON_PRESSED == buttonStatus) evt.signal = EVT_SYS_CONTROL_UP_BUTTON_PRESSED;
		else evt.signal = EVT_SYS_CONTROL_UP_BUTTON_RELEASED;
		app_sys_control_evt_push(&evt);
		app_button.buttonUpCurrentState = buttonStatus;
		DBG(DBG_LEVEL_INFO," %s \r\n", "EVT_SYS_CONTROL_UP_BUTTON_PRESSED");
	}
	buttonStatus = bsp_button_down_status();
	if (buttonStatus != app_button.buttonDownCurrentState)
	{
		if (BUTTON_PRESSED == buttonStatus) evt.signal = EVT_SYS_CONTROL_DOWN_BUTTON_PRESSED;
		else evt.signal = EVT_SYS_CONTROL_DOWN_BUTTON_RELEASED;
		app_button.buttonDownCurrentState = buttonStatus;
		DBG(DBG_LEVEL_INFO," %s \r\n", "EVT_SYS_CONTROL_DOWN_BUTTON_PRESSED");

		app_sys_control_evt_push(&evt);
	}
	buttonStatus = bsp_button_set_status();
	if (buttonStatus != app_button.buttonSetCurrentState)
	{
		if (BUTTON_PRESSED == buttonStatus) evt.signal = EVT_SYS_CONTROL_SET_BUTTON_PRESSED;
		else evt.signal = EVT_SYS_CONTROL_SET_BUTTON_RELEASED;
		app_button.buttonSetCurrentState = buttonStatus;
		DBG(DBG_LEVEL_INFO," %s \r\n", "EVT_SYS_CONTROL_SET_BUTTON_PRESSED");


		app_sys_control_evt_push(&evt);
	}
	buttonStatus = bsp_button_onoff_status();
	if (buttonStatus != app_button.buttonOnOffCurrentState)
	{
		if (BUTTON_PRESSED == buttonStatus) evt.signal = EVT_SYS_CONTROL_ONOFF_BUTTON_PRESSED;
		else evt.signal = EVT_SYS_CONTROL_ONOFF_BUTTON_RELEASED;
		app_sys_control_evt_push(&evt);
		app_button.buttonOnOffCurrentState = buttonStatus;
		DBG(DBG_LEVEL_INFO," %s \r\n", "EVT_SYS_CONTROL_ONOFF_BUTTON_PRESSED");
	}
}
