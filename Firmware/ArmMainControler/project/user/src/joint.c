/*
 * joint.c
 *
 *  Created on: 2022年7月5日
 *      Author: 随风
 */
#include "headfile.h"
#include "joint.h"
#include "arm_kinematic.h"


// 以下四个数组的值均为角度, 而非弧度
// 当前机械臂末端的欧拉位置, 前三个代表相对零点坐标，后三个代表相对原点X-Y-Z固定角旋转角(弧度)
float EulerPosNow[6];
// 新目标机械臂末端的欧拉位置, 前三个代表相对零点坐标，后三个代表相对原点X-Y-Z固定角旋转角(弧度)
float EulerPosNew[6];
// 当前机械臂关节的旋转角(角度)
float JointRotationNow[6];
// 目标机械臂关节旋转角(角度)
float JointRotationNew[6];

