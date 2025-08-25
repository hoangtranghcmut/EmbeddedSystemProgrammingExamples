/*
 * app_signals.h
 *
 *  Created on: Aug 12, 2025
 *      Author: Admin
 */

#ifndef APP_APP_SIGNALS_H_
#define APP_APP_SIGNALS_H_

enum system_signals {
    SIG_INIT,    /* initial transition */
    SIG_ENTRY,   /* state entry */
    SIG_UPDATE,	/* state update internally */
    SIG_EXIT,    /* state exit */
    SIG_USER     /* first user-defined signal */
};

/* Event signals */
enum event_signals {

	EVT_WATER_LOW= SIG_USER,
	EVT_WATER_NOT_LOW,
	EVT_WATER_HIGH,
	EVT_WATER_NOT_HIGH,
	EVT_WATER_TIMEOUT_TIMER_FIRED,
	EVT_LED_BLINK_TIMER_TIMEOUT,
	EVT_SENSOR_ERROR,
	EVT_RESUME_PRESSED,
	EVT_RESUME_RELEASED,
	MAX_NUM_EVT

};

enum state_handler_t{
	TRAN_STATUS,
	HANDLED_STATUS,
	IGNORED_STATUS
};



#endif /* APP_APP_SIGNALS_H_ */
