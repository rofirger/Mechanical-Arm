/*
 *      @File: joint.c
 *
 *      @Team: 删库跑路队
 *      @Author: 随风
 */
#include "headfile.h"
#include "joint.h"
#include "arm_kinematic.h"
#include "msg_process.h"

// 以下四个数组的值均为角度, 而非弧度
// 当前机械臂末端的欧拉位置, 前三个代表相对零点坐标，后三个代表相对原点X-Y-Z固定角旋转角(弧度)
float EulerPosNow[6] = {0};
// 新目标机械臂末端的欧拉位置, 前三个代表相对零点坐标，后三个代表相对原点X-Y-Z固定角旋转角(弧度)
float EulerPosNew[6] = {0};
// 当前机械臂关节的旋转角(角度)
float JointRotationNow[6] = {0};
// 目标机械臂关节旋转角(角度)
float JointRotationNew[6] = {0};

JointStatus joint_status[6] = {0};

// 该变量为机械臂运动过程的临时点
extern RotingPos roting_pos;

// 机械臂正在执行的任务
RobotTask robot_task;
// 机械臂整体状态
RobotStatus robot_status;
// 是否处于转换到下一个状态的过程中
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
