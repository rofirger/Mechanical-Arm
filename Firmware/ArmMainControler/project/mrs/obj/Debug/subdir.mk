################################################################################
# �Զ����ɵ��ļ�����Ҫ�༭��
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/projects/mechanical_arm/Firmware/ArmMainControler/Debug/debug.c 

OBJS += \
./Debug/debug.o 

C_DEPS += \
./Debug/debug.d 


# Each subdirectory must supply rules for building sources it contributes
Debug/debug.o: D:/projects/mechanical_arm/Firmware/ArmMainControler/Debug/debug.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\Debug" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\NetLib" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\project\code" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

