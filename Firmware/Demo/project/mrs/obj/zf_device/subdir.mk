################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/projects/mechanical_arm/Firmware/Demo/libraries/zf_device/zf_device_absolute_encoder.c \
D:/projects/mechanical_arm/Firmware/Demo/libraries/zf_device/zf_device_bluetooth_ch9141.c \
D:/projects/mechanical_arm/Firmware/Demo/libraries/zf_device/zf_device_bluetooth_ch9141_ch2.c \
D:/projects/mechanical_arm/Firmware/Demo/libraries/zf_device/zf_device_camera.c \
D:/projects/mechanical_arm/Firmware/Demo/libraries/zf_device/zf_device_icm20602.c \
D:/projects/mechanical_arm/Firmware/Demo/libraries/zf_device/zf_device_ips114.c \
D:/projects/mechanical_arm/Firmware/Demo/libraries/zf_device/zf_device_ips200_parallel8.c \
D:/projects/mechanical_arm/Firmware/Demo/libraries/zf_device/zf_device_mpu6050.c \
D:/projects/mechanical_arm/Firmware/Demo/libraries/zf_device/zf_device_mt9v03x_dvp.c \
D:/projects/mechanical_arm/Firmware/Demo/libraries/zf_device/zf_device_oled.c \
D:/projects/mechanical_arm/Firmware/Demo/libraries/zf_device/zf_device_scc8660_dvp.c \
D:/projects/mechanical_arm/Firmware/Demo/libraries/zf_device/zf_device_tft180.c \
D:/projects/mechanical_arm/Firmware/Demo/libraries/zf_device/zf_device_type.c \
D:/projects/mechanical_arm/Firmware/Demo/libraries/zf_device/zf_device_virtual_oscilloscope.c \
D:/projects/mechanical_arm/Firmware/Demo/libraries/zf_device/zf_device_wireless_ch573.c \
D:/projects/mechanical_arm/Firmware/Demo/libraries/zf_device/zf_device_wireless_uart.c 

OBJS += \
./zf_device/zf_device_absolute_encoder.o \
./zf_device/zf_device_bluetooth_ch9141.o \
./zf_device/zf_device_bluetooth_ch9141_ch2.o \
./zf_device/zf_device_camera.o \
./zf_device/zf_device_icm20602.o \
./zf_device/zf_device_ips114.o \
./zf_device/zf_device_ips200_parallel8.o \
./zf_device/zf_device_mpu6050.o \
./zf_device/zf_device_mt9v03x_dvp.o \
./zf_device/zf_device_oled.o \
./zf_device/zf_device_scc8660_dvp.o \
./zf_device/zf_device_tft180.o \
./zf_device/zf_device_type.o \
./zf_device/zf_device_virtual_oscilloscope.o \
./zf_device/zf_device_wireless_ch573.o \
./zf_device/zf_device_wireless_uart.o 

C_DEPS += \
./zf_device/zf_device_absolute_encoder.d \
./zf_device/zf_device_bluetooth_ch9141.d \
./zf_device/zf_device_bluetooth_ch9141_ch2.d \
./zf_device/zf_device_camera.d \
./zf_device/zf_device_icm20602.d \
./zf_device/zf_device_ips114.d \
./zf_device/zf_device_ips200_parallel8.d \
./zf_device/zf_device_mpu6050.d \
./zf_device/zf_device_mt9v03x_dvp.d \
./zf_device/zf_device_oled.d \
./zf_device/zf_device_scc8660_dvp.d \
./zf_device/zf_device_tft180.d \
./zf_device/zf_device_type.d \
./zf_device/zf_device_virtual_oscilloscope.d \
./zf_device/zf_device_wireless_ch573.d \
./zf_device/zf_device_wireless_uart.d 


# Each subdirectory must supply rules for building sources it contributes
zf_device/zf_device_absolute_encoder.o: D:/projects/mechanical_arm/Firmware/Demo/libraries/zf_device/zf_device_absolute_encoder.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\Demo\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\Demo\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\Demo\project\code" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_bluetooth_ch9141.o: D:/projects/mechanical_arm/Firmware/Demo/libraries/zf_device/zf_device_bluetooth_ch9141.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\Demo\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\Demo\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\Demo\project\code" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_bluetooth_ch9141_ch2.o: D:/projects/mechanical_arm/Firmware/Demo/libraries/zf_device/zf_device_bluetooth_ch9141_ch2.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\Demo\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\Demo\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\Demo\project\code" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_camera.o: D:/projects/mechanical_arm/Firmware/Demo/libraries/zf_device/zf_device_camera.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\Demo\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\Demo\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\Demo\project\code" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_icm20602.o: D:/projects/mechanical_arm/Firmware/Demo/libraries/zf_device/zf_device_icm20602.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\Demo\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\Demo\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\Demo\project\code" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_ips114.o: D:/projects/mechanical_arm/Firmware/Demo/libraries/zf_device/zf_device_ips114.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\Demo\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\Demo\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\Demo\project\code" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_ips200_parallel8.o: D:/projects/mechanical_arm/Firmware/Demo/libraries/zf_device/zf_device_ips200_parallel8.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\Demo\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\Demo\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\Demo\project\code" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_mpu6050.o: D:/projects/mechanical_arm/Firmware/Demo/libraries/zf_device/zf_device_mpu6050.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\Demo\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\Demo\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\Demo\project\code" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_mt9v03x_dvp.o: D:/projects/mechanical_arm/Firmware/Demo/libraries/zf_device/zf_device_mt9v03x_dvp.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\Demo\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\Demo\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\Demo\project\code" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_oled.o: D:/projects/mechanical_arm/Firmware/Demo/libraries/zf_device/zf_device_oled.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\Demo\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\Demo\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\Demo\project\code" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_scc8660_dvp.o: D:/projects/mechanical_arm/Firmware/Demo/libraries/zf_device/zf_device_scc8660_dvp.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\Demo\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\Demo\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\Demo\project\code" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_tft180.o: D:/projects/mechanical_arm/Firmware/Demo/libraries/zf_device/zf_device_tft180.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\Demo\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\Demo\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\Demo\project\code" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_type.o: D:/projects/mechanical_arm/Firmware/Demo/libraries/zf_device/zf_device_type.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\Demo\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\Demo\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\Demo\project\code" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_virtual_oscilloscope.o: D:/projects/mechanical_arm/Firmware/Demo/libraries/zf_device/zf_device_virtual_oscilloscope.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\Demo\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\Demo\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\Demo\project\code" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_wireless_ch573.o: D:/projects/mechanical_arm/Firmware/Demo/libraries/zf_device/zf_device_wireless_ch573.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\Demo\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\Demo\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\Demo\project\code" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_wireless_uart.o: D:/projects/mechanical_arm/Firmware/Demo/libraries/zf_device/zf_device_wireless_uart.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\Demo\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\Demo\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\Demo\project\code" -I"D:\projects\mechanical_arm\Firmware\Demo\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

