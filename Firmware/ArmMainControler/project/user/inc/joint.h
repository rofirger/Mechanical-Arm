/*
 * joint.h
 *
 *  Created on: 2022��7��5��
 *      Author: ���
 */

#ifndef JOINT_H_
#define JOINT_H_

#include "arm_kinematic.h"
#include "joint.h"


// �������ٱ�
#define SPEED_RATIO         26.8510
// ÿ���ؽڵ������ƽ��(�ǳ�ʼ��������)λ�õĿɵ���Ƕȷ�Χ        ע���ǽǶȣ����ǻ���
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

// ÿ���ؽ�ƽ��λ�õ��˶�ѧ�Ƕȣ����ȱ�ʾ
#define JOINT1_BALANCE_RAD  0.0f
#define JOINT2_BALANCE_RAD  PI
#define JOINT3_BALANCE_RAD  -PI_2
#define JOINT4_BALANCE_RAD  0.0f
#define JOINT5_BALANCE_RAD  0.0f
#define JOINT6_BALANCE_RAD  0.0f

// ÿ���ؽڿɴ��˶�ѧ�Ƕȷ�Χ���Ƕȱ�ʾ
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
    int _balance_pos;                   // ƽ��㣬ע���ֵ����������Ķ���(�Ѿ�������)
    int _now_pos;                       // ��ǰ�µı���������
    int _now_offset_balance;            // ��Ա���������(�Ѿ�������)   ��ǰλ��-ƽ��λ��
    int _target_offset_balance;         // Ŀ��
    int _init_pos_offset_balance;       // ��ʼλ�����ƽ��λ�õ�ƫ��
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
