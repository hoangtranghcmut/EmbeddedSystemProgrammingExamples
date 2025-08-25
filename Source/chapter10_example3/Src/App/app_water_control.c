/*
 * app_water_control.c
 *
 *  Created on: Aug 8, 2025
 *      Author: Admin
 */
#include "app_water_control.h"
#include "bsp_water.h"
#include "soft_timer.h"
#include "stdbool.h"
#include "console_dbg.h"
#include "soft_timer_config.h"

// Biến trạng thái toàn cục (static để giới hạn phạm vi trong file)
static app_water_state_t currentState = S_PUMP_CHECK;



#ifdef DEBUG_ENABLE
static const  char * app_water_state_name[] = {"S_PUMP_CHECK","S_PUMP_OFF","S_PUMP_ON","S_SENSOR_ERROR"};

#endif
// Hàm khởi tạo máy trạng thái
void app_water_control_init(void) {
	DBG(DBG_LEVEL_INFO,"Initializing \r\n");
	bsp_water_init();
	currentState = S_PUMP_CHECK; // Khởi tạo ở trạng thái khởi động
    bsp_water_motor_off();
    bsp_water_error_led_off();
    DBG(DBG_LEVEL_INFO,"state is %s \r\n", app_water_state_name[currentState]);
}
void app_water_control_update(void)
{
	app_water_control_fsm_update();
}
// Hàm xử lý máy trạng thái
void app_water_control_fsm_update(void) {

	//kiểm tra trạng thái sensor

	bool waterUnderLowerSen = (WATER_UNDER == bsp_water_lower_sensor_status());
	bool waterOverUpperSen  = (WATER_OVER == bsp_water_upper_sensor_status());
    switch (currentState) {
    case S_PUMP_CHECK:

        if (waterUnderLowerSen && (!waterOverUpperSen)) {
        	currentState = S_PUMP_ON;
        	bsp_water_motor_on();
        	//bật timer
        	soft_timer_set(SOFT_TIMER_WATER_CONTROL, APP_WATER_CONTROL_GUARD_TIMEOUT, false);

        	DBG(DBG_LEVEL_INFO,"state is %s \r\n", app_water_state_name[currentState]);
        }
        else if (!waterUnderLowerSen)
        {
        	currentState = S_PUMP_OFF;
        	bsp_water_motor_off();
        	DBG(DBG_LEVEL_INFO,"state is %s \r\n", app_water_state_name[currentState]);
        }
        else
        {
        	currentState = S_SENSOR_ERROR;
        	bsp_water_motor_off();
        	DBG(DBG_LEVEL_INFO,"state is %s \r\n", app_water_state_name[currentState]);
        }
        break;
        case S_PUMP_OFF:

            if (waterUnderLowerSen && (!waterOverUpperSen)) {
            	currentState = S_PUMP_ON;
            	bsp_water_motor_on();
            	//bật timer
            	soft_timer_set(SOFT_TIMER_WATER_CONTROL, APP_WATER_CONTROL_GUARD_TIMEOUT, false);
            	DBG(DBG_LEVEL_INFO,"state is %s \r\n", app_water_state_name[currentState]);
            }
            else if (waterUnderLowerSen && (waterOverUpperSen))
            {
            	currentState = S_SENSOR_ERROR;
            	bsp_water_motor_off();
            	DBG(DBG_LEVEL_INFO,"state is %s \r\n", app_water_state_name[currentState]);
            }
            break;
        case S_PUMP_ON:
            if (!waterUnderLowerSen && (waterOverUpperSen)){
            	currentState = S_PUMP_OFF;
            	bsp_water_motor_off();
            	//stop timer
            	soft_timer_stop(SOFT_TIMER_WATER_CONTROL);
            	DBG(DBG_LEVEL_INFO,"state is %s \r\n", app_water_state_name[currentState]);
            }
            else if ((waterUnderLowerSen && (waterOverUpperSen)) || soft_timer_is_overflow(SOFT_TIMER_WATER_CONTROL))
            {
            	currentState = S_SENSOR_ERROR;
            	//stop timer
            	soft_timer_stop(SOFT_TIMER_WATER_CONTROL);
            	bsp_water_motor_off();
            	DBG(DBG_LEVEL_INFO,"state is %s \r\n", app_water_state_name[currentState]);
            }
            break;
        case S_SENSOR_ERROR:

            break;
        default:			//không nên rơi vào trạng thái này
        	currentState = S_SENSOR_ERROR;
        	DBG(DBG_LEVEL_INFO,"state is %s \r\n", app_water_state_name[currentState]);
            bsp_water_motor_off();
            break;
    }
}
