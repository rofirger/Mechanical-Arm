################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/projects/mechanical_arm/Firmware/Visual/project/soft_compoment/06_SoftComponent/modelPredict.c \
D:/projects/mechanical_arm/Firmware/Visual/project/soft_compoment/06_SoftComponent/modelPreprocess.c \
D:/projects/mechanical_arm/Firmware/Visual/project/soft_compoment/06_SoftComponent/model_init.c 

OBJS += \
./soft_compoment/06_SoftComponent/modelPredict.o \
./soft_compoment/06_SoftComponent/modelPreprocess.o \
./soft_compoment/06_SoftComponent/model_init.o 

C_DEPS += \
./soft_compoment/06_SoftComponent/modelPredict.d \
./soft_compoment/06_SoftComponent/modelPreprocess.d \
./soft_compoment/06_SoftComponent/model_init.d 


# Each subdirectory must supply rules for building sources it contributes
soft_compoment/06_SoftComponent/modelPredict.o: D:/projects/mechanical_arm/Firmware/Visual/project/soft_compoment/06_SoftComponent/modelPredict.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\Visual\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\Visual\project\soft_compoment" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\Visual\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\Visual\project\code" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
soft_compoment/06_SoftComponent/modelPreprocess.o: D:/projects/mechanical_arm/Firmware/Visual/project/soft_compoment/06_SoftComponent/modelPreprocess.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\Visual\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\Visual\project\soft_compoment" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\Visual\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\Visual\project\code" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
soft_compoment/06_SoftComponent/model_init.o: D:/projects/mechanical_arm/Firmware/Visual/project/soft_compoment/06_SoftComponent/model_init.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\projects\mechanical_arm\Firmware\Visual\Libraries\doc" -I"D:\projects\mechanical_arm\Firmware\Visual\project\soft_compoment" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\sdk\Core" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\sdk\Ld" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\sdk\Peripheral" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\sdk\Startup" -I"D:\projects\mechanical_arm\Firmware\Visual\project\user\inc" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\zf_common" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\zf_device" -I"D:\projects\mechanical_arm\Firmware\Visual\project\code" -I"D:\projects\mechanical_arm\Firmware\Visual\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

