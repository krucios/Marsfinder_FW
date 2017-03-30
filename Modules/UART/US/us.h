/*
 * us.h
 *
 *  Created on: 30 Mar 2017
 *      Author: Andrei.PAzniak (krucios@mail.ru)
 */

#ifndef MODULES_UART_US_US_H_
#define MODULES_UART_US_US_H_

#include <drivers/CoreUARTapb/core_uart_apb.h>

extern UART_instance_t g_us;

void     us_init(addr_t base_addr, uint16_t baud_val);
size_t   us_get_rx(uint8_t* rx_buffer, size_t buffer_size);
void     us_send(const uint8_t* tx_buf, size_t size);
void     us_polled_tx_string(const uint8_t* str);

#endif /* MODULES_UART_US_US_H_ */
