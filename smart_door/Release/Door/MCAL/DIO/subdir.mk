################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Door/MCAL/DIO/DIO.c 

OBJS += \
./Door/MCAL/DIO/DIO.o 

C_DEPS += \
./Door/MCAL/DIO/DIO.d 


# Each subdirectory must supply rules for building sources it contributes
Door/MCAL/DIO/%.o: ../Door/MCAL/DIO/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


