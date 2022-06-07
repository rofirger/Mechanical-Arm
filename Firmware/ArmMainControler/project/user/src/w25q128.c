/*
 * w25q128.c
 *
 *  Created on: 2022��6��6��
 *      Author: ���
 */
#include "w25q128.h"
#include "Config.h"

uint8_t WriteAndReadByteFromFlash_SPI(uint8_t _byte)
{
    uint8_t ret;
    // ����CS����
    FLASH_SPI_CS_GPIO->BCR = FLASH_SPI_CS;

    // ����
    SPI1->DATAR = _byte;
    while ((SPI1->STATR & SPI_I2S_FLAG_BSY) != RESET);

    // ����
    SPI1->DATAR = 0;
    while ((SPI1->STATR & SPI_I2S_FLAG_BSY) != RESET);
    ret = SPI1->DATAR;;

    // ����CS����
    FLASH_SPI_CS_GPIO->BSHR = FLASH_SPI_CS;
    return ret;
}

void W25QXX_Init(void)
{
    SPI_InitTypeDef  SPI_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_I2S_DeInit(SPI1);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  // ˫��˫��ȫ˫��
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;

    // ѡ��SPIģʽ0����ģʽ�²���Ҫ��������DW1000��GPIO5/6
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;

    SPI_InitStructure.SPI_BaudRatePrescaler = FLASH_SPI_PRESCALER;      // ���岨����Ԥ��Ƶ��ֵ
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                               // ����ģʽ��ʹ���������NSS����
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;                      // ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
    SPI_InitStructure.SPI_CRCPolynomial = 7;

    SPI_Init(SPI1, &SPI_InitStructure);

    // �����������
    GPIO_InitStructure.GPIO_Pin = FLASH_SPI_CS;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(FLASH_SPI_CS_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = FLASH_SPI_SCK;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(FLASH_SPI_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = FLASH_SPI_MOSI;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(FLASH_SPI_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = FLASH_SPI_MISO;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(FLASH_SPI_GPIO, &GPIO_InitStructure);

    // ʹ��SPI
    SPI_Cmd(SPI1, ENABLE);

    // ����CS����
    FLASH_SPI_CS_GPIO->BSHR = FLASH_SPI_CS;
}

//��ȡоƬID
//����ֵ����:
//0XEF13,��ʾоƬ�ͺ�ΪW25Q80
//0XEF14,��ʾоƬ�ͺ�ΪW25Q16
//0XEF15,��ʾоƬ�ͺ�ΪW25Q32
//0XEF16,��ʾоƬ�ͺ�ΪW25Q64
//0XEF17,��ʾоƬ�ͺ�ΪW25Q128
uint16_t  W25QXX_ReadID(void)
{
    uint16_t temp = 0;
    // ����CS����
    FLASH_SPI_CS_GPIO->BCR = FLASH_SPI_CS;
    WriteAndReadByteFromFlash_SPI(0x90);
    WriteAndReadByteFromFlash_SPI(0x00);
    WriteAndReadByteFromFlash_SPI(0x00);
    WriteAndReadByteFromFlash_SPI(0x00);
    temp |= WriteAndReadByteFromFlash_SPI(0xFF) << 8;
    temp |= WriteAndReadByteFromFlash_SPI(0xFF);
    // ����CS����
    FLASH_SPI_CS_GPIO->BSHR = FLASH_SPI_CS;
    return temp;
}

//��ȡW25QXX��״̬�Ĵ���
//BIT7  6   5   4   3   2   1   0
//SPR   RV  TB BP2 BP1 BP0 WEL BUSY
//SPR:Ĭ��0,״̬�Ĵ�������λ,���WPʹ��
//TB,BP2,BP1,BP0:FLASH����д��������
//WEL:дʹ������
//BUSY:æ���λ(1,æ;0,����)
//Ĭ��:0x00
u8   W25QXX_ReadSR(void)                //��ȡ״̬�Ĵ���
{
    u8 type = 0;
    // ����CS����
    FLASH_SPI_CS_GPIO->BCR = FLASH_SPI_CS;
    WriteAndReadByteFromFlash_SPI(W25X_ReadStatusReg); //���Ͷ�ȡ״̬�Ĵ�������
    type = WriteAndReadByteFromFlash_SPI(0xFF); //��ȡһ���ֽ�
    // ����CS����
    FLASH_SPI_CS_GPIO->BSHR = FLASH_SPI_CS;
    return type;
}

//дW25QXX״̬�Ĵ���
//ֻ��SPR,TB,BP2,BP1,BP0(bit 7,5,4,3,2)����д!!!
void W25QXX_Write_SR(u8 sr)             //д״̬�Ĵ���
{
    // ����CS����
    FLASH_SPI_CS_GPIO->BCR = FLASH_SPI_CS;
    WriteAndReadByteFromFlash_SPI(W25X_WriteStatusReg);
    WriteAndReadByteFromFlash_SPI(sr);
    // ����CS����
    FLASH_SPI_CS_GPIO->BSHR = FLASH_SPI_CS;
}

//W25QXXдʹ��
//��WEL��λ
void W25QXX_Write_Enable(void)          //дʹ��
{
    // ����CS����
    FLASH_SPI_CS_GPIO->BCR = FLASH_SPI_CS;
    WriteAndReadByteFromFlash_SPI(W25X_WriteEnable);
    // ����CS����
    FLASH_SPI_CS_GPIO->BSHR = FLASH_SPI_CS;
}

//W25QXXд��ֹ
//��WEL����
void W25QXX_Write_Disable(void)     //д����
{
    // ����CS����
    FLASH_SPI_CS_GPIO->BCR = FLASH_SPI_CS;
    WriteAndReadByteFromFlash_SPI(W25X_WriteDisable);
    // ����CS����
    FLASH_SPI_CS_GPIO->BSHR = FLASH_SPI_CS;
}

//SPI��һҳ(0~65535)��д������256���ֽڵ�����
//��ָ����ַ��ʼд�����256�ֽڵ�����
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)
//NumByteToWrite:Ҫд����ֽ���(���256),������Ӧ�ó�����ҳ��ʣ���ֽ���!!!
void W25QXX_Write_Page(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)
{
    u16 i;
    W25QXX_Write_Enable();
    // ����CS����
    FLASH_SPI_CS_GPIO->BCR = FLASH_SPI_CS;
    WriteAndReadByteFromFlash_SPI(W25X_PageProgram); //����дҳ����
    WriteAndReadByteFromFlash_SPI((u8)(WriteAddr >> 16)); //����24bit��ַ
    WriteAndReadByteFromFlash_SPI((u8)(WriteAddr >> 8));
    WriteAndReadByteFromFlash_SPI((u8)(WriteAddr));

    for(i=0;i<NumByteToWrite;i++)
    { //ѭ��д��
        WriteAndReadByteFromFlash_SPI(pBuffer[i]);
    }
    // ����CS����
    FLASH_SPI_CS_GPIO->BSHR = FLASH_SPI_CS;
    W25QXX_Wait_Busy();
}

//�޼���дSPI FLASH
//����ȷ����д�ĵ�ַ��Χ�ڵ�����ȫ��Ϊ0XFF,�����ڷ�0XFF��д������ݽ�ʧ��!
//�����Զ���ҳ����
//��ָ����ַ��ʼд��ָ�����ȵ�����,����Ҫȷ����ַ��Խ��!
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)
//NumByteToWrite:Ҫд����ֽ���(���65535)
//CHECK OK
void W25QXX_Write_NoCheck(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)
{
    u16 pageremain;
    pageremain = 256 - WriteAddr%256; //��ҳʣ����ֽ���
    if(NumByteToWrite <= pageremain)
    { //������256���ֽ�
        pageremain = NumByteToWrite;
    }
    while(1)
    {
        W25QXX_Write_Page(pBuffer,WriteAddr,pageremain);
        if(NumByteToWrite == pageremain)
        { //д�������
            break;
        }
        else
        {
            pBuffer += pageremain;
            WriteAddr += pageremain;

            NumByteToWrite -= pageremain; //��ȥ�Ѿ�д���˵��ֽ���
            if(NumByteToWrite > 256)
            { //һ�ο���д��256���ֽ�
                pageremain = 256;
            }
            else
            {
                pageremain = NumByteToWrite; //����256���ֽ���
            }
        }
    }
}

//��ȡSPI FLASH
//��ָ����ַ��ʼ��ȡָ�����ȵ�����
//pBuffer:���ݴ洢��
//ReadAddr:��ʼ��ȡ�ĵ�ַ(24bit)
//NumByteToRead:Ҫ��ȡ���ֽ���(���65535)
void W25QXX_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead)   //��ȡflash
{
    u16 i;
    // ����CS����
    FLASH_SPI_CS_GPIO->BCR = FLASH_SPI_CS;
    WriteAndReadByteFromFlash_SPI(W25X_ReadData); //���Ͷ�ָ��
    WriteAndReadByteFromFlash_SPI((u8)(ReadAddr >> 16));   //����24bit��ַ
    WriteAndReadByteFromFlash_SPI((u8)(ReadAddr >> 8));
    WriteAndReadByteFromFlash_SPI((u8)(ReadAddr));

    for(i=0;i<NumByteToRead;i++)
    {
        pBuffer[i] = WriteAndReadByteFromFlash_SPI(0xFF); // ��ȡ����
    }
    // ����CS����
    FLASH_SPI_CS_GPIO->BSHR = FLASH_SPI_CS;
}

//дSPI FLASH
//��ָ����ַ��ʼд��ָ�����ȵ�����
//�ú�������������!
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)
//NumByteToWrite:Ҫд����ֽ���(���65535)
u8 W25QXX_BUFFER[4096];
void W25QXX_Write(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)//д��flash
{
    u32 secpos;
    u16 secoff;
    u16 secremain;
    u16 i;
    u8 * W25QXX_BUF;
    W25QXX_BUF = W25QXX_BUFFER;
    secpos = WriteAddr / 4096; //������ַ
    secoff = WriteAddr % 4096; //�������ڵ�ƫ��
    secremain = 4096 - secoff; //����ʣ��ռ��С
    if(NumByteToWrite <= secremain)
    { //������4096���ֽ�
        secremain = NumByteToWrite;
    }
    while(1)
    {
        W25QXX_Read(W25QXX_BUF,secpos*4096,4096); //������������������
        for(i=0;i<secremain;i++)
        { //У������
            if(W25QXX_BUF[secoff+i] != 0xFF)
            { //��Ҫ����
                break;
            }
        }
        if(i<secremain)
        { //��Ҫ����
            W25QXX_Erase_Sector(secpos); //�����������
            for(i=0;i<secremain;i++)
            { //����
                W25QXX_BUF[i+secoff] = pBuffer[i];
            }
            W25QXX_Write_NoCheck(W25QXX_BUF,secpos*4096,4096); //д����������
        }
        else
        {
            W25QXX_Write_NoCheck(pBuffer,WriteAddr,secremain); //д�Ѿ������˵�,ֱ��д������ʣ������.
        }

        if(NumByteToWrite == secremain)
        { //д�������
            break;
        }
        else
        { //д��δ����
            secpos++; //������ַ��1
            secoff = 0; //ƫ��λ��Ϊ0
            pBuffer += secremain; //ָ��ƫ��
            WriteAddr += secremain; //д��ַƫ��
            NumByteToWrite -= secremain; //�ֽ����ݼ�
            if(NumByteToWrite>4096)
            { //��һ����������д����
                secremain = 4096;
            }
            else
            { //��һ����������д����
                secremain = NumByteToWrite;
            }
        }
    }
}

//��������оƬ
//�ȴ�ʱ�䳬��...
void W25QXX_Erase_Chip(void)            //��Ƭ����
{
    W25QXX_Write_Enable(); //SET WEL
    W25QXX_Wait_Busy();

    // ����CS����
    FLASH_SPI_CS_GPIO->BCR = FLASH_SPI_CS;
    WriteAndReadByteFromFlash_SPI(W25X_ChipErase); //����Ƭ��������
    // ����CS����
    FLASH_SPI_CS_GPIO->BSHR = FLASH_SPI_CS;

    W25QXX_Wait_Busy(); //�ȴ�оƬ��������
}

//����һ������
//Dst_Addr:������ַ ����ʵ����������
//����һ������������ʱ��:150ms
void W25QXX_Erase_Sector(u32 Dst_Addr)  //��������
{
    Dst_Addr *= 4096;
    W25QXX_Write_Enable(); //SET WEL
    W25QXX_Wait_Busy();
    // ����CS����
    FLASH_SPI_CS_GPIO->BCR = FLASH_SPI_CS;
    WriteAndReadByteFromFlash_SPI(W25X_SectorErase); //������������ָ��
    WriteAndReadByteFromFlash_SPI((u8)(Dst_Addr >> 16)); //����24bit��ַ
    WriteAndReadByteFromFlash_SPI((u8)(Dst_Addr >> 8));
    WriteAndReadByteFromFlash_SPI((u8)Dst_Addr);
    // ����CS����
    FLASH_SPI_CS_GPIO->BSHR = FLASH_SPI_CS;
    W25QXX_Wait_Busy(); //�ȴ��������
}

void W25QXX_Wait_Busy(void)             //�ȴ�����
{
    while((W25QXX_ReadSR() & 0x01) == 1);
}
void W25QXX_PowerDown(void)         //�������ģʽ
{
    // ����CS����
    FLASH_SPI_CS_GPIO->BCR = FLASH_SPI_CS;
    WriteAndReadByteFromFlash_SPI(W25X_PowerDown);
    // ����CS����
    FLASH_SPI_CS_GPIO->BSHR = FLASH_SPI_CS;
    HAL_Delay(3);
}
void W25QXX_WAKEUP(void)                //����
{
    // ����CS����
    FLASH_SPI_CS_GPIO->BCR = FLASH_SPI_CS;
    WriteAndReadByteFromFlash_SPI(W25X_ReleasePowerDown);
    // ����CS����
    FLASH_SPI_CS_GPIO->BSHR = FLASH_SPI_CS;
    HAL_Delay(3);
}
