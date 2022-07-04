################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/projects/mechanical_arm/Firmware/CarLocateUWB_Base/libraries/sdk/Core/core_riscv.c 

OBJS += \
./sdk/Core/core_riscv.o 

C_DEPS += \
./sdk/Core/core_riscv.d 


# Each subdirectory must supply rules for building sources it contributes
sdk/Core/core_riscv.o: D:/projects/mechanical_arm/Firmware/CarLocateUWB_Base/libraries/sdk/Core/core_riscv.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\CarLocateUWB_Base\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\CarLocateUWB_Base\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\CarLocateUWB_Base\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\CarLocateUWB_Base\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\CarLocateUWB_Base\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\CarLocateUWB_Base\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\CarLocateUWB_Base\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\CarLocateUWB_Base\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\CarLocateUWB_Base\project\code" -I"D:\projects\mechanical_arm\Firmware\CarLocateUWB_Base\libraries\zf_driver" -I"C:\user\VScode\MinGW\include" -I"D:\projects\mechanical_arm\Firmware\CarLocateUWB_Base\decadriver" -I"D:\projects\mechanical_arm\Firmware\CarLocateUWB_Base\platform" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

