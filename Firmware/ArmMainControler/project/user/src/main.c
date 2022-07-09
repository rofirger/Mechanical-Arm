/*
 * @note: 部分库由 逐飞科技 提供！
 * */

#include "zf_common_headfile.h"
#include "MyCan.h"
#include "Config.h"
#include "WCHNET.h"
#include "string.h"
#include "ETH.h"
#include "w25q128.h"

static uint16_t p_ms = 0;
void Delay_Ms(uint32_t n)
{
    uint32_t i;

    SysTick->SR &= ~(1 << 0);
    i = (uint32_t)n * p_ms;

    SysTick->CMP = i;
    SysTick->CTLR |= (1 << 4) | (1 << 5) | (1 << 0);

    while((SysTick->SR & (1 << 0)) != (1 << 0))
        ;
    SysTick->CTLR &= ~(1 << 0);
}




/*
 * @note:控制机械臂主板上的LED闪烁
*/
#define CONTROLER_INDICATOR A10
void Blink(uint16_t _times)
{
    static int i = 0;
    if (i >= _times)
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

    // 按键
    gpio_init(BUTTON1, GPI, GPIO_HIGH, GPI_PULL_UP);
    gpio_init(BUTTON2, GPI, GPIO_HIGH, GPI_PULL_UP);

    // 配置 button2引脚中断
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    GPIO_EXTILineConfig(BUTTON2_PORT_SOURCE, BUTTON2_PIN_SOURCE);
    EXTI_InitStructure.EXTI_Line = BUTTON2_LINE;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    NVIC_InitStructure.NVIC_IRQChannel = BUTTON2_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure);
}

void FiveKeyStatus()
{
    uint8_t px;
    if (gpio_get_level(BUTTON2) == 0)
    {
        if (gpio_get_level(KEY_UP) == 1)
        {
            px = CAN_Send_Msg( "S C 2#", 7, (FILTER_ID_AXIS6_A >> 5));
        }
        else if (gpio_get_level(KEY_DOWN) == 1)
        {
            px = CAN_Send_Msg( "S V 2#", 7, (FILTER_ID_AXIS6_A >> 5));
        }
        if (px)
        {
            tft180_show_string(10, 10, "Send Failed6" );
        }
        else
        {
            tft180_show_string(10, 10, "Send Success6" );
        }
        return;
    }
    if (gpio_get_level(KEY_UP) == 1)
    {
        if (gpio_get_level(BUTTON1) == 1)
        {
            px = CAN_Send_Msg( "S C 2#", 7, (FILTER_ID_AXIS1_A >> 5));
        }
        else
        {
            px = CAN_Send_Msg( "S V 2#", 7, (FILTER_ID_AXIS1_A >> 5));
        }
        if( px )
        {
            tft180_show_string(10, 10, "Send Failed1" );
        }
        else
        {
            tft180_show_string(10, 10, "Send Success1" );
        }
    }
    if (gpio_get_level(KEY_DOWN) == 1)
    {
        if (gpio_get_level(BUTTON1) == 1)
        {
            px = CAN_Send_Msg( "S C 2#", 7, (FILTER_ID_AXIS2_A >> 5));
        }
        else
        {
            px = CAN_Send_Msg( "S V 2#", 7, (FILTER_ID_AXIS2_A >> 5));
        }
        if( px )
        {
            tft180_show_string(10, 10, "Send Failed2" );
        }
        else
        {
            tft180_show_string(10, 10, "Send Success2" );
        }
    }
    if (gpio_get_level(KEY_MID) == 1)
    {
        if (gpio_get_level(BUTTON1) == 1)
        {
            px = CAN_Send_Msg( "S C 2#", 7, (FILTER_ID_AXIS3_A >> 5));
        }
        else
        {
            px = CAN_Send_Msg( "S V 2#", 7, (FILTER_ID_AXIS3_A >> 5));
        }
        if( px )
        {
            tft180_show_string(10, 10, "Send Failed3" );
        }
        else
        {
            tft180_show_string(10, 10, "Send Success3" );
        }
    }
    if (gpio_get_level(KEY_LEFT) == 1)
    {
        if (gpio_get_level(BUTTON1) == 1)
        {
            px = CAN_Send_Msg( "S C 2#", 7, (FILTER_ID_AXIS4_A >> 5));
        }
        else
        {
            px = CAN_Send_Msg( "S V 2#", 7, (FILTER_ID_AXIS4_A >> 5));
        }
        if( px )
        {
            tft180_show_string(10, 10, "Send Failed4" );
        }
        else
        {
            tft180_show_string(10, 10, "Send Success4" );
        }
    }
    if (gpio_get_level(KEY_RIGHT) == 1)
    {
        if (gpio_get_level(BUTTON1) == 1)
        {
            px = CAN_Send_Msg( "S C 2#", 7, (FILTER_ID_AXIS5_A >> 5));
        }
        else
        {
            px = CAN_Send_Msg( "S V 2#", 7, (FILTER_ID_AXIS5_A >> 5));
        }
        if( px )
        {
            tft180_show_string(10, 10, "Send Failed5" );
        }
        else
        {
            tft180_show_string(10, 10, "Send Success5" );
        }
    }

}

void ETH_led()
{
    gpio_toggle_level(EGREEN_LED);
    gpio_toggle_level(EYELLOW_LED);
    //gpio_toggle_level(BEEP);
}

void Init()
{
    tft180_init();
    gpio_init(CONTROLER_INDICATOR, GPO, GPIO_LOW, GPO_PUSH_PULL);
    gpio_init(BEEP, GPO, GPIO_HIGH, GPO_PUSH_PULL);
    gpio_init(EGREEN_LED, GPO, GPIO_LOW, GPO_PUSH_PULL);
    gpio_init(EYELLOW_LED, GPO, GPIO_LOW, GPO_PUSH_PULL);
    KeyInit();
    CAN_Mode_Init( CAN_SJW_1tq, CAN_BS2_5tq, CAN_BS1_6tq, 12, CAN_Mode_Normal );

    W25QXX_Init();
}



typedef enum
{
    FlASH_192_SRAM_128 = 0,
    FLASH_224_SRAM_96,
    FLASH_256_SRAM_64,
    FLASH_288_RAM_32
} FLASH_SRAM_DEFIN;

//note: this operation will take effect after reset
void Config_Flash_SRAM(FLASH_SRAM_DEFIN SetFlashSRAM)
{
    uint8_t UserByte = FLASH_GetUserOptionByte() & 0xff; //get user option byte

    switch(SetFlashSRAM)
    {
    case 0:
        UserByte &= ~(0xc0); // SRAM_CODE_MODE = 00
        break;
    case 1:
        UserByte &= ~(0xc0); // SRAM_CODE_MODE = 00
        UserByte |= 0x7f;    // SRAM_CODE_MODE = 01
        break;
    case 2:
        UserByte &= ~(0xc0); // SRAM_CODE_MODE = 00
        UserByte |= 0xbf;    // SRAM_CODE_MODE = 10
        break;
    case 3:
        UserByte |= 0xff;    // SRAM_CODE_MODE = 11
        break;
    default:
        break;
    }

    FLASH_Unlock();
    FLASH_ProgramOptionByteData(0x1ffff802, UserByte);
    FLASH_Lock();
}

int main(void)
{

    interrupt_global_disable();             // 关闭总中断
    clock_init(SYSTEM_CLOCK_144M);          // 务必保留，设置系统时钟。
    debug_init();                           // 务必保留，本函数用于初始化MPU 时钟 调试串口
    Config_Flash_SRAM(FlASH_192_SRAM_128);
    Init();
    interrupt_global_enable();              // 总中断最后开启
    Eth();
    //gpio_set_level(BEEP, 1);
    uint16_t flash_id = W25QXX_ReadID();
    tft180_show_string(10, 10, "Hello world" );

    uint8_t pxbuf[10] = {'\0'};

    while(1)
    {
        WCHNET_MainTask();                                                     /*以太网库主任务函数，需要循环调用*/
        if(WCHNET_QueryGlobalInt())                                            /*查询以太网全局中断，如果有中断，调用全局中断处理函数*/
        {
           WCHNET_HandleGlobalInt();
        }
        FiveKeyStatus();
        Blink(1000);
    }
}







