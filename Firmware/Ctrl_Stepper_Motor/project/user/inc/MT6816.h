/*
 * ctrl_stepper_motor_init.h
 *
 *  Created on: 2022��4��19��
 *      Author: ���
 */

#ifndef MT6816_H_
#define MT6816_H_
#include "zf_common_headfile.h"
#include "zf_driver_gpio.h"
#include "zf_driver_spi.h"

typedef uint8_t bool;
#define true  1
#define false 0

// ����MT6816�����Ϣ
#define MT_SPI      SPI_1
#define MT_SPI_MODE SPI_MODE3
#define MT_SCK      SPI1_SCK_A5
#define MT_MOSI     SPI1_MOSI_A7
#define MT_MISO     SPI1_MISO_A6
#define MT_CS       A4

// MT6816�����Ϣ�ṹ��
typedef struct MT6816_Structure
{
    // ԭʼ�Ƕ���Ϣ
    uint16_t _raw_angle;
    // �������������ĽǶ���Ϣ
    uint16_t _decode_angle;
    // ��MT6816�޷���⵽�㹻�Ĵų�����������ʱ���ñ�־λ��Ϊ1
    bool _no_mag_warning;
}MT6816_Structure;

void MT6816_Init();
void MT6816_SetZero();
uint16_t MT6816_SendRead16bits(uint16_t send_data);
bool MT6816_ReadAngle(MT6816_Structure* mt6816_structure);
void MT6816_SpiTransfer16Bits (spi_index_enum spi_n, uint16 *write_buffer, uint16 *read_buffer, uint32 len);
void InitPos();
#endif /* MT6816_H_ */
