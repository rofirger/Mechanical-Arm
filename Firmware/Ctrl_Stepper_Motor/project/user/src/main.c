/*
 * @��л����л��ɿƼ�ch32V307��Դ���֧��
*/
/*
 *      @File: main.c
 *
 *      @Team: ɾ����·��
 *      @Author: ���
 */
#include "Motor.h"
#include "headfile.h"
#include "MyCan.h"
#include "stdlib.h"
#include "msg_process.h"
#include "Motor.h"


/*
 * @note:�����������ϵ�LED��˸
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
    // ָʾ��
    gpio_init(INDICATOR, GPO, 1, GPO_PUSH_PULL);
    // ��ʼ�������������GPIO�������
    gpio_init(AP_STEP, GPO, GPIO_LOW, GPO_PUSH_PULL);
    gpio_init(AN_STEP, GPO, GPIO_LOW, GPO_PUSH_PULL);
    gpio_init(BP_STEP, GPO, GPIO_LOW, GPO_PUSH_PULL);
    gpio_init(BN_STEP, GPO, GPIO_LOW, GPO_PUSH_PULL);
    // ��ʼ�������������оƬPWM������ţ����Ƶ��2M
#if (AXIS6 == 0)
    pwm_init(TIM2_PWM_CH1_A0, 20000, 4000);
    pwm_init(TIM1_PWM_CH1_A8, 20000, 4000);
#elif (AXIS6 == 1)
    pwm_init(TIM2_PWM_CH1_A0, 20000, 1500);
    pwm_init(TIM1_PWM_CH1_A8, 20000, 1500);
#endif
    MT6816_Init();
    // TFT��ʼ��
    tft180_init();
    // CAN��ʼ��
    CAN_Mode_Init( CAN_SJW_1tq, CAN_BS2_5tq, CAN_BS1_6tq, 12, CAN_Mode_Normal );
    // ��ʱ���ж�
    pit_init_ms(TIM8_PIT, 200);       // ָʾ��
    pit_init_us(TIM9_PIT, 1000 * 1000 * 1.0f / motor_fre);
}






int main(void)
{
    interrupt_global_disable();             // �ر����ж�
    clock_init(SYSTEM_CLOCK_144M);          // ��ر���������ϵͳʱ�ӡ�
    debug_init();                           // ��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���

    Init();
    interrupt_global_enable();              // ���ж������
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







