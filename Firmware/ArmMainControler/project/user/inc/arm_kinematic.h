/*
 * arm_kinematic.h
 *
 *  Created on: Jun 21, 2022
 *      Author: ���
 */

#ifndef ARM_KINEMATIC_H_
#define ARM_KINEMATIC_H_

#include "headfile.h"

#ifndef bool
#define bool        unsigned char
#endif
#ifndef false
#define false       0
#endif
#ifndef true
#define true        1
#endif

// 6R��е�����˲�������. �ֱ�Ϊ���� X ˳ʱ����ת���� X ����ƽ�ơ���Z����ƽ��
// ��ת��λ:��   ƽ�Ƶ�λ: mm
// ��ȡDH����XZ�任(�Ľ�DH����)
#define DH_BASE_HEIGHT          152.700f
#define DH_BASE_R1_L            30.000f
#define DH_R1_R2_L              186.721f
#define DH_R2_R3_L              68.249f
#define DH_R3_R4_L              190.229f
#define DH_R4_R5_L              125.500f

#define PI                      3.14159265358979323846f   // pi
#define PI_2                    1.57079632679489661923f   // pi/2
#define PI_4                    0.785398163397448309616f  // pi/4

#define RAD_TO_DEG              57.29577951308f

#define ABS(_num)      ((_num) >= 0 ? (_num) : (-(_num)))
typedef struct IK_AngleSolve
{
    uint8_t _num_joint3_solve;
    float _joint3[4];
    float _joint1[8];
    float _joint2[8];
    float _joint4[8];
    float _joint5[8];
    float _joint6[8];
}IK_AngleSolve;
float DegToRad(const float _deg);
float RadToDeg(const float _rad);
void LinkToTransformMat(const float* _link_param, float* _out_transform_mat);
void RotationMatToEulerAngle(const float* _rot_mat, float* _euler_angle);
void EulerAngleToRotationMat(const float* _euler_angle, float* _rot_mat);
void EulerPosToTranformMat(const float* _euler_pos, float* _trans_mat);
void RobotFK(const float* _joint_rotation, float* _output_joint_six_param);
bool RobotIK(const float* _joint_rotation, IK_AngleSolve* _output_solve, const float* _last_joint);
bool EulerPosToJointAngle(const float* _euler_pos, float* _joint_angles);
#endif /* ARM_KINEMATIC_H_ */
