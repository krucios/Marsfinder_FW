#ifdef MAVLINK_EN

#include <Modules/MAVLink/common/mavlink.h>
#include <Modules/MAVLink/handlers.h>
#include <Modules/Rover_Control/rover_control.h>

void handle_mavlink_user_2_cmd(mavlink_command_long_t* cmd) {
    uint8_t dir = (uint8_t) (cmd->param1);
    uint32_t units = (uint32_t)(cmd->param2);
    Rover_cmd_t rv_cmd = {dir, units};
    rover_move(rv_cmd);
}

#endif // MAVLINK_EN
