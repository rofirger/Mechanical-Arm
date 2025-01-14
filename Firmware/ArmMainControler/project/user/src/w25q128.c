/*
 *      @File: w25q128.h
 *
 *      @Team: 删库跑路队
 *      @Author: 随风
 */
#include "w25q128.h"
#include "Config.h"

uint8_t WriteAndReadByteFromFlash_SPI(uint8_t _byte)
{
    uint8_t ret;
    // 拉低CS引脚
    FLASH_SPI_CS_GPIO->BCR = FLASH_SPI_CS;

    // 发送
    SPI1->DATAR = _byte;
    while ((SPI1->STATR & SPI_I2S_FLAG_BSY) != RESET);

    // 接收
    SPI1->DATAR = 0;
    while ((SPI1->STATR & SPI_I2S_FLAG_BSY) != RESET);
    ret = SPI1->DATAR;;

    // 拉高CS引脚
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

    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  // 双线双向全双工
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;

    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;

    SPI_InitStructure.SPI_BaudRatePrescaler = FLASH_SPI_PRESCALER;      // 定义波特率预分频的值
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                               // 主机模式，使用软件控制NSS引脚
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;                      // 指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
    SPI_InitStructure.SPI_CRCPolynomial = 7;

    SPI_Init(SPI1, &SPI_InitStructure);

    // 相关引脚配置
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

    // 使能SPI
    SPI_Cmd(SPI1, ENABLE);

    // 拉高CS引脚
    FLASH_SPI_CS_GPIO->BSHR = FLASH_SPI_CS;
}

//读取芯片ID
//返回值如下:
//0XEF13,表示芯片型号为W25Q80
//0XEF14,表示芯片型号为W25Q16
//0XEF15,表示芯片型号为W25Q32
//0XEF16,表示芯片型号为W25Q64
//0XEF17,表示芯片型号为W25Q128
uint16_t  W25QXX_ReadID(void)
{
    uint16_t temp = 0;
    // 拉低CS引脚
    FLASH_SPI_CS_GPIO->BCR = FLASH_SPI_CS;
    WriteAndReadByteFromFlash_SPI(0x90);
    WriteAndReadByteFromFlash_SPI(0x00);
    WriteAndReadByteFromFlash_SPI(0x00);
    WriteAndReadByteFromFlash_SPI(0x00);
    temp |= WriteAndReadByteFromFlash_SPI(0xFF) << 8;
    temp |= WriteAndReadByteFromFlash_SPI(0xFF);
    // 拉高CS引脚
    FLASH_SPI_CS_GPIO->BSHR = FLASH_SPI_CS;
    return temp;
}

//读取W25QXX的状态寄存器
//BIT7  6   5   4   3   2   1   0
//SPR   RV  TB BP2 BP1 BP0 WEL BUSY
//SPR:默认0,状态寄存器保护位,配合WP使用
//TB,BP2,BP1,BP0:FLASH区域写保护设置
//WEL:写使能锁定
//BUSY:忙标记位(1,忙;0,空闲)
//默认:0x00
u8   W25QXX_ReadSR(void)                //读取状态寄存器
{
    u8 type = 0;
    // 拉低CS引脚
    FLASH_SPI_CS_GPIO->BCR = FLASH_SPI_CS;
    WriteAndReadByteFromFlash_SPI(W25X_ReadStatusReg); //发送读取状态寄存器命令
    type = WriteAndReadByteFromFlash_SPI(0xFF); //读取一个字节
    // 拉高CS引脚
    FLASH_SPI_CS_GPIO->BSHR = FLASH_SPI_CS;
    return type;
}

//写W25QXX状态寄存器
//只有SPR,TB,BP2,BP1,BP0(bit 7,5,4,3,2)可以写!!!
void W25QXX_Write_SR(u8 sr)             //写状态寄存器
{
    // 拉低CS引脚
    FLASH_SPI_CS_GPIO->BCR = FLASH_SPI_CS;
    WriteAndReadByteFromFlash_SPI(W25X_WriteStatusReg);
    WriteAndReadByteFromFlash_SPI(sr);
    // 拉高CS引脚
    FLASH_SPI_CS_GPIO->BSHR = FLASH_SPI_CS;
}

//W25QXX写使能
//将WEL置位
void W25QXX_Write_Enable(void)          //写使能
{
    // 拉低CS引脚
    FLASH_SPI_CS_GPIO->BCR = FLASH_SPI_CS;
    WriteAndReadByteFromFlash_SPI(W25X_WriteEnable);
    // 拉高CS引脚
    FLASH_SPI_CS_GPIO->BSHR = FLASH_SPI_CS;
}

//W25QXX写禁止
//将WEL清零
void W25QXX_Write_Disable(void)     //写保护
{
    // 拉低CS引脚
    FLASH_SPI_CS_GPIO->BCR = FLASH_SPI_CS;
    WriteAndReadByteFromFlash_SPI(W25X_WriteDisable);
    // 拉高CS引脚
    FLASH_SPI_CS_GPIO->BSHR = FLASH_SPI_CS;
}

//SPI在一页(0~65535)内写入少于256个字节的数据
//在指定地址开始写入最大256字节的数据
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(24bit)
//NumByteToWrite:要写入的字节数(最大256),该数不应该超过该页的剩余字节数!!!
void W25QXX_Write_Page(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)
{
    u16 i;
    W25QXX_Write_Enable();
    // 拉低CS引脚
    FLASH_SPI_CS_GPIO->BCR = FLASH_SPI_CS;
    WriteAndReadByteFromFlash_SPI(W25X_PageProgram); //发送写页命令
    WriteAndReadByteFromFlash_SPI((u8)(WriteAddr >> 16)); //发送24bit地址
    WriteAndReadByteFromFlash_SPI((u8)(WriteAddr >> 8));
    WriteAndReadByteFromFlash_SPI((u8)(WriteAddr));

    for(i=0;i<NumByteToWrite;i++)
    { //循环写数
        WriteAndReadByteFromFlash_SPI(pBuffer[i]);
    }
    // 拉高CS引脚
    FLASH_SPI_CS_GPIO->BSHR = FLASH_SPI_CS;
    W25QXX_Wait_Busy();
}

//无检验写SPI FLASH
//必须确保所写的地址范围内的数据全部为0XFF,否则在非0XFF处写入的数据将失败!
//具有自动换页功能
//在指定地址开始写入指定长度的数据,但是要确保地址不越界!
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(24bit)
//NumByteToWrite:要写入的字节数(最大65535)
//CHECK OK
void W25QXX_Write_NoCheck(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)
{
    u16 pageremain;
    pageremain = 256 - WriteAddr%256; //单页剩余的字节数
    if(NumByteToWrite <= pageremain)
    { //不大于256个字节
        pageremain = NumByteToWrite;
    }
    while(1)
    {
        W25QXX_Write_Page(pBuffer,WriteAddr,pageremain);
        if(NumByteToWrite == pageremain)
        { //写入结束了
            break;
        }
        else
        {
            pBuffer += pageremain;
            WriteAddr += pageremain;

            NumByteToWrite -= pageremain; //减去已经写入了的字节数
            if(NumByteToWrite > 256)
            { //一次可以写入256个字节
                pageremain = 256;
            }
            else
            {
                pageremain = NumByteToWrite; //不够256个字节了
            }
        }
    }
}

//读取SPI FLASH
//在指定地址开始读取指定长度的数据
//pBuffer:数据存储区
//ReadAddr:开始读取的地址(24bit)
//NumByteToRead:要读取的字节数(最大65535)
void W25QXX_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead)   //读取flash
{
    u16 i;
    // 拉低CS引脚
    FLASH_SPI_CS_GPIO->BCR = FLASH_SPI_CS;
    WriteAndReadByteFromFlash_SPI(W25X_ReadData); //发送读指令
    WriteAndReadByteFromFlash_SPI((u8)(ReadAddr >> 16));   //发送24bit地址
    WriteAndReadByteFromFlash_SPI((u8)(ReadAddr >> 8));
    WriteAndReadByteFromFlash_SPI((u8)(ReadAddr));

    for(i=0;i<NumByteToRead;i++)
    {
        pBuffer[i] = WriteAndReadByteFromFlash_SPI(0xFF); // 读取数据
    }
    // 拉高CS引脚
    FLASH_SPI_CS_GPIO->BSHR = FLASH_SPI_CS;
}

//写SPI FLASH
//在指定地址开始写入指定长度的数据
//该函数带擦除操作!
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(24bit)
//NumByteToWrite:要写入的字节数(最大65535)
u8 W25QXX_BUFFER[4096];
void W25QXX_Write(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)//写入flash
{
    u32 secpos;
    u16 secoff;
    u16 secremain;
    u16 i;
    u8 * W25QXX_BUF;
    W25QXX_BUF = W25QXX_BUFFER;
    secpos = WriteAddr / 4096; //扇区地址
    secoff = WriteAddr % 4096; //在扇区内的偏移
    secremain = 4096 - secoff; //扇区剩余空间大小
    if(NumByteToWrite <= secremain)
    { //不大于4096个字节
        secremain = NumByteToWrite;
    }
    while(1)
    {
        W25QXX_Read(W25QXX_BUF,secpos*4096,4096); //读出整个扇区的内容
        for(i=0;i<secremain;i++)
        { //校验数据
            if(W25QXX_BUF[secoff+i] != 0xFF)
            { //需要擦除
                break;
            }
        }
        if(i<secremain)
        { //需要擦除
            W25QXX_Erase_Sector(secpos); //擦除这个扇区
            for(i=0;i<secremain;i++)
            { //复制
                W25QXX_BUF[i+secoff] = pBuffer[i];
            }
            W25QXX_Write_NoCheck(W25QXX_BUF,secpos*4096,4096); //写入整个扇区
        }
        else
        {
            W25QXX_Write_NoCheck(pBuffer,WriteAddr,secremain); //写已经擦除了的,直接写入扇区剩余区间.
        }

        if(NumByteToWrite == secremain)
        { //写入结束了
            break;
        }
        else
        { //写入未结束
            secpos++; //扇区地址增1
            secoff = 0; //偏移位置为0
            pBuffer += secremain; //指针偏移
            WriteAddr += secremain; //写地址偏移
            NumByteToWrite -= secremain; //字节数递减
            if(NumByteToWrite>4096)
            { //下一个扇区还是写不完
                secremain = 4096;
            }
            else
            { //下一个扇区可以写完了
                secremain = NumByteToWrite;
            }
        }
    }
}

//擦除整个芯片
//等待时间超长...
void W25QXX_Erase_Chip(void)            //整片擦除
{
    W25QXX_Write_Enable(); //SET WEL
    W25QXX_Wait_Busy();

    // 拉低CS引脚
    FLASH_SPI_CS_GPIO->BCR = FLASH_SPI_CS;
    WriteAndReadByteFromFlash_SPI(W25X_ChipErase); //发送片擦除命令
    // 拉高CS引脚
    FLASH_SPI_CS_GPIO->BSHR = FLASH_SPI_CS;

    W25QXX_Wait_Busy(); //等待芯片擦除结束
}

//擦除一个扇区
//Dst_Addr:扇区地址 根据实际容量设置
//擦除一个扇区的最少时间:150ms
void W25QXX_Erase_Sector(u32 Dst_Addr)  //扇区擦除
{
    Dst_Addr *= 4096;
    W25QXX_Write_Enable(); //SET WEL
    W25QXX_Wait_Busy();
    // 拉低CS引脚
    FLASH_SPI_CS_GPIO->BCR = FLASH_SPI_CS;
    WriteAndReadByteFromFlash_SPI(W25X_SectorErase); //发送扇区擦除指令
    WriteAndReadByteFromFlash_SPI((u8)(Dst_Addr >> 16)); //发送24bit地址
    WriteAndReadByteFromFlash_SPI((u8)(Dst_Addr >> 8));
    WriteAndReadByteFromFlash_SPI((u8)Dst_Addr);
    // 拉高CS引脚
    FLASH_SPI_CS_GPIO->BSHR = FLASH_SPI_CS;
    W25QXX_Wait_Busy(); //等待擦除完成
}

void W25QXX_Wait_Busy(void)             //等待空闲
{
    while((W25QXX_ReadSR() & 0x01) == 1);
}
void W25QXX_PowerDown(void)         //进入掉电模式
{
    // 拉低CS引脚
    FLASH_SPI_CS_GPIO->BCR = FLASH_SPI_CS;
    WriteAndReadByteFromFlash_SPI(W25X_PowerDown);
    // 拉高CS引脚
    FLASH_SPI_CS_GPIO->BSHR = FLASH_SPI_CS;
    HAL_Delay(3);
}
void W25QXX_WAKEUP(void)                //唤醒
{
    // 拉低CS引脚
    FLASH_SPI_CS_GPIO->BCR = FLASH_SPI_CS;
    WriteAndReadByteFromFlash_SPI(W25X_ReleasePowerDown);
    // 拉高CS引脚
    FLASH_SPI_CS_GPIO->BSHR = FLASH_SPI_CS;
    HAL_Delay(3);
}
