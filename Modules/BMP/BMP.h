/*
 * bmp.h
 * Module (DOF10)
 * https://www.adafruit.com/datasheets/BST-BMP180-DS000-09.pdf
*/

#ifndef BMP_H_
#define BMP_H_

#include <stdint.h>

#include "../../Helpers/sys_helper/sys_helper.h"
#include "../I2C/i2c.h"

#define BMP180_SERIAL_ADDRESS 0x77

#include <unistd.h>

struct Cal_values
{
    // Calibration values
    int ac1;
    int ac2;
    int ac3;
    unsigned int ac4;
    unsigned int ac5;
    unsigned int ac6;
    int b1;
    int b2;
    int mb;
    int mc;
    int md;
} g_bmp_cal_values;

uint8_t BMP_calibrate();

i2c_status_t BMP_get_temperature(uint16_t* temperature);

#endif /* BMP_H_ */
