/*
 * Motor.h
 *
 *  Created on: 2022��4��21��
 *      Author: ���
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "MT6816.h"
#include "MyCan.h"

// ������������������GPIO�������
#define AP_STEP D11
#define AN_STEP D9
#define BP_STEP D15
#define BN_STEP D13
// �����������ϵ�ָʾ��
#define INDICATOR E2
#define ABS(_num)      ((_num) >= 0 ? (_num) : (-(_num)))
// �������ٱ�
#if (AXIS6 == 1)
#define SPEED_RATIO         25
#else
#define SPEED_RATIO         26.8510
#endif
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

// ��ת��Ч����������
#define INVALID_ROTION_ENCODER  45

#if (AXIS1 == 1)
// �������¿�����ʱ�뷽��û�л�е��������������ʱ�뷽���˶�����λ��
#define INIT_POS_ANGLE          308
#define BALANCE_POS_ANGLE       308
#endif

#if (AXIS2 == 1)
#define INIT_POS_ANGLE          141
#define BALANCE_POS_ANGLE       74
#endif

#if (AXIS3 == 1)
#define INIT_POS_ANGLE          46
#define BALANCE_POS_ANGLE       96
#endif

#if (AXIS4 == 1)
#define INIT_POS_ANGLE          225
#define BALANCE_POS_ANGLE       225
#endif

#if (AXIS5 == 1)
#define INIT_POS_ANGLE          119
#define BALANCE_POS_ANGLE       119
#endif

#if (AXIS6 == 1)
#define INIT_POS_ANGLE          68
#define BALANCE_POS_ANGLE       68
#endif

typedef struct JointRotationPos
{
    int _balance_pos;                   // ƽ��㣬ע���ֵ����������Ķ���(�Ѿ�������)
    int _now_pos;                       // ��ǰ�µı���������
    int _now_offset_balance;            // ��Ա���������(�Ѿ�������)   ��ǰλ��-ƽ��λ��
    int _target_offset_balance;         // Ŀ��
    int _init_pos_offset_balance;       // ��ʼλ�����ƽ��λ�õ�ƫ��
}JointRotationPos;

typedef enum RotionDir
{
    INCREASE_ENCODER,
    DECREASE_ENCODER
}RotionDir;

typedef struct RotionStatus
{
    RotionDir _last_rotion_dir;
    RotionDir _next_rotion_dir;
}RotionStatus;

typedef enum JointStatus
{
    TO_BE_INITED,
    INITED,
    ROTING_TO_NEW_POS,
    STAY_IN_POS
}JointStatus;

void CV_MotorStep(uint16_t _times, uint16_t _ms_interval);
void CCV_MotorStep(uint16_t _times, uint16_t _ms_interval);
void KeepPos();
void SetPos(const float _motor_angle);
void ErrorCompensation(const int _now_offset_balance, int* _target_offset_balance);
#endif /* MOTOR_H_ */
