################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SDK/platform/system/src/clock/fsl_clock_manager.c \
../SDK/platform/system/src/clock/fsl_clock_manager_common.c 

OBJS += \
./SDK/platform/system/src/clock/fsl_clock_manager.o \
./SDK/platform/system/src/clock/fsl_clock_manager_common.o 

C_DEPS += \
./SDK/platform/system/src/clock/fsl_clock_manager.d \
./SDK/platform/system/src/clock/fsl_clock_manager_common.d 


# Each subdirectory must supply rules for building sources it contributes
SDK/platform/system/src/clock/%.o: ../SDK/platform/system/src/clock/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -D"FSL_OSA_BM_TIMER_CONFIG=2" -D"CPU_MKL43Z256VLH4" -I"C:/Users/brao/workspace.kds/KDS3.0/KL43Z-STBC-AGM01/SDK/platform/hal/inc" -I"C:/Users/brao/workspace.kds/KDS3.0/KL43Z-STBC-AGM01/SDK/platform/hal/src/sim/MKL43Z4" -I"C:/Users/brao/workspace.kds/KDS3.0/KL43Z-STBC-AGM01/SDK/platform/system/src/clock/MKL43Z4" -I"C:/Users/brao/workspace.kds/KDS3.0/KL43Z-STBC-AGM01/SDK/platform/system/inc" -I"C:/Users/brao/workspace.kds/KDS3.0/KL43Z-STBC-AGM01/SDK/platform/osa/inc" -I"C:/Users/brao/workspace.kds/KDS3.0/KL43Z-STBC-AGM01/SDK/platform/CMSIS/Include" -I"C:/Users/brao/workspace.kds/KDS3.0/KL43Z-STBC-AGM01/SDK/platform/devices" -I"C:/Users/brao/workspace.kds/KDS3.0/KL43Z-STBC-AGM01/SDK/platform/devices/MKL43Z4/include" -I"C:/Users/brao/workspace.kds/KDS3.0/KL43Z-STBC-AGM01/SDK/platform/devices/MKL43Z4/startup" -I"C:/Users/brao/workspace.kds/KDS3.0/KL43Z-STBC-AGM01/Generated_Code/SDK/platform/devices/MKL43Z4/startup" -I"C:/Users/brao/workspace.kds/KDS3.0/KL43Z-STBC-AGM01/Sources" -I"C:/Users/brao/workspace.kds/KDS3.0/KL43Z-STBC-AGM01/Generated_Code" -I"C:/Users/brao/workspace.kds/KDS3.0/KL43Z-STBC-AGM01/SDK/platform/utilities/inc" -I"C:/Users/brao/workspace.kds/KDS3.0/KL43Z-STBC-AGM01/SDK/platform/drivers/inc" -I"C:/Users/brao/workspace.kds/KDS3.0/KL43Z-STBC-AGM01/SDK/platform/utilities/src" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


