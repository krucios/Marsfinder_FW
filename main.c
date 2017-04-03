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
        bt_polled_tx_string("\n\rHello from DEBUG mode!\n\r\n\r");
        /* Place your debug code here */
        uint8_t us_buf[1024];
        uint32_t us_len;

        us_len = us_get_rx(us_buf, 1024);
        for (uint8_t i = 0; i < us_len; i++) {
            if (us_buf[i] != 0xA) {
                us_buf[i] += 32; // For prevent sending control characters
            }
        }
        bt_send(us_buf, us_len);
        bt_polled_tx_string("\n\r");
#endif // MAVLINK_EN
    }
    return (0);
}

void setup() {
    rover_init();
    mctrl_init();
    timers_init();
    uart_init();
    i2c_init();
    timer_mss1_start();
#ifdef MAVLINK_EN
    mavlink_sys_update(MAV_MODE_AUTO_ARMED, MAV_STATE_STANDBY);
#endif // MAVLINK_EN

#ifdef MPU6050_ENABLED
    mpu6050_init();
#ifdef MPU6050_SELFTEST
    if (mpu6050_selfTest()) {
#ifdef MAVLINK_EN
        mavlink_message_t msg;

        // TODO retcode into msg
        mavlink_msg_statustext_pack(
                mavlink_system.sysid,
                mavlink_system.compid,
                &msg,
                MAV_SEVERITY_CRITICAL,
                "MPU6050 SELFTEST FAILED");
        mavlink_send_msg(&msg);
#endif // MAVLINK_EN
    }
#endif // MPU6050_SELFTEST
    mpu6050_calibration();
#endif // MPU6050_ENABLED

#ifdef HMC_ENABLED
    HMC_init();
#ifdef HMC_SELFTEST
    if (HMC_self_test()) {
#ifdef MAVLINK_EN
        mavlink_message_t msg;

        // TODO retcode into msg
        mavlink_msg_statustext_pack(
                mavlink_system.sysid,
                mavlink_system.compid,
                &msg,
                MAV_SEVERITY_CRITICAL,
                "HMC SELFTEST FAILED");
        mavlink_send_msg(&msg);
#endif // MAVLINK_EN
    }
#endif // HMC_SELFTEST
#endif // HMC_ENABLED

    timer_mss2_start();
}


