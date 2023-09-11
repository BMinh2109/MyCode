################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Components/Timer/pwm.cpp 

OBJS += \
./Components/Timer/pwm.o 

CPP_DEPS += \
./Components/Timer/pwm.d 


# Each subdirectory must supply rules for building sources it contributes
Components/Timer/%.o Components/Timer/%.su Components/Timer/%.cyclo: ../Components/Timer/%.cpp Components/Timer/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DSTM32G431xx -DUSE_FULL_LL_DRIVER -DHSE_VALUE=24000000 -DHSE_STARTUP_TIMEOUT=100 -DLSE_STARTUP_TIMEOUT=5000 -DLSE_VALUE=32768 -DEXTERNAL_CLOCK_VALUE=12288000 -DHSI_VALUE=16000000 -DLSI_VALUE=32000 -DVDD_VALUE=3300 -DPREFETCH_ENABLE=0 -DINSTRUCTION_CACHE_ENABLE=1 -DDATA_CACHE_ENABLE=1 -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I"D:/sharetech/Training/BlinkLED/Components" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Components-2f-Timer

clean-Components-2f-Timer:
	-$(RM) ./Components/Timer/pwm.cyclo ./Components/Timer/pwm.d ./Components/Timer/pwm.o ./Components/Timer/pwm.su

.PHONY: clean-Components-2f-Timer

