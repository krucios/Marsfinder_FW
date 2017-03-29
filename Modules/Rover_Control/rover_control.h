/*
 * rover_control.h
 *
 *  Created on: 05 марта 2016 г.
 *      Author: kruci_000
 */

#ifndef ROVER_CONTROL_H_
#define ROVER_CONTROL_H_

#include "drivers/CorePWM/core_pwm.h"

#define PWM_PRESCALE        (1u)
#define PWM_PERIOD          (1000u)
#define PWM_MAX PWM_PERIOD

#define SM_PER_WHEEL_TICK (1u)

#define ROVER_ALLOWED_ANGLE_DIFF (10u)

typedef enum {
    FORWARD,
    BACKWARD,
    ROUND_LEFT,
    ROUND_RIGHT,
    STOP
} Rover_direction;

/**
 *
 *  FL -> []---[] <- FR
 *           |
 *          / \
 *          | |
 *  BL -> []---[] <- BR
 */
typedef struct {
    uint32_t FL; // Forward left
    uint32_t FR; // Forward right
    uint32_t BL; // Backward left
    uint32_t BR; // Backward left
} Rover_distance_t;

extern Rover_distance_t rover_dist;
extern Rover_direction rover_state;

void Rover_init();
void Rover_go(const Rover_direction dir);
void Rover_move(const Rover_direction dir, const uint32_t unit); // sm for FW and BW deg for RL and RR
void Rover_move_routine();

void PWM_tach_IRQHandler(void);

#endif /* ROVER_CONTROL_H_ */
