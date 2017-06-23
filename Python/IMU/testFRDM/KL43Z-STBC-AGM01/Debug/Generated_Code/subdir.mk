################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/Cpu.c \
../Generated_Code/DbgCs1.c \
../Generated_Code/WAIT1.c \
../Generated_Code/clockMan1.c \
../Generated_Code/gpio1.c \
../Generated_Code/hardware_init.c \
../Generated_Code/i2cCom1.c \
../Generated_Code/osa1.c \
../Generated_Code/pin_init.c 

OBJS += \
./Generated_Code/Cpu.o \
./Generated_Code/DbgCs1.o \
./Generated_Code/WAIT1.o \
./Generated_Code/clockMan1.o \
./Generated_Code/gpio1.o \
./Generated_Code/hardware_init.o \
./Generated_Code/i2cCom1.o \
./Generated_Code/osa1.o \
./Generated_Code/pin_init.o 

C_DEPS += \
./Generated_Code/Cpu.d \
./Generated_Code/DbgCs1.d \
./Generated_Code/WAIT1.d \
./Generated_Code/clockMan1.d \
./Generated_Code/gpio1.d \
./Generated_Code/hardware_init.d \
./Generated_Code/i2cCom1.d \
./Generated_Code/osa1.d \
./Generated_Code/pin_init.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -D"FSL_OSA_BM_TIMER_CONFIG=2" -D"CPU_MKL43Z256VLH4" -I"C:/Users/brao/workspace.kds/KDS3.0/KL43Z-STBC-AGM01/SDK/platform/hal/inc" -I"C:/Users/brao/workspace.kds/KDS3.0/KL43Z-STBC-AGM01/SDK/platform/hal/src/sim/MKL43Z4" -I"C:/Users/brao/workspace.kds/KDS3.0/KL43Z-STBC-AGM01/SDK/platform/system/src/clock/MKL43Z4" -I"C:/Users/brao/workspace.kds/KDS3.0/KL43Z-STBC-AGM01/SDK/platform/system/inc" -I"C:/Users/brao/workspace.kds/KDS3.0/KL43Z-STBC-AGM01/SDK/platform/osa/inc" -I"C:/Users/brao/workspace.kds/KDS3.0/KL43Z-STBC-AGM01/SDK/platform/CMSIS/Include" -I"C:/Users/brao/workspace.kds/KDS3.0/KL43Z-STBC-AGM01/SDK/platform/devices" -I"C:/Users/brao/workspace.kds/KDS3.0/KL43Z-STBC-AGM01/SDK/platform/devices/MKL43Z4/include" -I"C:/Users/brao/workspace.kds/KDS3.0/KL43Z-STBC-AGM01/SDK/platform/devices/MKL43Z4/startup" -I"C:/Users/brao/workspace.kds/KDS3.0/KL43Z-STBC-AGM01/Generated_Code/SDK/platform/devices/MKL43Z4/startup" -I"C:/Users/brao/workspace.kds/KDS3.0/KL43Z-STBC-AGM01/Sources" -I"C:/Users/brao/workspace.kds/KDS3.0/KL43Z-STBC-AGM01/Generated_Code" -I"C:/Users/brao/workspace.kds/KDS3.0/KL43Z-STBC-AGM01/SDK/platform/utilities/inc" -I"C:/Users/brao/workspace.kds/KDS3.0/KL43Z-STBC-AGM01/SDK/platform/drivers/inc" -I"C:/Users/brao/workspace.kds/KDS3.0/KL43Z-STBC-AGM01/SDK/platform/utilities/src" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


