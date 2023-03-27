################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Users/Src/clock.c \
../Users/Src/gpio.c \
../Users/Src/motor.c \
../Users/Src/pid.c \
../Users/Src/tim.c \
../Users/Src/usart.c 

OBJS += \
./Users/Src/clock.o \
./Users/Src/gpio.o \
./Users/Src/motor.o \
./Users/Src/pid.o \
./Users/Src/tim.o \
./Users/Src/usart.o 

C_DEPS += \
./Users/Src/clock.d \
./Users/Src/gpio.d \
./Users/Src/motor.d \
./Users/Src/pid.d \
./Users/Src/tim.d \
./Users/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Users/Src/%.o Users/Src/%.su: ../Users/Src/%.c Users/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I"D:/nWorld/1_0_STM32/Projects/2_Name/MOTOR/Users/Inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Users-2f-Src

clean-Users-2f-Src:
	-$(RM) ./Users/Src/clock.d ./Users/Src/clock.o ./Users/Src/clock.su ./Users/Src/gpio.d ./Users/Src/gpio.o ./Users/Src/gpio.su ./Users/Src/motor.d ./Users/Src/motor.o ./Users/Src/motor.su ./Users/Src/pid.d ./Users/Src/pid.o ./Users/Src/pid.su ./Users/Src/tim.d ./Users/Src/tim.o ./Users/Src/tim.su ./Users/Src/usart.d ./Users/Src/usart.o ./Users/Src/usart.su

.PHONY: clean-Users-2f-Src

