#include "hal.h"
#include "hal_assert.h"
#include "core_i2c.h"
#include "../CMSIS/m2sxxx.h"

extern i2c_instance_t g_core_i2c;

/*------------------------------------------------------------------------------
 * This function must be modified to enable interrupts generated from the
 * CoreI2C instance identified as parameter.
 */
void I2C_enable_irq( i2c_instance_t * this_i2c )
{
    if(this_i2c == &g_core_i2c)
    {
        NVIC_EnableIRQ( FabricIrq0_IRQn );
    }
}

/*------------------------------------------------------------------------------
 * This function must be modified to disable interrupts generated from the
 * CoreI2C instance identified as parameter.
 */
void I2C_disable_irq( i2c_instance_t * this_i2c )
{
    if(this_i2c == &g_core_i2c)
    {
         NVIC_DisableIRQ( FabricIrq0_IRQn );
    }
}

