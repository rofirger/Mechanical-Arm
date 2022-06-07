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
    interrupt_global_disable();             // 关闭总中断
    clock_init(SYSTEM_CLOCK_144M);          // 务必保留，设置系统时钟。
    debug_init();                           // 务必保留，本函数用于初始化MPU 时钟 调试串口
    Init();
    interrupt_global_enable();              // 总中断最后开启
    while(1)
    {

        Blink(1);
        tft180_show_string(0,0,"ZongJie is SB!!!");
        system_delay_ms(500);
    }
}







