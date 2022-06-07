#include "zf_common_headfile.h"
#include "Config.h"
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
    gpio_init(INDICATOR, GPO, GPIO_LOW, GPO_PUSH_PULL);
    tft180_init();
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

        Blink(1);
        tft180_show_string(0,0,"ZongJie is SB!!!");
        system_delay_ms(500);
    }
}







