/*
 * soft_timer.c
 *
 *  Created on: Aug 9, 2025
 *      Author: Admin
 */


#include "soft_timer.h"
#include "soft_timer_config.h"
#include "stdint.h"
#include "atomic.h"
#include <string.h>
#include "error_codes.h"

static softTimer_t softTimer[SOFT_TIMER_MAX_TIMERS] = {0};

//hàm này sẽ được override trong bsp
__attribute__((weak)) uint32_t soft_timer_init_systick()
{
	return ERROR_OK;

}

uint32_t soft_timer_init(void)
{
	memset(softTimer, 0, sizeof(softTimer_t) * SOFT_TIMER_MAX_TIMERS);
	return ERROR_OK;
//	return soft_timer_init_systick();

}

uint32_t soft_timer_clear_flag(uint32_t ui32SoftTimerID)
{
	if (ui32SoftTimerID < SOFT_TIMER_MAX_TIMERS)
	{
		ATOMIC_WRITE(softTimer[ui32SoftTimerID].bTimerOverFlow, 0);
		return ERROR_OK;
	}
	return ERROR_INVALID_PARAM;
}

uint32_t soft_timer_set(uint32_t ui32SoftTimerID, uint32_t ui32Count, bool bIsPeriodic)
{
	if (ui32SoftTimerID < SOFT_TIMER_MAX_TIMERS)
	{
		ATOMIC_WRITE(softTimer[ui32SoftTimerID].ui32TimerCounterInMs, ui32Count);
		if (bIsPeriodic) ATOMIC_WRITE(softTimer[ui32SoftTimerID].ui32TimerPeriodInMS, ui32Count);
		return ERROR_OK;
	}
	return ERROR_INVALID_PARAM;
}

uint32_t soft_timer_stop(uint32_t ui32SoftTimerID)
{
	if (ui32SoftTimerID < SOFT_TIMER_MAX_TIMERS)
	{
		ATOMIC_WRITE(softTimer[ui32SoftTimerID].ui32TimerCounterInMs, 0);
		ATOMIC_WRITE(softTimer[ui32SoftTimerID].ui32TimerPeriodInMS, 0);
		ATOMIC_WRITE(softTimer[ui32SoftTimerID].bTimerOverFlow, false);
		return ERROR_OK;
	}
	return ERROR_INVALID_PARAM;
}
uint32_t soft_timer_register_callback(uint32_t ui32SoftTimerID, soft_timer_callback callBack)
{
	if (ui32SoftTimerID < SOFT_TIMER_MAX_TIMERS)
	{
		softTimer[ui32SoftTimerID].timerCallbackFunction = callBack;

		return ERROR_OK;
	}
	return ERROR_INVALID_PARAM;
}


void  soft_timer_update(void)
{

	for (uint16_t i = 0; i < SOFT_TIMER_MAX_TIMERS; i++)
	{
		uint32_t ui32Counter = softTimer[i].ui32TimerCounterInMs;
		if (ui32Counter > 0)
		{
			ui32Counter --;
			if (0 == ui32Counter)
			{
				softTimer[i].bTimerOverFlow = 1;
				//nếu timerPeriodInMS > 0 thì timer là loại periodic
				if (softTimer[i].ui32TimerPeriodInMS > 0) softTimer[i].ui32TimerCounterInMs = softTimer[i].ui32TimerPeriodInMS;
				else softTimer[i].ui32TimerCounterInMs = 0;
				//nếu hàm callback đã được đăng ký thì gọi callback
				if (softTimer[i].timerCallbackFunction)
				{
					(* softTimer[i].timerCallbackFunction)();
				}
			}
			else softTimer[i].ui32TimerCounterInMs = ui32Counter;

		}
	}
}

bool soft_timer_is_overflow(uint32_t ui32SoftTimerID)
{
	return (softTimer[ui32SoftTimerID].bTimerOverFlow);
}
