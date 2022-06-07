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
    //Config_Flash_SRAM(FLASH_256_SRAM_64);
    interrupt_global_enable();              // 总中断最后开启
    while(1)
    {


    }
}







