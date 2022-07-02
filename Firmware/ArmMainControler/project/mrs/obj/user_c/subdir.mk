################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/projects/mechanical_arm/Firmware/ArmMainControler/project/user/src/ETH.c \
D:/projects/mechanical_arm/Firmware/ArmMainControler/project/user/src/MyCan.c \
D:/projects/mechanical_arm/Firmware/ArmMainControler/project/user/src/arm_kinematic.c \
D:/projects/mechanical_arm/Firmware/ArmMainControler/project/user/src/isr.c \
D:/projects/mechanical_arm/Firmware/ArmMainControler/project/user/src/main.c \
D:/projects/mechanical_arm/Firmware/ArmMainControler/project/user/src/msg_process.c \
D:/projects/mechanical_arm/Firmware/ArmMainControler/project/user/src/w25q128.c 

OBJS += \
./user_c/ETH.o \
./user_c/MyCan.o \
./user_c/arm_kinematic.o \
./user_c/isr.o \
./user_c/main.o \
./user_c/msg_process.o \
./user_c/w25q128.o 

C_DEPS += \
./user_c/ETH.d \
./user_c/MyCan.d \
./user_c/arm_kinematic.d \
./user_c/isr.d \
./user_c/main.d \
./user_c/msg_process.d \
./user_c/w25q128.d 


# Each subdirectory must supply rules for building sources it contributes
user_c/ETH.o: D:/projects/mechanical_arm/Firmware/ArmMainControler/project/user/src/ETH.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\NetLib" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\project\code" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/MyCan.o: D:/projects/mechanical_arm/Firmware/ArmMainControler/project/user/src/MyCan.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\NetLib" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\project\code" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/arm_kinematic.o: D:/projects/mechanical_arm/Firmware/ArmMainControler/project/user/src/arm_kinematic.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\NetLib" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\project\code" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/isr.o: D:/projects/mechanical_arm/Firmware/ArmMainControler/project/user/src/isr.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\NetLib" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\project\code" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/main.o: D:/projects/mechanical_arm/Firmware/ArmMainControler/project/user/src/main.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\NetLib" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\project\code" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/msg_process.o: D:/projects/mechanical_arm/Firmware/ArmMainControler/project/user/src/msg_process.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\NetLib" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\project\code" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/w25q128.o: D:/projects/mechanical_arm/Firmware/ArmMainControler/project/user/src/w25q128.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\NetLib" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\project\code" -I"D:\projects\mechanical_arm\Firmware\ArmMainControler\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

