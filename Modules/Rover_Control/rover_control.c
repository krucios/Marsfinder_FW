/*
 * rover_control.c
 *
 *  Created on: 05 ����� 2016 �.
 *      Author: kruci_000
 */

#include "rover_control.h"
#include <CMSIS/m2sxxx.h>

/**
 * Global variables
 */
Rover_distance_t rover_dist = {0, 0, 0, 0};
Rover_direction rover_state = STOP;

/**
 * Local variables
 */
pwm_instance_t g_pwm;
pwm_id_t pwms[8] = {PWM_1, PWM_2, PWM_3, PWM_4, PWM_5, PWM_6, PWM_7, PWM_8};
pwm_tach_id_t interrupted_tach;
Rover_direction FL_dir, BR_dir;

uint32_t target_distance = 0;

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

void Rover_go(const Rover_direction dir) {
    uint32_t i;

    rover_state = dir;

    switch (dir) {
        case FORWARD: {
            FL_dir = FORWARD;
            BR_dir = FORWARD;
            for (i = 0; i < 8; i++)
                PWM_set_duty_cycle(&g_pwm, pwms[i], (i % 2) ? 0 : PWM_MAX);
            break;
        }
        case BACKWARD: {
            FL_dir = BACKWARD;
            BR_dir = BACKWARD;
            for (i = 0; i < 8; i++)
                PWM_set_duty_cycle(&g_pwm, pwms[i], (i % 2) ? PWM_MAX : 0);
            break;
        }
        case ROUND_LEFT: {
            FL_dir = BACKWARD;
            BR_dir = FORWARD;
            for (i = 0; i < 4; i++)
                PWM_set_duty_cycle(&g_pwm, pwms[i], (i % 2) ? PWM_MAX : 0);
            for (i = 4; i < 8; i++)
                PWM_set_duty_cycle(&g_pwm, pwms[i], (i % 2) ? 0 : PWM_MAX);
            break;
        }
        case ROUND_RIGHT: {
            FL_dir = FORWARD;
            BR_dir = BACKWARD;
            for (i = 0; i < 4; i++)
                PWM_set_duty_cycle(&g_pwm, pwms[i], (i % 2) ? 0 : PWM_MAX);
            for (i = 4; i < 8; i++)
                PWM_set_duty_cycle(&g_pwm, pwms[i], (i % 2) ? PWM_MAX : 0);
            break;
        }
        case STOP: {
            FL_dir = STOP;
            BR_dir = STOP;
            for (i = 0; i < 8; i++)
                PWM_set_duty_cycle(&g_pwm, pwms[i], 0);
            break;
        }
    }
}

void Rover_move(const Rover_direction dir, const uint32_t sm) {
    uint32_t start_value = (rover_dist.FL + rover_dist.BR) / 2;
    target_distance = start_value + sm;
    Rover_go(dir);
}

void Rover_move_routine() {
    uint32_t cur_dist = (rover_dist.FL + rover_dist.BR) / 2;
    if (target_distance < cur_dist) {
        Rover_go(STOP);
    }
}

void PWM_tach_IRQHandler(void) {
    interrupted_tach = PWM_tach_get_irq_source(&g_pwm);

    if (interrupted_tach != PWM_TACH_INVALID) {
        switch (interrupted_tach) {
        case PWM_TACH_1: {
            if (FL_dir == FORWARD) {
                rover_dist.FL += SM_PER_WHEEL_TICK;
            } else if (FL_dir == BACKWARD) {
                rover_dist.FL -= SM_PER_WHEEL_TICK;
            }
        } break;
        case PWM_TACH_2: {
            if (BR_dir == FORWARD) {
                rover_dist.BR += SM_PER_WHEEL_TICK;
            } else if (BR_dir == BACKWARD) {
                rover_dist.BR -= SM_PER_WHEEL_TICK;
            }
        } break;
        }

        PWM_tach_clear_irq(&g_pwm, interrupted_tach);
        /* Clear the interrupt in the Cortex-M3 NVIC */
        NVIC_ClearPendingIRQ(FabricIrq0_IRQn);
    }
}
