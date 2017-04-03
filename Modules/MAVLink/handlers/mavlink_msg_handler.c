/*
 * mavlink_msg_handler.c
 *
 *  Created on: 30 Mar 2017
 *      Author: Andrei.PAzniak (krucios@mail.ru)
 */

#ifdef MAVLINK_EN

#include <Modules/MAVLink/common/mavlink.h>
#include <Modules/MAVLink/handlers.h>

void handle_mavlink_message(mavlink_message_t* msg) {
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];
    uint32_t len;

    switch (msg->msgid) {
        case MAVLINK_MSG_ID_COMMAND_LONG: {
            mavlink_command_long_t cmd;
            mavlink_msg_command_long_decode(msg, &cmd);

            if (is_sys_comp_match(cmd.target_system, cmd.target_component)) {
                uint8_t result;
                mavlink_message_t ack;

                switch (cmd.command) {
                case MAV_CMD_USER_1: {
                    handle_mavlink_user_1_cmd(&cmd);
                    result = MAV_RESULT_ACCEPTED; // TODO: check it
                } break;
                case MAV_CMD_USER_2: {
                    handle_mavlink_user_2_cmd(&cmd);
                    result = MAV_RESULT_ACCEPTED; // TODO: check it
                } break;
                case MAV_CMD_USER_3: {
                    handle_mavlink_user_3_cmd(&cmd);
                    result = MAV_RESULT_ACCEPTED;
                } break;
                default: {
                        mavlink_message_t msg;
                        uint8_t buff[50];

                        sprintf(buff, "Unknown CMD: %d", cmd.command);
                        result = MAV_RESULT_UNSUPPORTED;
                        mavlink_msg_statustext_pack(mavlink_system.sysid,
                                mavlink_system.compid, &msg, MAV_SEVERITY_ERROR, buff);
                        mavlink_send_msg(&msg);
                    }
                }
                mavlink_msg_command_ack_pack(
                        mavlink_system.sysid,
                        mavlink_system.compid,
                        &ack,
                        cmd.command,
                        result);
                mavlink_send_msg(&ack);
            }
        } break;
        case MAVLINK_MSG_ID_PARAM_REQUEST_LIST: {
            // Start sending parameters
            param_queued_send_start();
        } break;
        case MAVLINK_MSG_ID_PARAM_REQUEST_READ: {
            mavlink_param_request_read_t read;
            mavlink_msg_param_request_read_decode(msg, &read);

            // Check if this message is for this system
            if (is_sys_comp_match(read.target_system, read.target_component)) {
                char* key = (char*) read.param_id;
                if (!strcmp(key, params[read.param_index].name)) {
                    mavlink_message_t message;

                    mavlink_msg_param_value_pack(mavlink_system.sysid,
                            mavlink_system.compid, &message,
                            params[read.param_index].name,
                            params[read.param_index].val, MAVLINK_TYPE_FLOAT,
                            ONBOARD_PARAM_COUNT, read.param_index);
                    mavlink_send_msg(&message);
                }
            }
        } break;
        case MAVLINK_MSG_ID_PARAM_SET: {
            mavlink_param_set_t set;
            mavlink_msg_param_set_decode(msg, &set);

            // Check if this message is for this system
            if (is_sys_comp_match(set.target_system, set.target_component)) {
                char* key = (char*) set.param_id;
                for (uint16_t i = 0; i < ONBOARD_PARAM_COUNT; i++) {
                    if (!strcmp(key, params[i].name)) {
                        if (params[i].val != set.param_value
                                && set.param_type == MAVLINK_TYPE_FLOAT) {
                            params[i].val = set.param_value;
                            mavlink_message_t message;

                            mavlink_msg_param_value_pack(mavlink_system.sysid,
                                    mavlink_system.compid, &message,
                                    params[i].name, params[i].val,
                                    MAVLINK_TYPE_FLOAT,
                                    ONBOARD_PARAM_COUNT, i);
                            mavlink_send_msg(&message);
                        }
                    }
                }
            }
        } break;
    }
}

#endif // MAVLINK_EN
