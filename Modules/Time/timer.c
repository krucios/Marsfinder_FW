/*
 * timer.c
 *
 *  Created on: 21 Jul 2016
 *      Author: S2400105
 */

#include "timer.h"

void timers_init(void) {
    timer_mss1_init(MSS_TIMER_PERIODIC_MODE, MSS_TIM1_PERIOD);
    timer_sys_init(MSS_SYS_TIM_PERIOD);
}

void timer_mss1_init(mss_timer_mode_t mode, uint32_t load_value) {
    MSS_TIM1_init(mode);
    MSS_TIM1_load_background(load_value);
}

void timer_mss1_start(void) {
    MSS_TIM1_start();
    MSS_TIM1_enable_irq();
}

void timer_sys_init(uint32_t load_value) {
    /*-------------------------------------------------------------------------
     * Initialize the system tick for 10mS operation or 1 tick every 100th of
     * a second and also make sure it is lower priority than the I2C IRQs.
     */
    NVIC_SetPriority(SysTick_IRQn, 0xFFu); /* Lowest possible priority */
    SysTick_Config(load_value);
}
