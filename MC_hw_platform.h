#ifndef MC_HW_PLATFORM_H_
#define MC_HW_PLATFORM_H_
/*****************************************************************************
*
*Created by Microsemi SmartDesign  Sat Mar 18 23:15:13 2017
*
*Memory map specification for peripherals in MC
*/

/*-----------------------------------------------------------------------------
* CM3 subsystem memory map
* Master(s) for this subsystem: CM3
*---------------------------------------------------------------------------*/
#define COREI2C_0_0                     0x50000000U
#define COREGPIO_0_0                    0x50001000U
#define CORETIMER_0_0                   0x50002000U
#define COREUARTAPB_0_0                 0x50003000U // BT
#define COREUARTAPB_0_1                 0x50004000U // US
#define COREUARTAPB_0_2                 0x50005000U // GPS
#define COREPWM_0_0                     0x50006000U


#endif /* MC_HW_PLATFORM_H_*/
