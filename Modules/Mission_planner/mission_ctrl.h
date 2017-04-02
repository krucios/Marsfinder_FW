/*
 * mission_ctrl.h
 *
 *  Created on: 02 апр. 2017 г.
 *      Author: kruci_000
 */

#ifndef MODULES_MISSION_PLANNER_MISSION_CTRL_H_
#define MODULES_MISSION_PLANNER_MISSION_CTRL_H_

#include <Modules/Mission_planner/mission_holder.h>

#define MISSION_SIZE (18u)

typedef enum {
    IDLE,
    MISSION_EXEC
} MCtrl_state;

extern MCtrl_state mctrl_state;

void mctrl_init();
void mctrl_execute();
void mctrl_execute_routine();

#endif /* MODULES_MISSION_PLANNER_MISSION_CTRL_H_ */
