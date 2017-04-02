#include <Modules/MAVLink/common/mavlink.h>
#include <Modules/MAVLink/handlers.h>
#include <Modules/Mission_planner/mission_ctrl.h>

void handle_mavlink_user_3_cmd(mavlink_command_long_t* cmd) {
    uint8_t exec = (uint8_t) (cmd->param1);
    if (exec == 1) {
        mctrl_execute();
    }
}
