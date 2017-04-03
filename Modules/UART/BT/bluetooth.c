/*
 * bluetooth.c
 *
 *  Created on: 21 июля 2016 г.
 *      Author: Andrei.PAzniak (krucios@mail.ru)
 */

#include "bluetooth.h"

#ifdef MAVLINK_EN
#include <Modules/MAVLink/handlers.h>
#include <Modules/MAVLink/common/mavlink.h>
#endif // MAVLINK_EN

UART_instance_t g_bt;

inline void bt_init(addr_t base_addr, uint16_t baud_val) {
    UART_init(&g_bt, base_addr, baud_val, (DATA_8_BITS | NO_PARITY));
}

inline void bt_send(const uint8_t* tx_buf, size_t size) {
    UART_send(&g_bt, tx_buf, size);
}

inline void bt_rx_routine() {
    uint8_t rx_c;

    if (UART_get_rx(&g_bt, &rx_c, 1)) {
#ifdef MAVLINK_EN
        mavlink_message_t msg;
        mavlink_status_t status;

        if (mavlink_parse_char(MAVLINK_COMM_0, rx_c, &msg, &status)) {
            handle_mavlink_message(&msg);
        }
#endif // MAVLINK_EN
    }
}

inline void bt_polled_tx_string(const uint8_t* str) {
    UART_polled_tx_string(&g_bt, str);
}


