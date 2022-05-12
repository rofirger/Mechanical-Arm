/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,逐飞科技
* All rights reserved.
*
* 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
* 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
*
* @file             main
* @company          成都逐飞科技有限公司
 * @author          逐飞科技(QQ790875685)
* @version          查看doc内version文件 版本说明
* @Software         MounRiver Studio V1.51
* @Target core      CH32V307VCT6
* @Taobao           https://seekfree.taobao.com/
* @date             2021-11-25
********************************************************************************************************************/

/*
 * @致谢：感谢逐飞科技ch32V307开源库的支持
*/

#include "Motor.h"
#include "zf_common_headfile.h"



/*
 * @note:控制驱动板上的LED闪烁
*/
void Blink()
{
    static int i = 0;
    if (i >= 100)
    {
        gpio_toggle_level(INDICATOR);
        i = 0;
    }
    i++;
}


int main(void)
{
    interrupt_global_disable();             // 关闭总中断
    clock_init(SYSTEM_CLOCK_144M);          // 务必保留，设置系统时钟。
    debug_init();                           // 务必保留，本函数用于初始化MPU 时钟 调试串口

    // 初始化步进电机驱动GPIO输出引脚
    gpio_init(INDICATOR, GPO, GPIO_LOW, GPO_PUSH_PULL);
    gpio_init(AP_STEP, GPO, GPIO_LOW, GPO_PUSH_PULL);
    gpio_init(AN_STEP, GPO, GPIO_LOW, GPO_PUSH_PULL);
    gpio_init(BP_STEP, GPO, GPIO_LOW, GPO_PUSH_PULL);
    gpio_init(BN_STEP, GPO, GPIO_LOW, GPO_PUSH_PULL);
    // 初始化步进电机驱动芯片PWM输出引脚，输出频率2M
    pwm_init(TIM2_PWM_CH1_A0, 20000, 4000);
    pwm_init(TIM1_PWM_CH1_A8, 20000, 4000);
    MT6816_Init();
    interrupt_global_enable();              // 总中断最后开启
    MT6816_SetZero();
    MT6816_Structure data;
    while(1)
    {
        MT6816_ReadAngle(&data);
        //gpio_set_level(E2, GPIO_HIGH);
/*
        gpio_set_level(AP_STEP, GPIO_HIGH);
        gpio_set_level(BP_STEP, GPIO_HIGH);
        gpio_set_level(AN_STEP, GPIO_LOW);
        gpio_set_level(BN_STEP, GPIO_LOW);
        system_delay_ms(1);

        gpio_set_level(AP_STEP, GPIO_LOW);
        gpio_set_level(BP_STEP, GPIO_HIGH);
        gpio_set_level(AN_STEP, GPIO_HIGH);
        gpio_set_level(BN_STEP, GPIO_LOW);
        system_delay_ms(1);

        gpio_set_level(AP_STEP, GPIO_LOW);
        gpio_set_level(BP_STEP, GPIO_LOW);
        gpio_set_level(AN_STEP, GPIO_HIGH);
        gpio_set_level(BN_STEP, GPIO_HIGH);
        system_delay_ms(1);

        gpio_set_level(AP_STEP, GPIO_HIGH);
        gpio_set_level(BP_STEP, GPIO_LOW);
        gpio_set_level(AN_STEP, GPIO_LOW);
        gpio_set_level(BN_STEP, GPIO_HIGH);
        system_delay_ms(1);
*/
        system_delay_ms(10);
        Blink();
    }
}







