/*
 * joint.h
 *
 *  Created on: 2022年7月5日
 *      Author: 随风
 */

#ifndef JOINT_H_
#define JOINT_H_

#include "arm_kinematic.h"
#include "joint.h"


// 减速器速比
#define SPEED_RATIO         26.8510
// 每个关节的相对与平衡(非初始化！！！)位置的可到达角度范围        注意是角度，而非弧度
#define JOINT1_MAX_ANGLE    180.0f
#define JOINT1_MIN_ANGLE    -180.0f
#define JOINT2_MAX_ANGLE    -10.12998f
#define JOINT2_MIN_ANGLE    -191.0f
#define JOINT3_MAX_ANGLE    180.0f
#define JOINT3_MIN_ANGLE    -10.87482f
#define JOINT4_MAX_ANGLE    180.0f
#define JOINT4_MIN_ANGLE    -180.0f
#define JOINT5_MAX_ANGLE    100.0f
#define JOINT5_MIN_ANGLE    -100.0f
#define JOINT6_MAX_ANGLE    180.0f
#define JOINT6_MIN_ANGLE    -180.0f

// 每个关节平衡位置的运动学角度，弧度表示
#define JOINT1_BALANCE_RAD  0.0f
#define JOINT2_BALANCE_RAD  PI
#define JOINT3_BALANCE_RAD  -PI_2
#define JOINT4_BALANCE_RAD  0.0f
#define JOINT5_BALANCE_RAD  0.0f
#define JOINT6_BALANCE_RAD  0.0f

// 每个关节可达运动学角度范围，角度表示
#define JOINT1_MAX_KINEMATICS_ANGLE     JOINT1_MAX_ANGLE
#define JOINT1_MIN_KINEMATICS_ANGLE     JOINT1_MIN_ANGLE
#define JOINT2_MAX_KINEMATICS_ANGLE     (JOINT2_MAX_ANGLE + 180.0f)
#define JOINT2_MIN_KINEMATICS_ANGLE     (JOINT2_MIN_ANGLE + 180.0f)
#define JOINT3_MAX_KINEMATICS_ANGLE     (JOINT3_MAX_ANGLE - 90.0f)
#define JOINT3_MIN_KINEMATICS_ANGLE     (JOINT3_MIN_ANGLE - 90.0f)
#define JOINT4_MAX_KINEMATICS_ANGLE     JOINT4_MAX_ANGLE
#define JOINT4_MIN_KINEMATICS_ANGLE     JOINT4_MIN_ANGLE
#define JOINT5_MAX_KINEMATICS_ANGLE     JOINT5_MAX_ANGLE
#define JOINT5_MIN_KINEMATICS_ANGLE     JOINT5_MIN_ANGLE
#define JOINT6_MAX_KINEMATICS_ANGLE     JOINT6_MAX_ANGLE
#define JOINT6_MIN_KINEMATICS_ANGLE     JOINT6_MIN_ANGLE

typedef struct JointRotationPos
{
    int _balance_pos;                   // 平衡点，注意该值代表编码器的读数(已经过解码)
    int _now_pos;                       // 当前下的编码器读数
    int _now_offset_balance;            // 相对编码器读数(已经过解码)   当前位置-平衡位置
    int _target_offset_balance;         // 目标
    int _init_pos_offset_balance;       // 初始位置相对平衡位置的偏差
}JointRotationPos;

typedef enum JointStatus
{
    TO_BE_INITED,
    INITED,
    ROTING_TO_NEW_POS,
    STAY_IN_POS
}JointStatus;

extern JointStatus joint_status[6];

void InitRobot(void);
void BackRobot(void);

#endif /* JOINT_H_ */
