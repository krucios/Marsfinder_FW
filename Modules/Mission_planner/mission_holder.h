/*
 * waypoint_holder.h
 *
 *  Created on: 31 Mar 2017
 *      Author: Andrei.Pazniak (krucios@mail.ru)
 */

#ifndef MODULES_MISSION_PLANNER_MISSION_HOLDER_H_
#define MODULES_MISSION_PLANNER_MISSION_HOLDER_H_

#include <Modules/Rover_Control/rover_control.h>

/*
 * Return values from some MH's methods.
 */
typedef enum {
    OK,         // Function successfully done
    ALLOC_FAIL, // Problems with new memory allocation
    IDX_FAIL    // Out of borders
} MH_retval_t;

/* NOTES:
 * As we use synchronous RX method (placed in main.c) so we don't use IRQ_disable\IRQ_enable for critical sections
 */

/* Allocates or reallocates mission array.
 * Have CRITICAL SECTION */
MH_retval_t mh_init(uint32_t size);

/* Returns command by index or command with INVALID direction in case of out of border access */
Rover_cmd_t mh_get(uint32_t idx);

/* Sets command by index.
 * Returns IDX_FAIL in case of out of border access.
 * Have CRITICAL SECTION */
MH_retval_t mh_set(uint32_t idx, Rover_cmd_t cmd);

/* Returns size of mission array */
uint32_t    mh_size();

/* Frees memory.
 * Have CRITICAL SECTION */
MH_retval_t mh_clear();

#endif /* MODULES_MISSION_PLANNER_MISSION_HOLDER_H_ */
