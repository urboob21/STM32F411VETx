################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/Src/core_systick_delay.c \
../Driver/Src/stm32_clock.c \
../Driver/Src/stm32_delay_timer.c \
../Driver/Src/stm32_gpio_driver.c \
../Driver/Src/stm32_usart.c 

OBJS += \
./Driver/Src/core_systick_delay.o \
./Driver/Src/stm32_clock.o \
./Driver/Src/stm32_delay_timer.o \
./Driver/Src/stm32_gpio_driver.o \
./Driver/Src/stm32_usart.o 

C_DEPS += \
./Driver/Src/core_systick_delay.d \
./Driver/Src/stm32_clock.d \
./Driver/Src/stm32_delay_timer.d \
./Driver/Src/stm32_gpio_driver.d \
./Driver/Src/stm32_usart.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/Src/%.o Driver/Src/%.su: ../Driver/Src/%.c Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F411VETx -DSTM32 -DSTM32F4 -c -I../Inc -I"D:/nWorld/8_CubexIDE/STM32F4_base/Driver/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Driver-2f-Src

clean-Driver-2f-Src:
	-$(RM) ./Driver/Src/core_systick_delay.d ./Driver/Src/core_systick_delay.o ./Driver/Src/core_systick_delay.su ./Driver/Src/stm32_clock.d ./Driver/Src/stm32_clock.o ./Driver/Src/stm32_clock.su ./Driver/Src/stm32_delay_timer.d ./Driver/Src/stm32_delay_timer.o ./Driver/Src/stm32_delay_timer.su ./Driver/Src/stm32_gpio_driver.d ./Driver/Src/stm32_gpio_driver.o ./Driver/Src/stm32_gpio_driver.su ./Driver/Src/stm32_usart.d ./Driver/Src/stm32_usart.o ./Driver/Src/stm32_usart.su

.PHONY: clean-Driver-2f-Src

