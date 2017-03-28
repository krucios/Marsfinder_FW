/*
 * rover_control.h
 *
 *  Created on: 05 марта 2016 г.
 *      Author: kruci_000
 */

#ifndef ROVER_CONTROL_H_
#define ROVER_CONTROL_H_

#include "drivers/CorePWM/core_pwm.h"
#include "MC_hw_platform.h"

#define PWM_PRESCALE        (1)
#define PWM_PERIOD          (1000)
#define PWM_MAX PWM_PERIOD

#define MM_PER_WHEEL_TICK (-1) // TODO: place here actual value

typedef enum {
    FORWARD,
    BACKWARD,
    ROUND_LEFT,
    ROUND_RIGHT,
    STOP
} RoverDirections;

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

void Rover_init();
void Rover_go(const RoverDirections dir);

void PWM_tach_IRQHandler(void);

#endif /* ROVER_CONTROL_H_ */
