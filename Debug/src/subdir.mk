################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/_write.c \
../src/clock.c \
../src/main.c \
../src/relays.c \
../src/ring.c \
../src/usart_comm.c \
../src/usb_comm.c 

OBJS += \
./src/_write.o \
./src/clock.o \
./src/main.o \
./src/relays.o \
./src/ring.o \
./src/usart_comm.o \
./src/usb_comm.o 

C_DEPS += \
./src/_write.d \
./src/clock.d \
./src/main.d \
./src/relays.d \
./src/ring.d \
./src/usart_comm.d \
./src/usb_comm.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Werror -Wall -Wextra  -g3 -DSTM32F1 -I"../include" -isystem/home/jdr/Projects/stm32/libopencm3-examples/libopencm3/include -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


