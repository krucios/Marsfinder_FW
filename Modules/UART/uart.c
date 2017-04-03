/*
 * uart.c
 *
 *  Created on: 21 ���� 2016 �.
 *      Author: Andrei.PAzniak (krucios@mail.ru)
 */

#include "uart.h"

inline void uart_init() {
    bt_init(COREUARTAPB_0_0, BAUD_VALUE_115200);
    us_init(COREUARTAPB_0_1, BAUD_VALUE_115200);
}


