/*
 * time.c
 *
 *  Created on: 20 Jul 2016
 *      Author: Andrei.Pazniak (krucios@mail.ru)
 */

#include "time.h"

#include <drivers_config/sys_config/sys_config.h>

uint32_t sec = 0;
uint32_t msec = 0;

inline uint64_t usec() {
    return (uint64_t)(1000000 * sec)
         + (MSEC_PER_SEC * msec)
         + (TIMER_PERIOD(USR_TIMER_FREQ) - MSS_TIM1_get_current_value()) / 50;
         //  TimVal * TimPeriod (us) / TimReloadVal
}

void usec_service_routine() {
    msec += USR_PERIOD_MSEC;
    if (msec >= MSEC_PER_SEC) {
        sec++;
        msec %= MSEC_PER_SEC;
    }
}

