/*
 * time.h
 *
 *  Created on: 20 Jul 2016
 *      Author: S2400105
 */

#ifndef MODULES_TIME_TIME_H_
#define MODULES_TIME_TIME_H_

#include <stdint.h>
#include <Modules/Time/timer.h>
#include <mss_timer/mss_timer.h>

#define USR_TIMER_FREQ MSS_TIM1_FREQ
#define MSEC_PER_SEC (1000u)
#define USR_PERIOD_MSEC (MSEC_PER_SEC / USR_TIMER_FREQ)

extern uint32_t sec;
extern uint32_t msec;

uint64_t usec();
void usec_service_routine();

#endif /* MODULES_TIME_TIME_H_ */
