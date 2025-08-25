/*
 * soft_timer.h
 *
 *  Created on: Aug 9, 2025
 *      Author: Admin
 */

#ifndef _SOFT_TIMER_H_
#define _SOFT_TIMER_H_

#include "stdint.h"
#include "stdbool.h"
typedef void (*soft_timer_callback) (void);


typedef struct softTimer_t
{
  uint32_t                		ui32TimerCounterInMs;
  uint32_t                      ui32TimerPeriodInMS;
  soft_timer_callback           timerCallbackFunction;
  bool							bTimerOverFlow;
} softTimer_t;

uint32_t soft_timer_init(void);
bool soft_timer_is_overflow(uint32_t ui32SoftTimerID);
void  soft_timer_update(void);
uint32_t soft_timer_register_callback(uint32_t ui32SoftTimerID, soft_timer_callback callBack);
uint32_t soft_timer_stop(uint32_t ui32SoftTimerID);
uint32_t soft_timer_set(uint32_t ui32SoftTimerID, uint32_t ui32Count, bool bIsPeriodic);
uint32_t soft_timer_clear_flag(uint32_t ui32SoftTimerID);
#endif /* MIDDLEWARE_SOFTTIMER_SOFT_TIMER_H_ */
