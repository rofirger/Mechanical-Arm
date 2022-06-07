################################################################################
# �Զ����ɵ��ļ�����Ҫ�༭��
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_driver/zf_driver_adc.c \
D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_driver/zf_driver_delay.c \
D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_driver/zf_driver_dvp.c \
D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_driver/zf_driver_encoder.c \
D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_driver/zf_driver_exti.c \
D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_driver/zf_driver_flash.c \
D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_driver/zf_driver_gpio.c \
D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_driver/zf_driver_pit.c \
D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_driver/zf_driver_pwm.c \
D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_driver/zf_driver_soft_iic.c \
D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_driver/zf_driver_spi.c \
D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_driver/zf_driver_timer.c \
D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_driver/zf_driver_uart.c \
D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_driver/zf_driver_usb_cdc.c 

S_UPPER_SRCS += \
D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_driver/zf_driver_irq.S 

OBJS += \
./zf_driver/zf_driver_adc.o \
./zf_driver/zf_driver_delay.o \
./zf_driver/zf_driver_dvp.o \
./zf_driver/zf_driver_encoder.o \
./zf_driver/zf_driver_exti.o \
./zf_driver/zf_driver_flash.o \
./zf_driver/zf_driver_gpio.o \
./zf_driver/zf_driver_irq.o \
./zf_driver/zf_driver_pit.o \
./zf_driver/zf_driver_pwm.o \
./zf_driver/zf_driver_soft_iic.o \
./zf_driver/zf_driver_spi.o \
./zf_driver/zf_driver_timer.o \
./zf_driver/zf_driver_uart.o \
./zf_driver/zf_driver_usb_cdc.o 

S_UPPER_DEPS += \
./zf_driver/zf_driver_irq.d 

C_DEPS += \
./zf_driver/zf_driver_adc.d \
./zf_driver/zf_driver_delay.d \
./zf_driver/zf_driver_dvp.d \
./zf_driver/zf_driver_encoder.d \
./zf_driver/zf_driver_exti.d \
./zf_driver/zf_driver_flash.d \
./zf_driver/zf_driver_gpio.d \
./zf_driver/zf_driver_pit.d \
./zf_driver/zf_driver_pwm.d \
./zf_driver/zf_driver_soft_iic.d \
./zf_driver/zf_driver_spi.d \
./zf_driver/zf_driver_timer.d \
./zf_driver/zf_driver_uart.d \
./zf_driver/zf_driver_usb_cdc.d 


# Each subdirectory must supply rules for building sources it contributes
zf_driver/zf_driver_adc.o: D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_driver/zf_driver_adc.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\Libraries\doc" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Core" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Ld" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Peripheral" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Startup" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\project\user\inc" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_common" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_device" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\project\code" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_delay.o: D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_driver/zf_driver_delay.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\Libraries\doc" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Core" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Ld" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Peripheral" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Startup" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\project\user\inc" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_common" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_device" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\project\code" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_dvp.o: D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_driver/zf_driver_dvp.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\Libraries\doc" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Core" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Ld" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Peripheral" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Startup" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\project\user\inc" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_common" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_device" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\project\code" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_encoder.o: D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_driver/zf_driver_encoder.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\Libraries\doc" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Core" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Ld" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Peripheral" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Startup" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\project\user\inc" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_common" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_device" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\project\code" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_exti.o: D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_driver/zf_driver_exti.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\Libraries\doc" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Core" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Ld" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Peripheral" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Startup" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\project\user\inc" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_common" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_device" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\project\code" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_flash.o: D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_driver/zf_driver_flash.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\Libraries\doc" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Core" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Ld" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Peripheral" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Startup" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\project\user\inc" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_common" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_device" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\project\code" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_gpio.o: D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_driver/zf_driver_gpio.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\Libraries\doc" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Core" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Ld" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Peripheral" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Startup" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\project\user\inc" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_common" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_device" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\project\code" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_irq.o: D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_driver/zf_driver_irq.S
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -x assembler -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Startup" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_driver" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_pit.o: D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_driver/zf_driver_pit.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\Libraries\doc" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Core" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Ld" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Peripheral" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Startup" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\project\user\inc" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_common" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_device" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\project\code" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_pwm.o: D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_driver/zf_driver_pwm.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\Libraries\doc" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Core" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Ld" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Peripheral" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Startup" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\project\user\inc" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_common" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_device" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\project\code" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_soft_iic.o: D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_driver/zf_driver_soft_iic.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\Libraries\doc" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Core" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Ld" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Peripheral" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Startup" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\project\user\inc" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_common" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_device" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\project\code" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_spi.o: D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_driver/zf_driver_spi.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\Libraries\doc" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Core" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Ld" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Peripheral" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Startup" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\project\user\inc" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_common" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_device" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\project\code" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_timer.o: D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_driver/zf_driver_timer.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\Libraries\doc" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Core" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Ld" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Peripheral" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Startup" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\project\user\inc" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_common" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_device" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\project\code" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_uart.o: D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_driver/zf_driver_uart.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\Libraries\doc" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Core" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Ld" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Peripheral" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Startup" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\project\user\inc" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_common" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_device" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\project\code" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_usb_cdc.o: D:/����/ch32v307_core_board/CarMainControl/CarMainControl/libraries/zf_driver/zf_driver_usb_cdc.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\Libraries\doc" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Core" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Ld" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Peripheral" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\sdk\Startup" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\project\user\inc" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_common" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_device" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\project\code" -I"D:\����\ch32v307_core_board\CarMainControl\CarMainControl\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

