#include <string.h>

#include "deca_spi.h"
#include "deca_device_api.h"
#include "port.h"

int openspi(/*SPI_TypeDef* SPIx*/)
{
    // done by port.c, default SPI used is SPI1

    return 0;

} // end openspi()

int closespi(void)
{
    // SPIx->STATR  [1] == 0:���ͻ������ǿ�
    while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE)== RESET);
    SPI_Cmd(SPIx, DISABLE);
    return 0;

}

/*
 * @brief:  ��DW1000д������
 * @return 0 for success
 */
#pragma GCC optimize ("O3")
int writetospi(uint16_t header_length, const uint8_t* header_buffer, uint32_t body_length, const uint8_t* body_buffer)
{
    decaIrqStatus_t stat;
    stat = decamutexon();

    // ����CS����
    SPIx_CS_GPIO->BCR = SPIx_CS;

    // ���ȴ���header
    for (uint16_t i = 0; i < header_length; ++i)
    {
        // ����SPI��ʼ�����õ�  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b, �Ĵ���SPI->DATAR���Ͱ�λ��Ч
        SPIx->DATAR = header_buffer[i];
        while ((SPIx->STATR & SPI_I2S_FLAG_BSY) != RESET);
        SPIx->DATAR;
    }
    // ������������
    for (uint32_t i = 0; i < body_length; ++i)
    {
        // ����SPI��ʼ�����õ�  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b, �Ĵ���SPI->DATAR���Ͱ�λ��Ч
        SPIx->DATAR = body_buffer[i];
        while ((SPIx->STATR & SPI_I2S_FLAG_BSY) != RESET);
        SPIx->DATAR;
    }
    // ����CS����
    SPIx_CS_GPIO->BSHR = SPIx_CS;

    decamutexoff(stat);
    return 0;
}


/*
 * @brief:  ��ȡDW1000�������������
 * @return 0 for success
 */
#pragma GCC optimize ("O3")
int readfromspi(uint16_t header_length,const uint8_t* header_buffer, uint32_t read_length, uint8_t* read_buffer)
{
    decaIrqStatus_t stat;
    stat = decamutexon();

    // ����CS����
    SPIx_CS_GPIO->BCR = SPIx_CS;
    // ���ȴ���header
    for (uint16_t i = 0; i < header_length; ++i)
    {
        // ����SPI��ʼ�����õ�  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b, �Ĵ���SPI->DATAR���Ͱ�λ��Ч
        SPIx->DATAR = header_buffer[i];
        while ((SPIx->STATR & SPI_I2S_FLAG_BSY) != RESET);
        read_buffer[0] = SPIx->DATAR;
    }
    // ������������
    for (uint32_t i = 0; i < read_length; ++i)
    {
        // ����SPI��ʼ�����õ�  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b, �Ĵ���SPI->DATAR���Ͱ�λ��Ч
        SPIx->DATAR = 0;
        while ((SPIx->STATR & SPI_I2S_FLAG_BSY) != RESET);
        read_buffer[i] = SPIx->DATAR;;
    }
    // ����CS����
    SPIx_CS_GPIO->BSHR = SPIx_CS;
    decamutexoff(stat);
    return 0;
}
