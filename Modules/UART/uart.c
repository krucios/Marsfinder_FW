/*
 * uart.c
 *
 *  Created on: 21 ���� 2016 �.
 *      Author: kruci_000
 */

#include "uart.h"

inline void uart_init() {
    BT_init(COREUARTAPB_0_0, BAUD_VALUE_115200);
}


