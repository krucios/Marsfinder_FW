/*
 * rover_control.h
 *
 *  Created on: 05 марта 2016 г.
 *      Author: Andrei.PAzniak (krucios@mail.ru)
 */

#ifndef ROVER_CONTROL_H_
#define ROVER_CONTROL_H_

#include "drivers/CorePWM/core_pwm.h"

#define PWM_PRESCALE        (1u)
#define PWM_PERIOD          (1000u)
#define PWM_MAX PWM_PERIOD

#define SM_PER_WHEEL_TICK (1u)

#define ROVER_ALLOWED_DIST_DIFF  (5u) // sm
#define ROVER_ALLOWED_ANGLE_DIFF (15u) // degrees

typedef enum {
    FORWARD,
    BACKWARD,
    ROUND_LEFT,
    ROUND_RIGHT,
    STOP,
    INVALID
} Rover_direction;

typedef enum {
    MANUAL_CTRL,
    CMD_EXEC,
    AUTOPILOT
} Rover_mode;

typedef struct {
    Rover_direction dir;
    uint32_t        units;
} Rover_cmd_t;

/**
 *
 *  FL -> []---[] <- FR
 *           |
 *          / \
 *          | |
 *  BL -> []---[] <- BR
 */
typedef struct {
    int32_t FL; // Forward left
    int32_t FR; // Forward right
    int32_t BL; // Backward left
    int32_t BR; // Backward left
} Rover_distance_t;

extern Rover_distance_t rover_dist;
extern Rover_direction  rover_state;
extern Rover_mode       rover_mode;

void rover_init();
void rover_go(const Rover_direction dir);
void rover_move(const Rover_cmd_t cmd);
void rover_movei(const Rover_direction dir);
void rover_move_routine();

void PWM_tach_IRQHandler(void);

#endif /* ROVER_CONTROL_H_ */
