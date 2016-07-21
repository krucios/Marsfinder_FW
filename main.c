/*
 * main.c
 *
 *  Created on: 14 февр. 2016 г.
 *      Author: kruci_000
 */

#include <Modules/Time/time.h>
#include <Modules/UART/uart.h>
#include <Modules/I2C/i2c.h>
#include <Modules/MPU6050/mpu6050.h>
#include <Modules/HMC/hmc.h>
#include <Modules/MAVLink/common/mavlink.h>
#include <Modules/MAVLink/handlers.h>
#include <Modules/MAVLink/system.h>
#include <Modules/AHRS/MadgwickAHRS.h>
#include <Modules/Parameters_Holder/param_holder.h>

#include <Helpers/sys_helper/sys_helper.h>
#include <Helpers/conversion_defines.h>

#include <hal.h>
#include <MC_hw_platform.h>
#include <m2sxxx.h>

#include <drivers_config/sys_config/sys_config.h>
#include <drivers/mss_timer/mss_timer.h>

#include <stdio.h>

void setup(void);

int main(void) {
    setup();

    uint8_t buff[80];
    uint32_t size;

    uint8_t rx_c;

    mavlink_message_t msg;
    mavlink_status_t status;

    while (1) {
        delay(1000);

        MPU6050_getScaledData(&params.param[PARAM_AX],
                              &params.param[PARAM_AY],
                              &params.param[PARAM_AZ],
                              &params.param[PARAM_GX],
                              &params.param[PARAM_GY],
                              &params.param[PARAM_GZ],
                              &params.param[PARAM_T]);
/* HMC isn't working now
        HMC_get_scaled_Data(&params.param[PARAM_MX],
                            &params.param[PARAM_MY],
                            &params.param[PARAM_MZ]);
*/
        UART_get_rx(&g_bt, &rx_c, 1);
        if (mavlink_parse_char(MAVLINK_COMM_0, rx_c, &msg, &status)) {
            handle_mavlink_message(&msg);
        }
        param_queued_send_routine();
    }
    return 0;
}

/*------------------------------------------------------------------------------
 * Service the I2C timeout functionality.
 */
void SysTick_Handler(void) {
    I2C_system_tick(&g_core_i2c, 10);
}
void FabricIrq0_IRQHandler(void) {
    I2C_isr(&g_core_i2c);
}

void setup() {
    // Enable usec
    MSS_TIM1_init(MSS_TIMER_PERIODIC_MODE);
    MSS_TIM1_load_background(MSS_SYS_M3_CLK_FREQ / 20); // TODO Remove hardcode
    MSS_TIM1_start();
    MSS_TIM1_enable_irq();

    uart_init();
    i2c_init();
    mavlink_sys_update(MAV_MODE_AUTO_ARMED, MAV_STATE_STANDBY);
    MPU6050_init();
    // HMC_init();

    beta = 3.14159265358979f * (5.0f / 180.0f) * sqrt(3.0f / 4.0f);

    /*-------------------------------------------------------------------------
     * Initialize the system tick for 10mS operation or 1 tick every 100th of
     * a second and also make sure it is lower priority than the I2C IRQs.
     */
    NVIC_SetPriority(SysTick_IRQn, 0xFFu); /* Lowest possible priority */
    SysTick_Config(MSS_SYS_M3_CLK_FREQ / 100);
}

void Timer1_IRQHandler() {
    mavlink_message_t msg;

    mavlink_msg_heartbeat_pack(
            mavlink_system.sysid,
            mavlink_system.compid,
            &msg,
            MAV_TYPE_GROUND_ROVER,
            MAV_AUTOPILOT_GENERIC,
            mavlink_sys_mode,
            0,
            mavlink_sys_state);
    mavlink_send_msg(&msg);

    mavlink_msg_sys_status_pack(
            mavlink_system.sysid,
            mavlink_system.compid,
            &msg,
            MAV_SYS_STATUS_SENSOR_3D_GYRO
            | MAV_SYS_STATUS_SENSOR_3D_ACCEL
            | MAV_SYS_STATUS_SENSOR_3D_MAG
            | MAV_SYS_STATUS_SENSOR_ABSOLUTE_PRESSURE
            | MAV_SYS_STATUS_SENSOR_GPS,
            MAV_SYS_STATUS_SENSOR_3D_GYRO
            | MAV_SYS_STATUS_SENSOR_3D_ACCEL
            | MAV_SYS_STATUS_SENSOR_3D_MAG,
            MAV_SYS_STATUS_SENSOR_3D_GYRO
            | MAV_SYS_STATUS_SENSOR_3D_ACCEL
            | MAV_SYS_STATUS_SENSOR_3D_MAG
            | MAV_SYS_STATUS_SENSOR_ABSOLUTE_PRESSURE
            | MAV_SYS_STATUS_SENSOR_GPS,
            50,                             // TODO remove hardoded values
            0,
            -1,
            -1,
            0,
            0,
            0,
            0,
            0,
            0);
    mavlink_send_msg(&msg);

    mavlink_msg_autopilot_version_pack(
            mavlink_system.sysid,
            mavlink_system.compid,
            &msg,
            0, // No capabilities (MAV_PROTOCOL_CAPABILITY). TBD
            42,
            42,
            42,
            42,
            "DEADBEEF",
            "DEADBEEF",
            "DEADBEEF",
            42,
            42,
            42);
    mavlink_send_msg(&msg);

    mavlink_msg_highres_imu_pack(
            mavlink_system.sysid,
            mavlink_system.compid,
            &msg,
            usec(),
            params.param[PARAM_AX],
            params.param[PARAM_AY],
            params.param[PARAM_AZ],
            params.param[PARAM_GX],
            params.param[PARAM_GY],
            params.param[PARAM_GZ],
            params.param[PARAM_MX],
            params.param[PARAM_MY],
            params.param[PARAM_MZ],
            0,
            0,
            0,
            params.param[PARAM_T],
            (1 << 12) | ((1 << 9) - 1));
    mavlink_send_msg(&msg);

    mavlink_msg_attitude_quaternion_pack(
            mavlink_system.sysid,
            mavlink_system.compid,
            &msg,
            usec(),
            q0,
            q1,
            q2,
            q3,
            params.param[PARAM_GX] * DEG_TO_RAD,
            params.param[PARAM_GY] * DEG_TO_RAD,
            params.param[PARAM_GZ] * DEG_TO_RAD);
    mavlink_send_msg(&msg);

    MadgwickAHRSupdateIMU(params.param[PARAM_GX] * DEG_TO_RAD,
                          params.param[PARAM_GY] * DEG_TO_RAD,
                          params.param[PARAM_GZ] * DEG_TO_RAD,
                          params.param[PARAM_AX],
                          params.param[PARAM_AY],
                          params.param[PARAM_AZ]);

    usec_service_routine();

    MSS_TIM1_clear_irq();
}


