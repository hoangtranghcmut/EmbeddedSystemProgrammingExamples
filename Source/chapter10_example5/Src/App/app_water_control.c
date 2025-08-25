/*
 * app_water_control.c
 *
 *  Created on: Aug 8, 2025
 *      Author: Admin
 */
#include "app_water_control.h"
#include "bsp_water.h"
#include "bsp_led.h"
#include "soft_timer.h"
#include "stdbool.h"
#include "console_dbg.h"
#include "soft_timer_config.h"

// Biến trạng thái toàn cục (static để giới hạn phạm vi trong file)
static app_water_state_t currentState = S_PUMP_OFF;
static app_water_error_led_state_t errorLedState = S_ERROR_LED_OFF;
static	bool	bErrorStatus = false;

static bool preWaterUnderLowerSen = false;
static bool preWaterOverUpperSen  = false;

static void app_control_s_pump_off_handler(app_water_control_fsm_evt_t * evt);
void app_control_s_pump_on_handler(app_water_control_fsm_evt_t * evt);
void app_control_s_pump_error_handler(app_water_control_fsm_evt_t * evt);

// khai báo mảng con trỏ hàm handler tương ứng với trạng thái
static const app_water_control_fsm_state_handler appWaterControlStateHandler[NUM_PUMP_STATES] = {
		app_control_s_pump_off_handler,
		app_control_s_pump_on_handler,
		app_control_s_pump_error_handler
};

#ifdef DEBUG_ENABLE
static const  char * app_water_state_name[] = {"S_PUMP_OFF","S_PUMP_ON","S_SENSOR_ERROR"};
static const char * appErrorLedStateName[] = {"S_ERROR_LED_OFF" ,"S_ERROR_BLINK_ON" ,"S_ERROR_BLINK_OFF" };
#endif



 static void app_control_s_pump_off_handler(app_water_control_fsm_evt_t * evt)
 {
	 switch (evt->signal)
	 {
	 case EVT_WATER_LOW:
		 currentState = S_PUMP_ON;
		 bsp_water_motor_on();
		 soft_timer_set(SOFT_TIMER_WATER_CONTROL, APP_WATER_CONTROL_GUARD_TIMEOUT, false);
		 break;
	 case EVT_SENSOR_ERROR:
		 currentState = S_SENSOR_ERROR;
		 bsp_water_motor_off();
		 bErrorStatus = true;
		 break;
	 default:
		 break;
	 }
	    DBG(DBG_LEVEL_INFO,"state is %s \r\n", app_water_state_name[currentState]);

 }


 void app_control_s_pump_on_handler(app_water_control_fsm_evt_t * evt)
 {
	 switch (evt->signal)
	 {
	 case EVT_WATER_TIMEOUT_TIMER_FIRED:
	 case EVT_SENSOR_ERROR:
		 currentState = S_SENSOR_ERROR;
		 bsp_water_motor_off();
		 bErrorStatus =  true;
		 soft_timer_set(SOFT_TIMER_WATER_CONTROL, APP_WATER_CONTROL_GUARD_TIMEOUT, false);
		 break;
	 case EVT_WATER_HIGH:
		 currentState = S_PUMP_OFF;
		 bsp_water_motor_off();
		 break;
	 default:
		 break;
	 }
	    DBG(DBG_LEVEL_INFO,"state is %s \r\n", app_water_state_name[currentState]);

 }



 void app_control_s_pump_error_handler(app_water_control_fsm_evt_t * evt)
 {
	 switch (evt->signal)
	 {

	 default:
		 break;
	 }
	    DBG(DBG_LEVEL_INFO,"state is %s \r\n", app_water_state_name[currentState]);

 }

// Hàm khởi tạo máy trạng thái
void app_water_control_init(void) {
	DBG(DBG_LEVEL_INFO,"Initializing \r\n");
	bsp_water_init();
	currentState = S_PUMP_OFF; // Khởi tạo ở trạng thái khởi động
	bErrorStatus = false;		//khởi động biến trạng thái lỗi
    bsp_water_motor_off();
    bsp_water_error_led_off();
    errorLedState = S_ERROR_LED_OFF; //khởi động máy trạng thái cho Led
    bsp_led_error_init();
    bsp_water_error_led_off();
    DBG(DBG_LEVEL_INFO,"state is %s \r\n", app_water_state_name[currentState]);
    DBG(DBG_LEVEL_INFO,"error led state is %s \r\n", appErrorLedStateName[errorLedState]);
}

// Hàm lấy sự kiện từ ngõ vào, mỗi lần chỉ lấy 1 sự kiện
//trả về true nếu có sự kiện

static bool  app_water_control_fsm_get_event(app_water_control_fsm_evt_t *evt)
{
	bool waterUnderLowerSen = (WATER_UNDER == bsp_water_lower_sensor_status());
	bool waterOverUpperSen  = (WATER_OVER == bsp_water_upper_sensor_status());
	bool ret = false;

	if (waterUnderLowerSen != preWaterUnderLowerSen)
	{
		if (waterUnderLowerSen)
		{
				if (waterOverUpperSen)
				{
					evt->signal = EVT_SENSOR_ERROR;
					DBG(DBG_LEVEL_INFO,"signal %s \r\n", "EVT_SENSOR_ERROR");

				}
				else
				{
					DBG(DBG_LEVEL_INFO,"signal %s \r\n", "EVT_WATER_LOW");

					evt->signal = EVT_WATER_LOW;
				}
		}

		else
			{
				DBG(DBG_LEVEL_INFO,"signal %s \r\n", "EVT_WATER_NOT_LOW");
				evt->signal = EVT_WATER_NOT_LOW;

			}
		ret = true;
	}
	else if (waterOverUpperSen != preWaterOverUpperSen)
	{

		if (waterOverUpperSen)
			{
			if (waterUnderLowerSen)
			{
				DBG(DBG_LEVEL_INFO,"signal %s \r\n", "EVT_SENSOR_ERROR");
				evt->signal = EVT_SENSOR_ERROR;
			}
			else
			{
				DBG(DBG_LEVEL_INFO,"signal %s \r\n", "EVT_WATER_HIGH");
				evt->signal = EVT_WATER_HIGH;
			}
			}
		else
			{
				DBG(DBG_LEVEL_INFO,"signal %s \r\n", "EVT_WATER_NOT_HIGH");
				evt->signal = EVT_WATER_NOT_HIGH;
			}
		ret = true;
	}
	else if (soft_timer_is_overflow(SOFT_TIMER_WATER_CONTROL))
	{
		soft_timer_stop(SOFT_TIMER_WATER_CONTROL);
		DBG(DBG_LEVEL_INFO,"signal %s \r\n", "timer timeout EVT_SENSOR_ERROR");
		evt->signal = EVT_SENSOR_ERROR;
		ret = true;
	}
	preWaterUnderLowerSen = waterUnderLowerSen;
	preWaterOverUpperSen = waterOverUpperSen;
	return ret;
}
void app_water_control_fsm_update(app_water_control_fsm_evt_t *evt) {

	if (currentState < NUM_PUMP_STATES)
	{
		appWaterControlStateHandler[currentState](evt);
	}

}


void app_water_led_fsm_update(void)
{
	switch (errorLedState)
	{
	case S_ERROR_LED_OFF:
		if (bErrorStatus)
		{
			errorLedState = S_ERROR_BLINK_ON;
			bsp_led_error_on();
			//bật timer chạy theo chu kỳ
			soft_timer_set(SOFT_TIMER_BLINK_LED, APP_WATER_BLINK_PERIOD, true);
		    DBG(DBG_LEVEL_INFO,"error led state is %s \r\n", appErrorLedStateName[errorLedState]);

		}
		break;
	case S_ERROR_BLINK_ON:
		if (!bErrorStatus)
		{
			errorLedState = S_ERROR_LED_OFF;
			bsp_led_error_off();
			soft_timer_stop(SOFT_TIMER_BLINK_LED);
		    DBG(DBG_LEVEL_INFO,"error led state is %s \r\n", appErrorLedStateName[errorLedState]);

		}
		else if (soft_timer_is_overflow(SOFT_TIMER_BLINK_LED))
		{
			errorLedState = S_ERROR_BLINK_OFF;
			bsp_led_error_off();
			soft_timer_clear_flag(SOFT_TIMER_BLINK_LED);
		    DBG(DBG_LEVEL_INFO,"error led state is %s \r\n", appErrorLedStateName[errorLedState]);

		}

		break;

	case S_ERROR_BLINK_OFF:
		if (!bErrorStatus)
		{
			errorLedState = S_ERROR_LED_OFF;
			bsp_led_error_off();
			soft_timer_stop(SOFT_TIMER_BLINK_LED);
		    DBG(DBG_LEVEL_INFO,"error led state is %s \r\n", appErrorLedStateName[errorLedState]);

		}
		else if (soft_timer_is_overflow(SOFT_TIMER_BLINK_LED))
		{
			errorLedState = S_ERROR_BLINK_ON;
			bsp_led_error_on();
			soft_timer_clear_flag(SOFT_TIMER_BLINK_LED);
		    DBG(DBG_LEVEL_INFO,"error led state is %s \r\n", appErrorLedStateName[errorLedState]);

		}

		break;
	default:	//không nên vào đây
		errorLedState = S_ERROR_BLINK_ON;
		bsp_led_error_on();
		soft_timer_set(SOFT_TIMER_BLINK_LED, APP_WATER_BLINK_PERIOD, true);
	    DBG(DBG_LEVEL_INFO,"error led state is %s \r\n", appErrorLedStateName[errorLedState]);

		break;

	}
}

void app_water_control_update(void)
{
	app_water_control_fsm_evt_t evt;
	if (app_water_control_fsm_get_event(&evt))	app_water_control_fsm_update(&evt);
	app_water_led_fsm_update();
}
