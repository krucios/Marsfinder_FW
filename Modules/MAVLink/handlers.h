/*
 * handlers.h
 *
 *  Created on: 20 Jul 2016
 *      Author: Andrei.Pazniak (krucios@mail.ru)
 */

#ifndef MODULES_MAVLINK_HANDLERS_H_
#define MODULES_MAVLINK_HANDLERS_H_

#include "common/mavlink.h"
#include "mavlink_helpers.h"

#include <Modules/UART/uart.h>
#include <Modules/Storage/Parameters_Holder/param_holder.h>

#include <stdio.h>

void handle_mavlink_user_1_cmd(mavlink_command_long_t* cmd);
void handle_mavlink_user_2_cmd(mavlink_command_long_t* cmd);
void handle_mavlink_message(mavlink_message_t* msg);

#endif /* MODULES_MAVLINK_HANDLERS_H_ */
