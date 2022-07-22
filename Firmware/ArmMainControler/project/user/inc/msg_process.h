/*
 *      @File: msg_process.h
 *
 *      @Team: 删库跑路队
 *      @Author: 随风
 */

#ifndef MSG_PROCESS_H_
#define MSG_PROCESS_H_

#include "headfile.h"
#include "MyCan.h"
#include "Config.h"
#include "WCHNET.h"
#include "string.h"
#include "ETH.h"
#include "arm_kinematic.h"

typedef struct RotingPos
{
    bool _is_move_to_new_pos[10];
    bool _is_roting;
    float _move_to_new_pos[10][6];          // 欧拉参数
    uint32_t _now_index;
    uint32_t _max_index;
}RotingPos;

void ETH_MsgProcess(char* _eth_msg);
void CAN_MsgProcess(char* _joint_msg);
void InitRobot(void);
void BackRobot(void);
void WakeRobot(void);
void StartUart();
void CloseUart();
void QueryJointStatus(void);
void InitRotingPos();
void MainLoop();

#endif /* MSG_PROCESS_H_ */
