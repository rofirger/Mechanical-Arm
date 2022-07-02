/*
 * sram.h
 *
 *  Created on: 2022��6��30��
 *      Author: ���
 */

#ifndef SRAM_H_
#define SRAM_H_

#include "headfile.h"

#define Bank1_SRAM1_ADDR    ((u32)(0x60000000))
void FSMC_SRAM_Init(void);
void FSMC_SRAM_WriteBuffer(u8* pBuffer,u32 WriteAddr,u32 n);
void FSMC_SRAM_ReadBuffer(u8* pBuffer,u32 ReadAddr,u32 n);

#endif /* SRAM_H_ */
