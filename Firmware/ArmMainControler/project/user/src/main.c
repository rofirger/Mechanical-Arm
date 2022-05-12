/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,��ɿƼ�
* All rights reserved.
*
* �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
* ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
*
* @file             main
* @company          �ɶ���ɿƼ����޹�˾
 * @author          ��ɿƼ�(QQ790875685)
* @version          �鿴doc��version�ļ� �汾˵��
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
 * @note:���ƻ�е�������ϵ�LED��˸
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
    // Note: 5Key�ڲ���ʹ����������
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
    interrupt_global_disable();             // �ر����ж�
    clock_init(SYSTEM_CLOCK_144M);          // ��ر���������ϵͳʱ�ӡ�
    debug_init();                           // ��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���

    Init();
    interrupt_global_enable();              // ���ж������
    while(1)
    {
        //FiveKeyStatus();
        tft180_show_char(10,10, 'A');
        tft180_show_char(20,10, 'B');
        system_delay_ms(10);
        Blink();
    }
}







