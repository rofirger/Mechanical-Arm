/*
 * msg_process.h
 *
 *  Created on: 2022��7��5��
 *      Author: ���
 */

#ifndef MSG_PROCESS_H_
#define MSG_PROCESS_H_

#include "Motor.h"

void CAN_MsgProcess(char* _can_msg);
void SendBackChangeEncoder(const RotionDir _dir, int _num);
void KeepPosSendBroadcastMsg();
void RotingSendBroadcastMsg();
#endif /* MSG_PROCESS_H_ */
