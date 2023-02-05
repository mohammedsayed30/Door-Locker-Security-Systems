################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LCD.c \
../app1.c \
../app1_functions.c \
../gpio.c \
../keypad.c \
../timer1.c \
../urat.c 

OBJS += \
./LCD.o \
./app1.o \
./app1_functions.o \
./gpio.o \
./keypad.o \
./timer1.o \
./urat.o 

C_DEPS += \
./LCD.d \
./app1.d \
./app1_functions.d \
./gpio.d \
./keypad.d \
./timer1.d \
./urat.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


