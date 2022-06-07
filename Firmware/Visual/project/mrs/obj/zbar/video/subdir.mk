################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/projects/mechanical_arm/Firmware/Visual/project/zbar/video/null.c \
D:/projects/mechanical_arm/Firmware/Visual/project/zbar/video/v4l1.c \
D:/projects/mechanical_arm/Firmware/Visual/project/zbar/video/v4l2.c \
D:/projects/mechanical_arm/Firmware/Visual/project/zbar/video/vfw.c 

OBJS += \
./zbar/video/null.o \
./zbar/video/v4l1.o \
./zbar/video/v4l2.o \
./zbar/video/vfw.o 

C_DEPS += \
./zbar/video/null.d \
./zbar/video/v4l1.d \
./zbar/video/v4l2.d \
./zbar/video/vfw.d 


# Each subdirectory must supply rules for building sources it contributes
zbar/video/null.o: D:/projects/mechanical_arm/Firmware/Visual/project/zbar/video/null.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\Visual\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\Visual\project\zbar" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\Visual\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\Visual\project\code" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zbar/video/v4l1.o: D:/projects/mechanical_arm/Firmware/Visual/project/zbar/video/v4l1.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\Visual\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\Visual\project\zbar" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\Visual\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\Visual\project\code" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zbar/video/v4l2.o: D:/projects/mechanical_arm/Firmware/Visual/project/zbar/video/v4l2.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\Visual\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\Visual\project\zbar" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\Visual\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\Visual\project\code" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zbar/video/vfw.o: D:/projects/mechanical_arm/Firmware/Visual/project/zbar/video/vfw.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\Visual\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\Visual\project\zbar" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\Visual\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\Visual\project\code" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

