################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/projects/mechanical_arm/Firmware/CarLocateUWB_Tag/decadriver/deca_device.c \
D:/projects/mechanical_arm/Firmware/CarLocateUWB_Tag/decadriver/deca_params_init.c 

OBJS += \
./decadriver/deca_device.o \
./decadriver/deca_params_init.o 

C_DEPS += \
./decadriver/deca_device.d \
./decadriver/deca_params_init.d 


# Each subdirectory must supply rules for building sources it contributes
decadriver/deca_device.o: D:/projects/mechanical_arm/Firmware/CarLocateUWB_Tag/decadriver/deca_device.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\CarLocateUWB_Tag\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\CarLocateUWB_Tag\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\CarLocateUWB_Tag\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\CarLocateUWB_Tag\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\CarLocateUWB_Tag\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\CarLocateUWB_Tag\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\CarLocateUWB_Tag\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\CarLocateUWB_Tag\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\CarLocateUWB_Tag\project\code" -I"D:\projects\mechanical_arm\Firmware\CarLocateUWB_Tag\libraries\zf_driver" -I"C:\user\VScode\MinGW\include" -I"D:\projects\mechanical_arm\Firmware\CarLocateUWB_Tag\decadriver" -I"D:\projects\mechanical_arm\Firmware\CarLocateUWB_Tag\platform" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
decadriver/deca_params_init.o: D:/projects/mechanical_arm/Firmware/CarLocateUWB_Tag/decadriver/deca_params_init.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\CarLocateUWB_Tag\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\CarLocateUWB_Tag\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\CarLocateUWB_Tag\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\CarLocateUWB_Tag\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\CarLocateUWB_Tag\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\CarLocateUWB_Tag\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\CarLocateUWB_Tag\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\CarLocateUWB_Tag\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\CarLocateUWB_Tag\project\code" -I"D:\projects\mechanical_arm\Firmware\CarLocateUWB_Tag\libraries\zf_driver" -I"C:\user\VScode\MinGW\include" -I"D:\projects\mechanical_arm\Firmware\CarLocateUWB_Tag\decadriver" -I"D:\projects\mechanical_arm\Firmware\CarLocateUWB_Tag\platform" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

