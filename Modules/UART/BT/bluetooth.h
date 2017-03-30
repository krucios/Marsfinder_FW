/*
 * bluetooth.h
 *
 *  Created on: 20 Jul 2016
 *      Author: Andrei.PAzniak (krucios@mail.ru)
 */

#ifndef MODULES_UART_BT_BLUETOOTH_H_
#define MODULES_UART_BT_BLUETOOTH_H_

#include <drivers/CoreUARTapb/core_uart_apb.h>

extern UART_instance_t g_bt;

void     bt_init(addr_t base_addr, uint16_t baud_val);
void     bt_send(const uint8_t* tx_buf, size_t size);
size_t   bt_get_rx(uint8_t* rx_buffer, size_t buffer_size);
void     bt_polled_tx_string(const uint8_t* str);

#endif /* MODULES_UART_BT_BLUETOOTH_H_ */
