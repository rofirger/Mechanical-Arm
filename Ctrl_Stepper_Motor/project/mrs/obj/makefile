################################################################################
# 自动生成的文件。不要编辑！
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include zf_driver/subdir.mk
-include zf_device/subdir.mk
-include zf_common/subdir.mk
-include user_c/subdir.mk
-include sdk/Startup/subdir.mk
-include sdk/Peripheral/subdir.mk
-include sdk/Core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
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
SECONDARY_FLASH += \
Ctrl_Stepper_Motor.hex \

SECONDARY_LIST += \
Ctrl_Stepper_Motor.lst \

SECONDARY_SIZE += \
Ctrl_Stepper_Motor.siz \


# 所有目标
all: Ctrl_Stepper_Motor.elf secondary-outputs

# 工具调用
Ctrl_Stepper_Motor.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -T "D:\projects\mechanical_arm\Ctrl_Stepper_Motor\libraries\sdk\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -L"../" -Wl,-Map,"Ctrl_Stepper_Motor.map" --specs=nano.specs -u _printf_float --specs=nosys.specs -o "Ctrl_Stepper_Motor.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
Ctrl_Stepper_Motor.hex: Ctrl_Stepper_Motor.elf
	@	riscv-none-embed-objcopy -O ihex "Ctrl_Stepper_Motor.elf"  "Ctrl_Stepper_Motor.hex"
	@	@
Ctrl_Stepper_Motor.lst: Ctrl_Stepper_Motor.elf
	@	riscv-none-embed-objdump --source --all-headers --demangle --line-numbers --wide "Ctrl_Stepper_Motor.elf" > "Ctrl_Stepper_Motor.lst"
	@	@
Ctrl_Stepper_Motor.siz: Ctrl_Stepper_Motor.elf
	@	riscv-none-embed-size --format=berkeley "Ctrl_Stepper_Motor.elf"
	@	@
# 其他目标
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) Ctrl_Stepper_Motor.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
