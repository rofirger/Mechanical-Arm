/*
 * w25q128.h
 *
 *  Created on: 2022��6��6��
 *      Author: ���
 */

#ifndef W25Q128_H_
#define W25Q128_H_
#include "ch32v30x_conf.h"

#define W25Q128 0XEF17
//ָ���
#define W25X_WriteEnable        0x06
#define W25X_WriteDisable       0x04
#define W25X_ReadStatusReg      0x05
#define W25X_WriteStatusReg     0x01
#define W25X_ReadData           0x03
#define W25X_FastReadData       0x0B
#define W25X_FastReadDual       0x3B
#define W25X_PageProgram        0x02
#define W25X_BlockErase         0xD8
#define W25X_SectorErase        0x20
#define W25X_ChipErase          0xC7
#define W25X_PowerDown          0xB9
#define W25X_ReleasePowerDown   0xAB
#define W25X_DeviceID           0xAB
#define W25X_ManufactDeviceID   0x90
#define W25X_JedecDeviceID      0x9F

void W25QXX_Init(void);
uint16_t  W25QXX_ReadID(void);               //��ȡFLASH ID
uint8_t   W25QXX_ReadSR(void);               //��ȡ״̬�Ĵ���
void W25QXX_Write_SR(uint8_t sr);            //д״̬�Ĵ���
void W25QXX_Write_Enable(void);         //дʹ��
void W25QXX_Write_Disable(void);        //д����
void W25QXX_Write_NoCheck(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite);
void W25QXX_Read(uint8_t* pBuffer,uint32_t ReadAddr,uint16_t NumByteToRead);   //��ȡflash
void W25QXX_Write(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite);//д��flash
void W25QXX_Erase_Chip(void);           //��Ƭ����
void W25QXX_Erase_Sector(uint32_t Dst_Addr); //��������
void W25QXX_Wait_Busy(void);            //�ȴ�����
void W25QXX_PowerDown(void);            //�������ģʽ
void W25QXX_WAKEUP(void);               //����


#endif /* W25Q128_H_ */
