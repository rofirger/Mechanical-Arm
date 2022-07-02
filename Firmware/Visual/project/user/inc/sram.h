/*
 * sram.h
 *
 *  Created on: 2022年6月30日
 *      Author: 随风
 */

#ifndef SRAM_H_
#define SRAM_H_

#include "headfile.h"

#define Bank1_SRAM1_ADDR    ((u32)(0x60000000))
void FSMC_SRAM_Init(void);
void FSMC_SRAM_WriteBuffer(u8* pBuffer,u32 WriteAddr,u32 n);
void FSMC_SRAM_ReadBuffer(u8* pBuffer,u32 ReadAddr,u32 n);

#endif /* SRAM_H_ */
