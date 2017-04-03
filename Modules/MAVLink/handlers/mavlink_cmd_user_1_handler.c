#ifdef MAVLINK_EN

#include <Modules/MAVLink/common/mavlink.h>
#include <Modules/MAVLink/handlers.h>
#include <Modules/Rover_Control/rover_control.h>

void handle_mavlink_user_1_cmd(mavlink_command_long_t* cmd) {
    uint8_t dir = cmd->param1;
    rover_movei((Rover_direction)dir);
}

#endif // MAVLINK_EN
