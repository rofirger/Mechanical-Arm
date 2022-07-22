/*
 *      @File: joint.c
 *
 *      @Team: ɾ����·��
 *      @Author: ���
 */
#include "headfile.h"
#include "joint.h"
#include "arm_kinematic.h"
#include "msg_process.h"

// �����ĸ������ֵ��Ϊ�Ƕ�, ���ǻ���
// ��ǰ��е��ĩ�˵�ŷ��λ��, ǰ�����������������꣬�������������ԭ��X-Y-Z�̶�����ת��(����)
float EulerPosNow[6] = {0};
// ��Ŀ���е��ĩ�˵�ŷ��λ��, ǰ�����������������꣬�������������ԭ��X-Y-Z�̶�����ת��(����)
float EulerPosNew[6] = {0};
// ��ǰ��е�۹ؽڵ���ת��(�Ƕ�)
float JointRotationNow[6] = {0};
// Ŀ���е�۹ؽ���ת��(�Ƕ�)
float JointRotationNew[6] = {0};

JointStatus joint_status[6] = {0};

// �ñ���Ϊ��е���˶����̵���ʱ��
extern RotingPos roting_pos;

// ��е������ִ�е�����
RobotTask robot_task;
// ��е������״̬
RobotStatus robot_status;
// �Ƿ���ת������һ��״̬�Ĺ�����
RobotTransform robot_tranform;


void UpdateRobotTask(RobotTask _robot_task)
{
    robot_task = _robot_task;
}

RobotTask GetRobotTask()
{
    return robot_task;
}

void UpdateRobotStatus(RobotStatus _robot_status)
{
    robot_status = _robot_status;
}

RobotStatus GetRobotStatus()
{
    return robot_status;
}

void UpdateRobotTransform(RobotTransform _transform_status)
{
    robot_tranform = _transform_status;
}

RobotTransform GetRobotTransform()
{
    return robot_tranform;
}

void SetTruckPos()
{
    roting_pos._is_move_to_new_pos[0] = true;
    roting_pos._max_index = 1;
    roting_pos._now_index = 0;
    roting_pos._move_to_new_pos[0][0] = 0;
    roting_pos._move_to_new_pos[0][1] = 230;
    roting_pos._move_to_new_pos[0][2] = 280;
    roting_pos._move_to_new_pos[0][3] = 0;
    roting_pos._move_to_new_pos[0][4] = PI;
    roting_pos._move_to_new_pos[0][5] = 0;
    roting_pos._is_roting = true;
}
