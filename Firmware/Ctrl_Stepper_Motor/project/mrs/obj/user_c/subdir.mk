################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/projects/mechanical_arm/Firmware/Ctrl_Stepper_Motor/project/user/src/MT6816.c \
D:/projects/mechanical_arm/Firmware/Ctrl_Stepper_Motor/project/user/src/Motor.c \
D:/projects/mechanical_arm/Firmware/Ctrl_Stepper_Motor/project/user/src/MyCan.c \
D:/projects/mechanical_arm/Firmware/Ctrl_Stepper_Motor/project/user/src/isr.c \
D:/projects/mechanical_arm/Firmware/Ctrl_Stepper_Motor/project/user/src/main.c \
D:/projects/mechanical_arm/Firmware/Ctrl_Stepper_Motor/project/user/src/msg_process.c 

OBJS += \
./user_c/MT6816.o \
./user_c/Motor.o \
./user_c/MyCan.o \
./user_c/isr.o \
./user_c/main.o \
./user_c/msg_process.o 

C_DEPS += \
./user_c/MT6816.d \
./user_c/Motor.d \
./user_c/MyCan.d \
./user_c/isr.d \
./user_c/main.d \
./user_c/msg_process.d 


# Each subdirectory must supply rules for building sources it contributes
user_c/MT6816.o: D:/projects/mechanical_arm/Firmware/Ctrl_Stepper_Motor/project/user/src/MT6816.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\project\code" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/Motor.o: D:/projects/mechanical_arm/Firmware/Ctrl_Stepper_Motor/project/user/src/Motor.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\project\code" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/MyCan.o: D:/projects/mechanical_arm/Firmware/Ctrl_Stepper_Motor/project/user/src/MyCan.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\project\code" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/isr.o: D:/projects/mechanical_arm/Firmware/Ctrl_Stepper_Motor/project/user/src/isr.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\project\code" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/main.o: D:/projects/mechanical_arm/Firmware/Ctrl_Stepper_Motor/project/user/src/main.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\project\code" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/msg_process.o: D:/projects/mechanical_arm/Firmware/Ctrl_Stepper_Motor/project/user/src/msg_process.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\project\code" -I"D:\projects\mechanical_arm\Firmware\Ctrl_Stepper_Motor\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

