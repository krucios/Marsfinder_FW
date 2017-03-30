/*
 * main.c
 *
 *  Created on: 30 Mar 2017
 *      Author: Andrei.PAzniak (krucios@mail.ru)
 */

#include <Modules/Rover_Control/rover_control.h>
#include <Modules/Time/time.h>
#include <Modules/Time/timer.h>
#include <Modules/UART/uart.h>
#include <Modules/I2C/i2c.h>
#include <Modules/MPU6050/mpu6050.h>
#include <Modules/HMC/hmc.h>
#include <Modules/MAVLink/common/mavlink.h>
#include <Modules/MAVLink/handlers.h>
#include <Modules/MAVLink/system.h>
#include <Modules/Parameters_Holder/param_holder.h>

#include <Helpers/sys_helper/sys_helper.h>

#include <hal.h>
#include <MC_hw_platform.h>
#include <m2sxxx.h>

#include <defines.h>

void setup(void);

int main(void) {
    // Modules initialisation
    setup();

    uint8_t rx_c;

    mavlink_message_t msg;
    mavlink_status_t status;

    while (1) {
        delay(1000);
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

        if (bt_get_rx(&rx_c, 1)) {
            if (mavlink_parse_char(MAVLINK_COMM_0, rx_c, &msg, &status)) {
                handle_mavlink_message(&msg);
            }
            param_queued_send_routine();
        }
    }
    return (0);
}

void setup() {
    rover_init();
    timers_init();
    uart_init();
    i2c_init();
    mavlink_sys_update(MAV_MODE_AUTO_ARMED, MAV_STATE_STANDBY);
    timer_mss1_start();
#ifdef MPU6050_ENABLED
    mpu6050_init();
#ifdef MPU6050_SELFTEST
    if (mpu6050_selfTest()) {
        mavlink_message_t msg;

        // TODO retcode into msg
        mavlink_msg_statustext_pack(
                mavlink_system.sysid,
                mavlink_system.compid,
                &msg,
                MAV_SEVERITY_CRITICAL,
                "MPU6050 SELFTEST FAILED");
        mavlink_send_msg(&msg);
    }
#endif // MPU6050_SELFTEST
    mpu6050_calibration();
#endif // MPU6050_ENABLED
#ifdef HMC_ENABLED
    HMC_init();
#ifdef HMC_SELFTEST
    if (HMC_self_test()) {
        mavlink_message_t msg;

        // TODO retcode into msg
        mavlink_msg_statustext_pack(
                mavlink_system.sysid,
                mavlink_system.compid,
                &msg,
                MAV_SEVERITY_CRITICAL,
                "HMC SELFTEST FAILED");
        mavlink_send_msg(&msg);
    }
#endif // HMC_SELFTEST
#endif // HMC_ENABLED
    timer_mss2_start();
}


