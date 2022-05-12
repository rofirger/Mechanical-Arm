/*
 * ctrl_stepper_motor_init.c
 *
 *  Created on: 2022��4��19��
 *      Author: ���
 */
#include <MT6816.h>
#include "zf_common_headfile.h"
extern const uint32 spi_index[3];

// �ڲ�����
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
    gpio_init(MT_CS, GPO, 1, SPEED_50MHZ | GPO_PUSH_PULL); // �ر�spi
    // MT6816�����ֲ�P18: MT6816ʹ��ģʽ3�����н�������
    spi_init(MT_SPI, MT_SPI_MODE, system_clock / 16, MT_SCK, MT_MOSI, MT_MISO, SPI_CS_NULL);
}

// �ڲ�����
uint16_t MT6816_SendRead16bits(uint16_t send_data)
{
    uint16_t ret = 0;
    gpio_set_level(MT_CS, 0);
    MT6816_SpiTransfer16Bits(MT_SPI, &send_data, &ret, 1);
    gpio_set_level(MT_CS, 1);
    return ret;
}

/*
 * MT6816�ǶȼĴ�������
*/
void MT6816_SetZero()
{
    uint16_t tx[2];
       // MT6816�����ֲ�P19��MOSI��R/WλΪ0ʱ����8Ϊ����д��MT6816��Ϊ1ʱ������MT6816��ȡ(ͨ��MISO)0x03/0x04�Ĵ����еİ�λ����
    tx[0] = (0x00 | 0x03) << 8; // ��ȡMT6816��Reg.Address == 0x03�Ĵ�����16λֵ
    tx[1] = (0x00 | 0x04) << 8; // ��ȡMT6816��Reg.Address == 0x04�Ĵ�����16λֵ

    MT6816_SendRead16bits(tx[0]);
    MT6816_SendRead16bits(tx[1]);
}

bool MT6816_ReadAngle(MT6816_Structure* mt6816_structure)
{
    uint16_t rx[2];
    uint16_t tx[2];
    // MT6816�����ֲ�P19��MOSI��R/WλΪ0ʱ����8Ϊ����д��MT6816��Ϊ1ʱ������MT6816��ȡ(ͨ��MISO)0x03/0x04�Ĵ����еİ�λ����
    tx[0] = (0x80 | 0x03) << 8; // ��ȡMT6816��Reg.Address == 0x03�Ĵ�����16λֵ
    tx[1] = (0x80 | 0x04) << 8; // ��ȡMT6816��Reg.Address == 0x04�Ĵ�����16λֵ
    for (uint8_t i = 0; i < 4; ++i)
    {
        rx[0] = MT6816_SendRead16bits(tx[0]);
        rx[1] = MT6816_SendRead16bits(tx[1]);
        uint16_t angle_raw_data = ((rx[0] & 0x00FF) << 8) | (rx[1] & 0x00FF);
        // MT6816�����ֲ�P21��angle_raw_data[0]Ϊ��żУ��λ, angle_raw_data[1]Ϊ��ͨ�ܶȲ��㾯��( 1: ��ͨ�ܶȲ���)���������Ƕ���Ϣ
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
