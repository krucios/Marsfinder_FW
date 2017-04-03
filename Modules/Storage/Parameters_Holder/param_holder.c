/*
 * param_holder.c
 *
 *  Created on: 20 Jul 2016
 *      Author: Andrei.Pazniak (krucios@mail.ru)
 */
#ifdef MAVLINK_EN
#include "param_holder.h"

Onboard_param_t params[ONBOARD_PARAM_COUNT] = {
        {0, "ACCEL_X"},
        {0, "ACCEL_Y"},
        {0, "ACCEL_Z"},
        {0, "GYROS_X"},
        {0, "GYROS_Y"},
        {0, "GYROS_Z"},
        {0, "MAGNT_X"},
        {0, "MAGNT_Y"},
        {0, "MAGNT_Z"},
        {0, "TEMP_CS"},
        {0, "LEFT_WH"},
        {0, "RIGH_WH"}
    };

static uint16_t m_parameter_i = 0;

void param_send(uint8_t index) {
    mavlink_message_t message;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    uint8_t len;

    mavlink_msg_param_value_pack(
        mavlink_system.sysid,
        mavlink_system.compid,
        &message,
        params[index].name,
        params[index].val,
        MAVLINK_TYPE_INT16_T,
        ONBOARD_PARAM_COUNT,
        index);
    mavlink_send_msg(&message);
}

void param_queued_send_start(void) {
    m_parameter_i = 0;
}

void param_queued_send_routine(void) {
    if (m_parameter_i < ONBOARD_PARAM_COUNT) {
        param_send(m_parameter_i);
        m_parameter_i++;
    }
}
#endif // MAVLINK_EN
