/*
 * @致谢：感谢逐飞科技ch32V307开源库的支持
*/
/*
 *      @File: main.c
 *
 *      @Team: 删库跑路队
 *      @Author: 随风
 */
#include "Motor.h"
#include "headfile.h"
#include "MyCan.h"
#include "stdlib.h"
#include "msg_process.h"
#include "Motor.h"


/*
 * @note:控制驱动板上的LED闪烁
*/

volatile bool is_stop = false;
volatile bool is_start = false;

void Blink(uint16_t _times)
{
    static int i = 0;
    if (i >= _times)
    {
        gpio_toggle_level(INDICATOR);
        i = 0;
    }
    i++;
}

void Init()
{
    // 指示灯
    gpio_init(INDICATOR, GPO, 1, GPO_PUSH_PULL);
    // 初始化步进电机驱动GPIO输出引脚
    gpio_init(AP_STEP, GPO, GPIO_LOW, GPO_PUSH_PULL);
    gpio_init(AN_STEP, GPO, GPIO_LOW, GPO_PUSH_PULL);
    gpio_init(BP_STEP, GPO, GPIO_LOW, GPO_PUSH_PULL);
    gpio_init(BN_STEP, GPO, GPIO_LOW, GPO_PUSH_PULL);
    // 初始化步进电机驱动芯片PWM输出引脚，输出频率2M
#if (AXIS6 == 0)
    pwm_init(TIM2_PWM_CH1_A0, 20000, 4000);
    pwm_init(TIM1_PWM_CH1_A8, 20000, 4000);
#elif (AXIS6 == 1)
    pwm_init(TIM2_PWM_CH1_A0, 20000, 1500);
    pwm_init(TIM1_PWM_CH1_A8, 20000, 1500);
#endif
    MT6816_Init();
    // TFT初始化
    tft180_init();
    // CAN初始化
    CAN_Mode_Init( CAN_SJW_1tq, CAN_BS2_5tq, CAN_BS1_6tq, 12, CAN_Mode_Normal );
    // 定时器中断
    pit_init_ms(TIM8_PIT, 200);       // 指示灯
    pit_init_us(TIM9_PIT, 1000 * 1000 * 1.0f / motor_fre);
}






int main(void)
{
    interrupt_global_disable();             // 关闭总中断
    clock_init(SYSTEM_CLOCK_144M);          // 务必保留，设置系统时钟。
    debug_init();                           // 务必保留，本函数用于初始化MPU 时钟 调试串口

    Init();
    interrupt_global_enable();              // 总中断最后开启
    //MT6816_SetZero();
    MT6816_Structure data;
    tft180_show_string(0, 0, "Hello world.");
    MT6816_ReadAngle(&data);
    while(1)
    {
        if (is_start)
        {
            KeepPos();
        }
    }
}







