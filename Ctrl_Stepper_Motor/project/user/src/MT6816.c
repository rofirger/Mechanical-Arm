/*
 * ctrl_stepper_motor_init.c
 *
 *  Created on: 2022年4月19日
 *      Author: 随风
 */
#include <MT6816.h>
#include "zf_common_headfile.h"
extern const uint32 spi_index[3];

// 内部函数
void MT6816_SpiTransfer16Bits (spi_index_enum spi_n, uint16 *write_buffer, uint16 *read_buffer, uint32 len)
{
    while(len--)
    {
        ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = (*write_buffer&0xFF00)>>8;
        while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
        if(read_buffer != NULL)
        {
            //while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_RXNE) == RESET);
            *read_buffer = ((((SPI_TypeDef *)(spi_index[spi_n]))->DATAR) & 0x00FF) << 8;
        }

        ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = (*write_buffer&0x00FF);
         while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
         if(read_buffer != NULL)
         {
             //while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_RXNE) == RESET);
             *read_buffer = (*read_buffer) | ((((SPI_TypeDef *)(spi_index[spi_n]))->DATAR) & 0x00FF);
         }
         write_buffer++;
         read_buffer++;
    }
}

void MT6816_Init()
{
    gpio_init(MT_CS, GPO, 1, SPEED_50MHZ | GPO_PUSH_PULL); // 关闭spi
    // MT6816数据手册P18: MT6816使用模式3来进行交换数据
    spi_init(MT_SPI, MT_SPI_MODE, system_clock / 16, MT_SCK, MT_MOSI, MT_MISO, SPI_CS_NULL);
}

// 内部函数
uint16_t MT6816_SendRead16bits(uint16_t send_data)
{
    uint16_t ret = 0;
    gpio_set_level(MT_CS, 0);
    MT6816_SpiTransfer16Bits(MT_SPI, &send_data, &ret, 1);
    gpio_set_level(MT_CS, 1);
    return ret;
}

/*
 * MT6816角度寄存器清零
*/
void MT6816_SetZero()
{
    uint16_t tx[2];
       // MT6816数据手册P19：MOSI是R/W位为0时，后8为将被写入MT6816；为1时，将从MT6816读取(通过MISO)0x03/0x04寄存器中的八位数据
    tx[0] = (0x00 | 0x03) << 8; // 读取MT6816的Reg.Address == 0x03寄存器的16位值
    tx[1] = (0x00 | 0x04) << 8; // 读取MT6816的Reg.Address == 0x04寄存器的16位值

    MT6816_SendRead16bits(tx[0]);
    MT6816_SendRead16bits(tx[1]);
}

bool MT6816_ReadAngle(MT6816_Structure* mt6816_structure)
{
    uint16_t rx[2];
    uint16_t tx[2];
    // MT6816数据手册P19：MOSI是R/W位为0时，后8为将被写入MT6816；为1时，将从MT6816读取(通过MISO)0x03/0x04寄存器中的八位数据
    tx[0] = (0x80 | 0x03) << 8; // 读取MT6816的Reg.Address == 0x03寄存器的16位值
    tx[1] = (0x80 | 0x04) << 8; // 读取MT6816的Reg.Address == 0x04寄存器的16位值
    for (uint8_t i = 0; i < 4; ++i)
    {
        rx[0] = MT6816_SendRead16bits(tx[0]);
        rx[1] = MT6816_SendRead16bits(tx[1]);
        uint16_t angle_raw_data = ((rx[0] & 0x00FF) << 8) | (rx[1] & 0x00FF);
        // MT6816数据手册P21：angle_raw_data[0]为奇偶校验位, angle_raw_data[1]为磁通密度不足警告( 1: 磁通密度不足)，不包含角度信息
        uint8_t check = 0;
        for (uint8_t j = 1; j < 16; ++j)
        {
            if (angle_raw_data & (0x01 << j))
            {
                check++;
            }
        }
        if ((check & 0x01) == (angle_raw_data & 0x01))
        {
            mt6816_structure->_raw_angle = angle_raw_data;
            mt6816_structure->_decode_angle = (angle_raw_data >> 2) * 360 / 16384;
            mt6816_structure->_no_mag_warning = ((angle_raw_data & 0x02) >> 1);
            return true;
        }
    }
    return false;
}
