################################################################################
# 自动生成的文件。不要编辑！
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include User/subdir.mk
-include Startup/subdir.mk
-include Peripheral/src/subdir.mk
-include Debug/subdir.mk
-include Core/subdir.mk
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
TcpClient.hex \

SECONDARY_LIST += \
TcpClient.lst \

SECONDARY_SIZE += \
TcpClient.siz \


# 所有目标
all: TcpClient.elf secondary-outputs

# 工具调用
TcpClient.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized  -g -T "D:\projects\mechanical_arm\ch32v307\EVT\EXAM\ETH\TcpClient\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -L"D:\projects\mechanical_arm\ch32v307\EVT\EXAM\ETH\NetLib" -Wl,-Map,"TcpClient.map" --specs=nano.specs --specs=nosys.specs  -o "TcpClient.elf" $(OBJS) $(USER_OBJS) $(LIBS) -lprintf
	@	@
TcpClient.hex: TcpClient.elf
	@	riscv-none-embed-objcopy -O ihex "TcpClient.elf"  "TcpClient.hex"
	@	@
TcpClient.lst: TcpClient.elf
	@	riscv-none-embed-objdump --source --all-headers --demangle --line-numbers --wide "TcpClient.elf" > "TcpClient.lst"
	@	@
TcpClient.siz: TcpClient.elf
	@	riscv-none-embed-size --format=berkeley "TcpClient.elf"
	@	@
# 其他目标
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) TcpClient.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
