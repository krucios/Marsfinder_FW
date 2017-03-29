/*
 * timer_handlers.c
 *
 *  Created on: 21 Jul 2016
 *      Author: S2400105
 */

#include "time.h"
#include "timer.h"
#include "defines.h"

#include <Helpers/conversion_defines.h>

#include <Modules/I2C/i2c.h>
#include <Modules/Rover_Control/rover_control.h>
#include <Modules/Parameters_Holder/param_holder.h>
#include <Modules/MAVLink/common/mavlink.h>
#include <Modules/AHRS/MadgwickAHRS.h>
#include <Modules/MPU6050/mpu6050.h>
#include <Modules/HMC/hmc.h>

/*------------------------------------------------------------------------------
 * Service the I2C timeout functionality.
 */
void SysTick_Handler(void) {
    I2C_system_tick(&g_core_i2c, 10);
}
void FabricIrq0_IRQHandler(void) {
    I2C_isr(&g_core_i2c);
    PWM_tach_IRQHandler();
}

/*-----------------------------------------------------------------------------
 * Service MAVlink protocol message routine
 */
void Timer1_IRQHandler() {
    mavlink_message_t msg;

    MadgwickAHRSupdateIMU(params[PARAM_GX].val * DEG_TO_RAD,
                          params[PARAM_GY].val * DEG_TO_RAD,
                          params[PARAM_GZ].val * DEG_TO_RAD,
                          params[PARAM_AX].val,
                          params[PARAM_AY].val,
                          params[PARAM_AZ].val);

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
            params[PARAM_AX].val,
            params[PARAM_AY].val,
            params[PARAM_AZ].val,
            params[PARAM_GX].val,
            params[PARAM_GY].val,
            params[PARAM_GZ].val,
            params[PARAM_MX].val,
            params[PARAM_MY].val,
            params[PARAM_MZ].val,
            0,
            0,
            0,
            params[PARAM_T].val,
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
            params[PARAM_GX].val * DEG_TO_RAD,
            params[PARAM_GY].val * DEG_TO_RAD,
            params[PARAM_GZ].val * DEG_TO_RAD);
    mavlink_send_msg(&msg);

    usec_service_routine();

    MSS_TIM1_clear_irq();
}


/*-------------------------------------
 * Read values from sensors
 */
void Timer2_IRQHandler() {
    Rover_move_routine();
    MSS_TIM2_clear_irq();
}
