/*
 * mission_ctrl.c
 *
 *  Created on: 02 апр. 2017 г.
 *      Author: kruci_000
 */

#include <Modules/Mission_planner/mission_ctrl.h>
#include <Modules/Rover_Control/rover_control.h>

MCtrl_state mctrl_state;
uint32_t cur_cmd_idx;

void mctrl_init() {
    mctrl_state = IDLE;
    Rover_cmd_t cmd_arr[MISSION_SIZE] = {
            {FORWARD, 200},
            {ROUND_RIGHT, 90},
            {FORWARD, 50},
            {ROUND_RIGHT, 90},
            {FORWARD, 50},
            {ROUND_RIGHT, 90},
            {FORWARD, 50},
            {ROUND_LEFT, 90},
            {FORWARD, 50},
            {ROUND_LEFT, 90},
            {FORWARD, 50},
            {ROUND_RIGHT, 90},
            {FORWARD, 50},
            {ROUND_RIGHT, 90},
            {FORWARD, 50},
            {ROUND_LEFT, 90},
            {FORWARD, 50},
            {ROUND_LEFT, 180}
    };
    mh_init(MISSION_SIZE);
    for (int i = 0; i < MISSION_SIZE; i++) {
        mh_set(i, cmd_arr[i]);
    }
}

void mctrl_execute() {
    mctrl_state = MISSION_EXEC;
    cur_cmd_idx = 0;
}

void mctrl_execute_routine() {
    if ((cur_cmd_idx < MISSION_SIZE) && (mctrl_state == MISSION_EXEC)) {
        if (rover_mode == MANUAL_CTRL) { // Rover has done previous command
            rover_move(mh_get(cur_cmd_idx++));
        }
    } else {
        mctrl_state = IDLE;
        cur_cmd_idx = 0;
    }
}

