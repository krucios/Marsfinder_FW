/*
 * main.c
 *
 *  Created on: 30 Mar 2017
 *      Author: Andrei.PAzniak (krucios@mail.ru)
 */

#include <Modules/Rover_Control/rover_control.h>
#include <Modules/Mission_planner/mission_ctrl.h>
#include <Modules/Time/time.h>
#include <Modules/Time/timer.h>
#include <Modules/UART/uart.h>
#include <Modules/I2C/i2c.h>
#include <Modules/MPU6050/mpu6050.h>
#include <Modules/HMC/hmc.h>
#ifdef MAVLINK_EN
#include <Modules/MAVLink/common/mavlink.h>
#include <Modules/MAVLink/handlers.h>
#include <Modules/MAVLink/system.h>
#else
#include <stdlib.h>
#include <stdio.h>
#endif // MAVLINK_EN
#include <Modules/Storage/Parameters_Holder/param_holder.h>

#include <Helpers/sys_helper/sys_helper.h>

#include <hal.h>
#include <MC_hw_platform.h>
#include <m2sxxx.h>

#include <defines.h>

void setup(void);

int main(void) {
    // Modules initialisation
    setup();

    uint8_t us_buf[1024];
    uint32_t us_len;

    uint8_t dist_str[8];
    uint8_t angl_str[8];
    uint8_t res_str[20];
    uint8_t str_len;

    while (1) {
        delay(1000);
#ifdef MAVLINK_EN
#ifdef MPU6050_ENABLED
        mpu6050_getScaledData(&params[PARAM_AX].val,
                              &params[PARAM_AY].val,
                              &params[PARAM_AZ].val,
                              &params[PARAM_GX].val,
                              &params[PARAM_GY].val,
                              &params[PARAM_GZ].val,
                              &params[PARAM_T].val);
#endif // MPU6050_ENABLED
#ifdef HMC_ENABLED
        HMC_get_scaled_Data(&params[PARAM_MX].val,
                            &params[PARAM_MY].val,
                            &params[PARAM_MZ].val);
#endif // HMC_ENABLED

        params[PARAM_FL_WHEEL].val = rover_dist.FL;
        params[PARAM_BR_WHEEL].val = rover_dist.BR;

        bt_rx_routine();
        param_queued_send_routine();
#else
        /* Place your debug code here */
        us_len = us_get_rx((us_buf + us_len), 128);
        if (us_len > 3) {
            for (uint8_t i = 3; i < us_len;) { // 3 - length of message from US
                if (us_buf[i] == 0xA) {
                    uint16_t dist = (us_buf[i - 3] << 8) | us_buf[i - 2];
                    uint8_t  angl = us_buf[i - 1];

                    sprintf(res_str, "%0d\t%0d\r\n", dist, angl);
                    bt_polled_tx_string(res_str);

                    i += 3;
                } else {
                    i++;
                }
            }
            us_len = 0;
        }
#endif // MAVLINK_EN
    }
    return (0);
}

void setup() {
	uint8_t retcode;         // variable to store retcode
	uint8_t msg_str[40];     // variable to store a message string
	uint8_t hmc_retcode; 	 // variable to store retcode hmc module
	uint8_t hmc_msg_str[40]; // variable to store a message string for retcode hmc module
    rover_init();
    mctrl_init();
    timers_init();
    uart_init();
    i2c_init();
    timer_mss1_start();
#ifdef MAVLINK_EN
    mavlink_sys_update(MAV_MODE_AUTO_ARMED, MAV_STATE_STANDBY);
#else
    bt_polled_tx_string("\n\rHello from Marsfinder_FW mode!\n\r\n\r");
    us_polled_tx_string("w"); // ASCII 0x77
#endif // MAVLINK_EN

#ifdef MPU6050_ENABLED
    mpu6050_init();
#ifdef MPU6050_SELFTEST
    retcode = mpu6050_selfTest(); //store retcode from selfTest function
    if (retcode) {                //check retcode
#ifdef MAVLINK_EN
        mavlink_message_t msg;

        sprintf(msg_str,"MPU6050 SELFTEST FAILED. CODE: %0d",
        retcode);                 //create c-string with retcode
        // TODO retcode into msg
        mavlink_msg_statustext_pack(
                mavlink_system.sysid,
                mavlink_system.compid,
                &msg,
                MAV_SEVERITY_CRITICAL,
                msdg_str);        //use previously prepared c-string instead of string literal
        mavlink_send_msg(&msg);
#endif // MAVLINK_EN
    }
#endif // MPU6050_SELFTEST
    mpu6050_calibration();
#endif // MPU6050_ENABLED

#ifdef HMC_ENABLED
    HMC_init();
#ifdef HMC_SELFTEST
    hmc_retcode = HMC_self_test();  //store hmc_retcode from selfTest function
    if (hmc_retcode) {              //check hmc_retcode
#ifdef MAVLINK_EN
        mavlink_message_t msg;

        sprintf(hmc_msg_str,"HMC SELFTEST FAILED. CODE: %0d",
        hmc_retcode);               //create c-string with retcode
        // TODO retcode into msg
        mavlink_msg_statustext_pack(
                mavlink_system.sysid,
                mavlink_system.compid,
                &msg,
                MAV_SEVERITY_CRITICAL,
                hmc_msg_str);      //use previously prepared c-string instead of string literal
        mavlink_send_msg(&msg);
#endif // MAVLINK_EN
    }
#endif // HMC_SELFTEST
#endif // HMC_ENABLED

    timer_mss2_start();
}


