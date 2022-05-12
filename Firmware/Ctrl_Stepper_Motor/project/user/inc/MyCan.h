/*
 * MyCan.h
 *
 *  Created on: 2022年5月3日
 *      Author: 随风
 */

#ifndef MYCAN_H_
#define MYCAN_H_
#include "zf_common_headfile.h".h"
void CAN_Mode_Init(uint8_t tsjw, uint8_t tbs2, uint8_t tbs1, uint16_t brp, uint8_t mode );
uint8_t CAN_Send_Msg(uint8_t *msg, uint8_t len);
uint8_t CAN_Receive_Msg(uint8_t *buf );
#endif /* MYCAN_H_ */
