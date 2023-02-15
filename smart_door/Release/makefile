################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Door/MCAL/UART/subdir.mk
-include Door/MCAL/DIO/subdir.mk
-include Door/HAL/keypad/subdir.mk
-include Door/HAL/LCD/subdir.mk
-include Door/APP/main/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
smart_door.lss \

FLASH_IMAGE += \
smart_door.hex \

EEPROM_IMAGE += \
smart_door.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: smart_door.elf secondary-outputs

# Tool invocations
smart_door.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,smart_door.map -mmcu=atmega32 -o "smart_door.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

smart_door.lss: smart_door.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S smart_door.elf  >"smart_door.lss"
	@echo 'Finished building: $@'
	@echo ' '

smart_door.hex: smart_door.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex smart_door.elf  "smart_door.hex"
	@echo 'Finished building: $@'
	@echo ' '

smart_door.eep: smart_door.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex smart_door.elf  "smart_door.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: smart_door.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 smart_door.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) smart_door.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
