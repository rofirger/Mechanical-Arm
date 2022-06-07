################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/桌面/ch32v307_core_board/CarMainControl/CarMainControl/libraries/sdk/Core/core_riscv.c 

OBJS += \
./sdk/Core/core_riscv.o 

C_DEPS += \
./sdk/Core/core_riscv.d 


# Each subdirectory must supply rules for building sources it contributes
sdk/Core/core_riscv.o: D:/桌面/ch32v307_core_board/CarMainControl/CarMainControl/libraries/sdk/Core/core_riscv.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\桌面\ch32v307_core_board\CarMainControl\CarMainControl\Libraries\doc" -I"D:\桌面\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Core" -I"D:\桌面\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Ld" -I"D:\桌面\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Peripheral" -I"D:\桌面\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Startup" -I"D:\桌面\ch32v307_core_board\CarMainControl\CarMainControl\project\user\inc" -I"D:\桌面\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_common" -I"D:\桌面\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_device" -I"D:\桌面\ch32v307_core_board\CarMainControl\CarMainControl\project\code" -I"D:\桌面\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

