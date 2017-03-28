/*
 * rover_control.c
 *
 *  Created on: 05 марта 2016 г.
 *      Author: kruci_000
 */

#include "rover_control.h"
#include <CMSIS/m2sxxx.h>

/**
 * Global variables
 */
Rover_distance_t rover_dist = {0, 0, 0, 0};

/**
 * Local variables
 */
pwm_instance_t g_pwm;
pwm_id_t pwms[8]= {PWM_1, PWM_2, PWM_3, PWM_4, PWM_5, PWM_6, PWM_7, PWM_8};
pwm_tach_id_t interrupted_tach;

void Rover_init() {
    uint32_t i;

    PWM_init(&g_pwm, COREPWM_0_0, PWM_PRESCALE, PWM_PERIOD);
    PWM_tach_init(&g_pwm, TACH_PRESCALE_PCLK_DIV_2048);
    PWM_tach_set_mode(&g_pwm, PWM_TACH_1, TACH_CONTINUOUS);
    PWM_tach_set_mode(&g_pwm, PWM_TACH_2, TACH_CONTINUOUS);

    for (i = 0; i < 8; i++)
        PWM_enable(&g_pwm, pwms[i]);

    Rover_go(STOP);

    PWM_tach_clear_status(&g_pwm, PWM_TACH_1);
    PWM_tach_clear_status(&g_pwm, PWM_TACH_2);

    PWM_tach_enable_irq(&g_pwm, PWM_TACH_1);
    PWM_tach_enable_irq(&g_pwm, PWM_TACH_2);

    /* Clear interrupt */
    NVIC_ClearPendingIRQ(FabricIrq0_IRQn);

    /* Enable Interrupt IRQ0 */
    NVIC_EnableIRQ(FabricIrq0_IRQn);
}

void Rover_go(const RoverDirections dir) {
    uint32_t i;

    switch (dir) {
        case FORWARD: {
            for (i = 0; i < 8; i++)
                PWM_set_duty_cycle(&g_pwm, pwms[i], (i % 2) ? 0 : PWM_MAX);
            break;
        }
        case BACKWARD: {
            for (i = 0; i < 8; i++)
                PWM_set_duty_cycle(&g_pwm, pwms[i], (i % 2) ? PWM_MAX : 0);
            break;
        }
        case ROUND_LEFT: {
            for (i = 0; i < 4; i++)
                PWM_set_duty_cycle(&g_pwm, pwms[i], (i % 2) ? PWM_MAX : 0);
            for (i = 4; i < 8; i++)
                PWM_set_duty_cycle(&g_pwm, pwms[i], (i % 2) ? 0 : PWM_MAX);
            break;
        }
        case ROUND_RIGHT: {
            for (i = 0; i < 4; i++)
                PWM_set_duty_cycle(&g_pwm, pwms[i], (i % 2) ? 0 : PWM_MAX);
            for (i = 4; i < 8; i++)
                PWM_set_duty_cycle(&g_pwm, pwms[i], (i % 2) ? PWM_MAX : 0);
            break;
        }
        case STOP: {
            for (i = 0; i < 8; i++)
                PWM_set_duty_cycle(&g_pwm, pwms[i], 0);
            break;
        }
    }
}

void PWM_tach_IRQHandler(void) {
    interrupted_tach = PWM_tach_get_irq_source(&g_pwm);

    switch (interrupted_tach) {
    case PWM_TACH_INVALID: {
        PWM_tach_clear_irq(&g_pwm, interrupted_tach);
        /* Clear the interrupt in the Cortex-M3 NVIC */
        NVIC_ClearPendingIRQ(FabricIrq0_IRQn);
    } break;
    case PWM_TACH_1: {
        rover_dist.FL += MM_PER_WHEEL_TICK;
    } break;
    case PWM_TACH_2: {
        rover_dist.BR += MM_PER_WHEEL_TICK;
    } break;
    }
}
