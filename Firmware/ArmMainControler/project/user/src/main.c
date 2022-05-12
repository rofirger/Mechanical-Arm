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



#include "zf_common_headfile.h"

#define KEY_UP    E1
#define KEY_DOWN  E2
#define KEY_MID   D13
#define KEY_LEFT  D6
#define KEY_RIGHT E3

#define BEEP      E15

/*
 * @note:控制机械臂主板上的LED闪烁
*/
#define CONTROLER_INDICATOR A10
void Blink()
{
    static int i = 0;
    if (i >= 100)
    {
        gpio_toggle_level(CONTROLER_INDICATOR);
        i = 0;
    }
    i++;
}

void KeyInit()
{
    // Note: 5Key内部已使用下拉电阻
    gpio_init(KEY_UP, GPI, GPIO_LOW, GPI_PULL_DOWN);
    gpio_init(KEY_DOWN, GPI, GPIO_LOW, GPI_PULL_DOWN);
    gpio_init(KEY_MID, GPI, GPIO_LOW, GPI_PULL_DOWN);
    gpio_init(KEY_LEFT, GPI, GPIO_LOW, GPI_PULL_DOWN);
    gpio_init(KEY_RIGHT, GPI, GPIO_LOW, GPI_PULL_DOWN);
}

void FiveKeyStatus()
{
    if (gpio_get_level(KEY_UP) == 1)
    {
        tft180_show_char(50,10, '1');
    }
    if (gpio_get_level(KEY_DOWN) == 1)
    {
        tft180_show_char(50,10, '2');
    }
    if (gpio_get_level(KEY_MID) == 1)
    {
        tft180_show_char(50,10, '3');
    }
    if (gpio_get_level(KEY_LEFT) == 1)
    {
        tft180_show_char(50,10, '4');
    }
    if (gpio_get_level(KEY_RIGHT) == 1)
    {
        tft180_show_char(50,10, '5');
        gpio_set_level(BEEP, 1);
    }
    else
    {
        gpio_set_level(BEEP, 0);
    }
}

void Init()
{
    tft180_init();
    gpio_init(CONTROLER_INDICATOR, GPO, GPIO_LOW, GPO_PUSH_PULL);
    gpio_init(BEEP, GPO, GPIO_LOW, GPO_PUSH_PULL);
    KeyInit();
}

int main(void)
{
    interrupt_global_disable();             // 关闭总中断
    clock_init(SYSTEM_CLOCK_144M);          // 务必保留，设置系统时钟。
    debug_init();                           // 务必保留，本函数用于初始化MPU 时钟 调试串口

    Init();
    interrupt_global_enable();              // 总中断最后开启
    while(1)
    {
        //FiveKeyStatus();
        tft180_show_char(10,10, 'A');
        tft180_show_char(20,10, 'B');
        system_delay_ms(10);
        Blink();
    }
}







