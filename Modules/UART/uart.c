/*
 * uart.c
 *
 *  Created on: 21 июля 2016 г.
 *      Author: Andrei.PAzniak (krucios@mail.ru)
 */

#include "uart.h"

inline void uart_init() {
    BT_init(COREUARTAPB_0_0, BAUD_VALUE_115200);
}


