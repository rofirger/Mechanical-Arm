################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/projects/mechanical_arm/Firmware/UWB/platform/deca_mutex.c \
D:/projects/mechanical_arm/Firmware/UWB/platform/deca_sleep.c \
D:/projects/mechanical_arm/Firmware/UWB/platform/deca_spi.c \
D:/projects/mechanical_arm/Firmware/UWB/platform/lcd.c \
D:/projects/mechanical_arm/Firmware/UWB/platform/port.c 

OBJS += \
./platform/deca_mutex.o \
./platform/deca_sleep.o \
./platform/deca_spi.o \
./platform/lcd.o \
./platform/port.o 

C_DEPS += \
./platform/deca_mutex.d \
./platform/deca_sleep.d \
./platform/deca_spi.d \
./platform/lcd.d \
./platform/port.d 


# Each subdirectory must supply rules for building sources it contributes
platform/deca_mutex.o: D:/projects/mechanical_arm/Firmware/UWB/platform/deca_mutex.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\UWB\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\UWB\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\UWB\project\code" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\zf_driver" -I"C:\user\VScode\MinGW\include" -I"D:\projects\mechanical_arm\Firmware\UWB\decadriver" -I"D:\projects\mechanical_arm\Firmware\UWB\platform" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
platform/deca_sleep.o: D:/projects/mechanical_arm/Firmware/UWB/platform/deca_sleep.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\UWB\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\UWB\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\UWB\project\code" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\zf_driver" -I"C:\user\VScode\MinGW\include" -I"D:\projects\mechanical_arm\Firmware\UWB\decadriver" -I"D:\projects\mechanical_arm\Firmware\UWB\platform" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
platform/deca_spi.o: D:/projects/mechanical_arm/Firmware/UWB/platform/deca_spi.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\UWB\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\UWB\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\UWB\project\code" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\zf_driver" -I"C:\user\VScode\MinGW\include" -I"D:\projects\mechanical_arm\Firmware\UWB\decadriver" -I"D:\projects\mechanical_arm\Firmware\UWB\platform" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
platform/lcd.o: D:/projects/mechanical_arm/Firmware/UWB/platform/lcd.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\UWB\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\UWB\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\UWB\project\code" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\zf_driver" -I"C:\user\VScode\MinGW\include" -I"D:\projects\mechanical_arm\Firmware\UWB\decadriver" -I"D:\projects\mechanical_arm\Firmware\UWB\platform" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
platform/port.o: D:/projects/mechanical_arm/Firmware/UWB/platform/port.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\UWB\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\UWB\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\UWB\project\code" -I"D:\projects\mechanical_arm\Firmware\UWB\libraries\zf_driver" -I"C:\user\VScode\MinGW\include" -I"D:\projects\mechanical_arm\Firmware\UWB\decadriver" -I"D:\projects\mechanical_arm\Firmware\UWB\platform" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

