################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Startup/startup_stm32f303k8tx.s 

OBJS += \
./Startup/startup_stm32f303k8tx.o 

S_DEPS += \
./Startup/startup_stm32f303k8tx.d 


# Each subdirectory must supply rules for building sources it contributes
Startup/%.o: ../Startup/%.s Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -c -I"C:/vrs/vrs_cv6_/HTS221" -I"C:/vrs/vrs_cv6_/LPS25HB" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Startup

clean-Startup:
	-$(RM) ./Startup/startup_stm32f303k8tx.d ./Startup/startup_stm32f303k8tx.o

.PHONY: clean-Startup

