################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/projects/mechanical_arm/Firmware/UWB/project/user/src/isr.c \
D:/projects/mechanical_arm/Firmware/UWB/project/user/src/main.c 

OBJS += \
./user_c/isr.o \
./user_c/main.o 

C_DEPS += \
./user_c/isr.d \
./user_c/main.d 


# Each subdirectory must supply rules for building sources it contributes
user_c/isr.o: D:/projects/mechanical_arm/Firmware/UWB/project/user/src/isr.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\UWB\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\UWB\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\UWB\project\code" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\zf_driver" -I"C:\user\VScode\MinGW\include" -I"D:\projects\mechanical_arm\Firmware\UWB\decadriver" -I"D:\projects\mechanical_arm\Firmware\UWB\platform" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/main.o: D:/projects/mechanical_arm/Firmware/UWB/project/user/src/main.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\UWB\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\UWB\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\UWB\project\code" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\zf_driver" -I"C:\user\VScode\MinGW\include" -I"D:\projects\mechanical_arm\Firmware\UWB\decadriver" -I"D:\projects\mechanical_arm\Firmware\UWB\platform" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

