/*
 * joint.c
 *
 *  Created on: 2022��7��5��
 *      Author: ���
 */
#include "headfile.h"
#include "joint.h"
#include "arm_kinematic.h"


// �����ĸ������ֵ��Ϊ�Ƕ�, ���ǻ���
// ��ǰ��е��ĩ�˵�ŷ��λ��, ǰ�����������������꣬�������������ԭ��X-Y-Z�̶�����ת��(����)
float EulerPosNow[6];
// ��Ŀ���е��ĩ�˵�ŷ��λ��, ǰ�����������������꣬�������������ԭ��X-Y-Z�̶�����ת��(����)
float EulerPosNew[6];
// ��ǰ��е�۹ؽڵ���ת��(�Ƕ�)
float JointRotationNow[6];
// Ŀ���е�۹ؽ���ת��(�Ƕ�)
float JointRotationNew[6];

