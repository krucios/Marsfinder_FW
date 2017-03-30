#ifndef MAVLINK_CMD_USER_1_HANDLER
#define MAVLINK_CMD_USER_1_HANDLER

#include "../common/mavlink.h"

#include <Modules/Rover_Control/rover_control.h>

void handle_mavlink_user_1_cmd(mavlink_command_long_t* cmd) {
    uint8_t dir = cmd->param1;
    rover_movei((Rover_direction)dir);
}

#endif // MAVLINK_CMD_USER_1_HANDLER
