/*
 * param_holder.h
 *
 *  Created on: 20 Jul 2016
 *      Author: S2400105
 */

#ifndef MODULES_PARAMETERS_HOLDER_PARAM_HOLDER_H_
#define MODULES_PARAMETERS_HOLDER_PARAM_HOLDER_H_

#include <Modules/MAVLink/common/mavlink.h>
#include <Modules/MAVLink/system.h>
#include <Modules/UART/uart.h>

#define ONBOARD_PARAM_COUNT 12
#define PARAM_AX        0
#define PARAM_AY        1
#define PARAM_AZ        2
#define PARAM_GX        3
#define PARAM_GY        4
#define PARAM_GZ        5
#define PARAM_MX        6
#define PARAM_MY        7
#define PARAM_MZ        8
#define PARAM_T         9
#define PARAM_FL_WHEEL  10
#define PARAM_BR_WHEEL  11

typedef struct {
    float val;
    char  name[MAVLINK_MSG_PARAM_SET_FIELD_PARAM_ID_LEN];
} Onboard_param_t;

extern Onboard_param_t params[ONBOARD_PARAM_COUNT];

void param_send(uint8_t index);
void param_queued_send_start(void);
void param_queued_send_routine(void);

#endif /* MODULES_PARAMETERS_HOLDER_PARAM_HOLDER_H_ */
