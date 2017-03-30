#include <Modules/MAVLink/common/mavlink.h>
#include <Modules/MAVLink/handlers.h>
#include <Modules/Rover_Control/rover_control.h>

void handle_mavlink_user_2_cmd(mavlink_command_long_t* cmd) {
    uint8_t dir = (uint8_t) (cmd->param1);
    uint32_t sm = (uint32_t)(cmd->param2);
    rover_move((Rover_direction)dir, sm);
}
