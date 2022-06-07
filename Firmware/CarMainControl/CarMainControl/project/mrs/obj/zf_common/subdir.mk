################################################################################
# �Զ����ɵ��ļ�����Ҫ�༭��
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_common/zf_common_clock.c \
D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_common/zf_common_debug.c \
D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_common/zf_common_fifo.c \
D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_common/zf_common_font.c \
D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_common/zf_common_function.c \
D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_common/zf_common_interrupt.c 

OBJS += \
./zf_common/zf_common_clock.o \
./zf_common/zf_common_debug.o \
./zf_common/zf_common_fifo.o \
./zf_common/zf_common_font.o \
./zf_common/zf_common_function.o \
./zf_common/zf_common_interrupt.o 

C_DEPS += \
./zf_common/zf_common_clock.d \
./zf_common/zf_common_debug.d \
./zf_common/zf_common_fifo.d \
./zf_common/zf_common_font.d \
./zf_common/zf_common_function.d \
./zf_common/zf_common_interrupt.d 


# Each subdirectory must supply rules for building sources it contributes
zf_common/zf_common_clock.o: D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_common/zf_common_clock.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\Libraries\doc" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Core" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Ld" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Peripheral" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Startup" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\project\user\inc" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_common" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_device" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\project\code" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_debug.o: D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_common/zf_common_debug.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\Libraries\doc" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Core" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Ld" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Peripheral" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Startup" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\project\user\inc" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_common" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_device" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\project\code" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_fifo.o: D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_common/zf_common_fifo.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\Libraries\doc" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Core" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Ld" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Peripheral" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Startup" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\project\user\inc" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_common" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_device" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\project\code" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_font.o: D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_common/zf_common_font.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\Libraries\doc" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Core" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Ld" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Peripheral" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Startup" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\project\user\inc" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_common" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_device" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\project\code" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_function.o: D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_common/zf_common_function.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\Libraries\doc" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Core" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Ld" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Peripheral" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Startup" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\project\user\inc" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_common" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_device" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\project\code" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_interrupt.o: D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_common/zf_common_interrupt.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\Libraries\doc" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Core" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Ld" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Peripheral" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Startup" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\project\user\inc" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_common" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_device" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\project\code" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

