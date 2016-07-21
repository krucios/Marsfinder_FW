/*
 * micros.h
 *
 *  Created on: 20 Jul 2016
 *      Author: S2400105
 */

#ifndef MODULES_MICROS_MICROS_H_
#define MODULES_MICROS_MICROS_H_

static uint32_t sec = 0;
static uint32_t msec = 0;

uint64_t micros();

void micros_service_routine();

#endif /* MODULES_MICROS_MICROS_H_ */
