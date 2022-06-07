/*
 * deca_spi.c
 *
 *  Created on: 2022年6月4日
 *      Author: 随风
 */


#include "deca_spi.h"
#include "deca_device_api.h"
#include "port.h"

void CloseDW_SPI(void)
{
    // SPIx->STATR  [1] == 0:发送缓冲区非空
    while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE)== RESET);
    SPI_Cmd(SPIx, DISABLE);
}

/*
 * @brief:  向DW1000写入数据
 * @return 0 for success
 */
uint8_t WriteToDW_SPI(uint16_t header_length, const uint8_t* header_buffer, uint16_t body_length, const uint8_t* body_buffer)
{
    decaIrqStatus_t stat;
    stat = decamutexon();

    // 拉低CS引脚
    SPIx_CS_GPIO->BCR = SPIx_CS;

    // 首先传输header
    for (uint16_t i = 0; i < header_length; ++i)
    {
        // 由于SPI初始化设置的  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b, 寄存器SPI->DATAR仅低八位有效
        SPIx->DATAR = header_buffer[i];
        while ((SPIx->STATR & SPI_I2S_FLAG_BSY) != RESET);
    }
    // 传输数据主体
    for (uint16_t i = 0; i < body_length; ++i)
    {
        // 由于SPI初始化设置的  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b, 寄存器SPI->DATAR仅低八位有效
        SPIx->DATAR = body_buffer[i];
        while ((SPIx->STATR & SPI_I2S_FLAG_BSY) != RESET);
    }
    // 拉高CS引脚
    SPIx_CS_GPIO->BSHR = SPIx_CS;

    decamutexoff(stat);
    return 0;
}

/*
 * @brief:  读取DW1000传输过来的数据
 * @return 0 for success
 */
uint8_t ReadFromDW_SPI(uint16_t header_length, const uint8_t* header_buffer, uint16_t read_length, const uint8_t* read_buffer)
{
    decaIrqStatus_t stat;
    stat = decamutexon();

    // 拉低CS引脚
    SPIx_CS_GPIO->BCR = SPIx_CS;

    // 首先传输header
    for (uint16_t i = 0; i < header_length; ++i)
    {
        // 由于SPI初始化设置的  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b, 寄存器SPI->DATAR仅低八位有效
        SPIx->DATAR = 0;
        while ((SPIx->STATR & SPI_I2S_FLAG_BSY) != RESET);
        header_buffer[i] = SPIx->DATAR;
    }
    // 传输数据主体
    for (uint16_t i = 0; i < read_length; ++i)
    {
        // 由于SPI初始化设置的  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b, 寄存器SPI->DATAR仅低八位有效
        SPIx->DATAR = 0;
        while ((SPIx->STATR & SPI_I2S_FLAG_BSY) != RESET);
        read_buffer[i] = SPIx->DATAR;;
    }
    // 拉高CS引脚
    SPIx_CS_GPIO->BSHR = SPIx_CS;

    decamutexoff(stat);
    return 0;
}
