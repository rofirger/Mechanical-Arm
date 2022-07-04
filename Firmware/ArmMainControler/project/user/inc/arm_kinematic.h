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
#define DH_BASE_HEIGHT          152.7
#define DH_BASE_R1_L            30
#define DH_R1_R2_L              186.721
#define DH_R2_R3_L              68.249
#define DH_R3_R4_L              190.229
#define DH_R4_R5_L              125.5

#define PI                      3.14159265358979323846   // pi
#define PI_2                    1.57079632679489661923   // pi/2
#define PI_4                    0.785398163397448309616  // pi/4

#define RAD_TO_DEG              57.29577951308f

#define ABS(_num)      ((_num) >= 0 ? (_num) : (-(_num)))
typedef struct IK_AngleSolve
{
    uint8_t _num_solve;
    float _solve[16][6];
}IK_AngleSlove;

void RobotFK(const float* _joint_rotation, float* _output_joint_six_param);
void RobotIK(const float* _joint_rotation, IK_AngleSlove* _output_solve);

#endif /* ARM_KINEMATIC_H_ */
