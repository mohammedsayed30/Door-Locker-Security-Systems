################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../app2.c \
../app2_functions.c \
../buzzer.c \
../dc_motor.c \
../eeprom.c \
../gpio.c \
../i2c.c \
../pwm.c \
../timer1.c \
../urat.c 

OBJS += \
./app2.o \
./app2_functions.o \
./buzzer.o \
./dc_motor.o \
./eeprom.o \
./gpio.o \
./i2c.o \
./pwm.o \
./timer1.o \
./urat.o 

C_DEPS += \
./app2.d \
./app2_functions.d \
./buzzer.d \
./dc_motor.d \
./eeprom.d \
./gpio.d \
./i2c.d \
./pwm.d \
./timer1.d \
./urat.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


