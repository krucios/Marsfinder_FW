################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Modules/Time/time.c 

OBJS += \
./Modules/Time/time.o 

C_DEPS += \
./Modules/Time/time.d 


# Each subdirectory must supply rules for building sources it contributes
Modules/Time/%.o: ../Modules/Time/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:\Users\kruci_000\Desktop\University\SoC\Marsfinder\Marsfinder\Marsfinder_FW" -I"C:\Users\kruci_000\Desktop\University\SoC\Marsfinder\Marsfinder\Marsfinder_FW\hal\CortexM3\GNU" -I"C:\Users\kruci_000\Desktop\University\SoC\Marsfinder\Marsfinder\Marsfinder_FW\hal\CortexM3" -I"C:\Users\kruci_000\Desktop\University\SoC\Marsfinder\Marsfinder\Marsfinder_FW\CMSIS" -I"C:\Users\kruci_000\Desktop\University\SoC\Marsfinder\Marsfinder\Marsfinder_FW\hal" -I"C:\Users\kruci_000\Desktop\University\SoC\Marsfinder\Marsfinder\Marsfinder_FW\drivers" -std=gnu11 --specs=cmsis.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


