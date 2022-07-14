/*
 * msg_process.h
 *
 *  Created on: Jun 30, 2022
 *      Author: Ëæ·ç
 */

#ifndef MSG_PROCESS_H_
#define MSG_PROCESS_H_

#include "headfile.h"
#include "MyCan.h"
#include "Config.h"
#include "WCHNET.h"
#include "string.h"
#include "ETH.h"

void ETH_MsgProcess(char* _eth_msg);
void CAN_MsgProcess(char* _joint_msg);
void InitRobot(void);
void BackRobot(void);
void WakeRobot(void);
void StartUart();
void CloseUart();
void QueryJointStatus(void);
#endif /* MSG_PROCESS_H_ */
