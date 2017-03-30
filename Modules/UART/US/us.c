/*
 * us.c
 *
 *  Created on: 30 Mar 2017
 *      Author: Andrei.PAzniak (krucios@mail.ru)
 */

#include "us.h"

UART_instance_t g_us;

inline void us_init(addr_t base_addr, uint16_t baud_val) {
    UART_init(&g_us, base_addr, baud_val, (DATA_8_BITS | NO_PARITY));
}

inline size_t us_get_rx(uint8_t* rx_buffer, size_t buffer_size) {
    return (UART_get_rx(&g_us, rx_buffer, buffer_size));
}

inline void us_send(const uint8_t* tx_buf, size_t size) {
    UART_send(&g_us, tx_buf, size);
}

inline void us_polled_tx_string(const uint8_t* str) {
    UART_polled_tx_string(&g_us, str);
}
