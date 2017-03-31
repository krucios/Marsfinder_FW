/*
 * waypoint_holder.c
 *
 *  Created on: 31 Mar 2017
 *      Author: Andrei.Pazniak (krucios@mail.ru)
 */

#include "mission_holder.h"
#include <stdlib.h>

uint32_t     cmd_arr_size;
Rover_cmd_t* cmd_arr;

MH_retval_t mh_init(uint32_t size) {
    if (size > 0) {
        mh_clear();
        cmd_arr_size = size;
        cmd_arr = (Rover_cmd_t*)malloc(sizeof(Rover_cmd_t) * size);
        if (!cmd_arr) {
            return (ALLOC_FAIL);
        }
    }
    return (OK);
}

Rover_cmd_t mh_get(uint32_t idx) {
    if (idx < cmd_arr_size) {
        return (cmd_arr[idx]);
    }
    Rover_cmd_t err = {INVALID, 0};
    return (err);
}

MH_retval_t mh_set(uint32_t idx, Rover_cmd_t cmd) {
    if (idx < cmd_arr_size) {
        cmd_arr[idx] = cmd;
        return (OK);
    }
    return (IDX_FAIL);
}

uint32_t mh_size() {
    return (cmd_arr_size);
}

MH_retval_t mh_clear() {
    free(cmd_arr);
    cmd_arr_size = 0;
    return (OK);
}
