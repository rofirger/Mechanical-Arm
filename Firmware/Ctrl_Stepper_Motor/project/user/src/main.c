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

/*
 * @��л����л��ɿƼ�ch32V307��Դ���֧��
*/

#include "Motor.h"
#include "zf_common_headfile.h"



/*
 * @note:�����������ϵ�LED��˸
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
    interrupt_global_disable();             // �ر����ж�
    clock_init(SYSTEM_CLOCK_144M);          // ��ر���������ϵͳʱ�ӡ�
    debug_init();                           // ��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���

    // ��ʼ�������������GPIO�������
    gpio_init(INDICATOR, GPO, GPIO_LOW, GPO_PUSH_PULL);
    gpio_init(AP_STEP, GPO, GPIO_LOW, GPO_PUSH_PULL);
    gpio_init(AN_STEP, GPO, GPIO_LOW, GPO_PUSH_PULL);
    gpio_init(BP_STEP, GPO, GPIO_LOW, GPO_PUSH_PULL);
    gpio_init(BN_STEP, GPO, GPIO_LOW, GPO_PUSH_PULL);
    // ��ʼ�������������оƬPWM������ţ����Ƶ��2M
    pwm_init(TIM2_PWM_CH1_A0, 20000, 4000);
    pwm_init(TIM1_PWM_CH1_A8, 20000, 4000);
    MT6816_Init();
    interrupt_global_enable();              // ���ж������
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







