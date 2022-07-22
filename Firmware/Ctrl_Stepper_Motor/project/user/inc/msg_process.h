/*
 *      @File: msg_process.h
 *
 *      @Team: É¾¿âÅÜÂ·¶Ó
 *      @Author: Ëæ·ç
 */

#ifndef MSG_PROCESS_H_
#define MSG_PROCESS_H_

#include "Motor.h"

void CAN_MsgProcess(char* _can_msg);
void SendBackChangeEncoder(const RotionDir _dir, int _num);
void KeepPosSendBroadcastMsg();
void RotingSendBroadcastMsg();
void SendBackStatus(void);
#endif /* MSG_PROCESS_H_ */
