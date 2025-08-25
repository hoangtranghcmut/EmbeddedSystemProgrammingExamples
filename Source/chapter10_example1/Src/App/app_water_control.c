/*
 * app_water_control.c
 *
 *  Created on: Aug 8, 2025
 *      Author: Admin
 */
#include "app_water_control.h"
#include "bsp_water.h"
#include "console_dbg.h"

// Biến trạng thái toàn cục (static để giới hạn phạm vi trong file)
static app_water_state_t current_state = S_PUMP_OFF;

#ifdef DEBUG_ENABLE
static const  char * app_water_state_name[] = {"S_PUMP_OFF","S_PUMP_ON"};

#endif
// Hàm khởi tạo máy trạng thái
void app_water_control_init(void) {
	DBG(DBG_LEVEL_INFO,"Initializing \r\n");
	bsp_water_init();
	current_state = S_PUMP_OFF; // Khởi tạo ở trạng thái dừng máy bơm
    bsp_water_motor_off();
    bsp_water_error_led_off();
    DBG(DBG_LEVEL_INFO,"state is %s \r\n", app_water_state_name[current_state]);
}
void app_water_control_update(void)
{
	app_water_control_fsm_update();
}
// Hàm xử lý máy trạng thái
void app_water_control_fsm_update(void) {

    switch (current_state) {
        case S_PUMP_OFF:

            if (WATER_UNDER == bsp_water_lower_sensor_status()) {
            	current_state = S_PUMP_ON;
            	bsp_water_motor_on();
            	DBG(DBG_LEVEL_INFO,"state is %s \r\n", app_water_state_name[current_state]);
            }
            break;
        case S_PUMP_ON:
            if (WATER_OVER == bsp_water_upper_sensor_status()) {
            	current_state = S_PUMP_OFF;
            	bsp_water_motor_off();
            	DBG(DBG_LEVEL_INFO,"state is %s \r\n", app_water_state_name[current_state]);
            }
            break;
        default:
        	current_state = S_PUMP_OFF;
        	DBG(DBG_LEVEL_INFO,"state is %s \r\n", app_water_state_name[current_state]);
            bsp_water_motor_off();
            break;
    }
}
