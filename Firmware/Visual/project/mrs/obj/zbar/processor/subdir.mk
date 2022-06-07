################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/projects/mechanical_arm/Firmware/Visual/project/zbar/processor/lock.c \
D:/projects/mechanical_arm/Firmware/Visual/project/zbar/processor/null.c 

OBJS += \
./zbar/processor/lock.o \
./zbar/processor/null.o 

C_DEPS += \
./zbar/processor/lock.d \
./zbar/processor/null.d 


# Each subdirectory must supply rules for building sources it contributes
zbar/processor/lock.o: D:/projects/mechanical_arm/Firmware/Visual/project/zbar/processor/lock.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\Visual\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\Visual\project\zbar" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\Visual\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\Visual\project\code" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zbar/processor/null.o: D:/projects/mechanical_arm/Firmware/Visual/project/zbar/processor/null.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\Visual\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\Visual\project\zbar" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\Visual\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\Visual\project\code" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

