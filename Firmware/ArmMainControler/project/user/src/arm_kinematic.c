/*
 * arm_kinematic.c
 *
 *  Created on: Jun 21, 2022
 *      Author: 随风
 */

/*
 * @note:关于MounRiver Studio环境下的数学库math.h的使用, 在GNU RISC-V Cross C Linker下的Libraries(-l)下添加  m
 */

#include "arm_kinematic.h"
#include "Config.h"
#include "headfile.h"
#include "joint.h"
#include "math.h"

// 连杆参数表
const float link_parameter[6][4] = {
        {0, 0, DH_BASE_HEIGHT, 0},
        {PI_2, DH_BASE_R1_L, 0, 0},
        {0, DH_R1_R2_L, 0, 0},
        {PI_2, DH_R2_R3_L, DH_R3_R4_L, 0},
        {PI_2, 0, 0, 0},
        {-PI_2, 0, DH_R4_R5_L, 0},
};

// 机械臂pieper末端到实际末端变换矩阵
float PiePerTranforMat[16] = { 1, 0, 0, 0,
                               0, 1, 0, 0,
                               0, 0, 1, DH_R4_R5_L,
                               0, 0, 0, 1};
// 机械臂实际末端到pieper末端的变换矩阵
float PosePieperTranformMat[16] = { 1, 0, 0, 0,
                                    0, 1, 0, 0,
                                    0, 0, 1, -DH_R4_R5_L,
                                    0, 0, 0, 1};

// 当前机械臂末端的欧拉位置, 前三个代表相对零点坐标，后三个代表相对原点X-Y-Z固定角旋转角
extern float EulerPosNow[6];
// 新目标机械臂末端的欧拉位置, 前三个代表相对零点坐标，后三个代表相对原点X-Y-Z固定角旋转角
extern float EulerPosNew[6];
// 当前机械臂关节的旋转角
extern float JointRotationNow[6];
// 目标机械臂关节旋转角
extern float JointRotationNew[6];
// 逆解集合
IK_AngleSolve IK_Angles;

/*
 * @brief:角度换算弧度
 */
inline float DegToRad(const float _deg)
{
    return _deg / RAD_TO_DEG;
}

/*
 * @brief:弧度换算角度
 */
inline float RadToDeg(const float _rad)
{
    return _rad * RAD_TO_DEG;
}

/*
 * @brief:     根据连杆参数求连杆变换矩阵
 * @param:     _link_param  6*4连杆参数表;       _out_transform_mat  6连杆变换矩阵
 */
void LinkToTransformMat(const float* _link_param, float* _out_transform_mat)
{
    for (int _i = 0; _i < 6; ++_i)
    {
        _out_transform_mat[_i * 4 + 0] = cos(_link_param[_i * 4 + 3]);
        _out_transform_mat[_i * 4 + 1] = -sin(_link_param[_i * 4 + 3]);
        _out_transform_mat[_i * 4 + 2] = 0;
        _out_transform_mat[_i * 4 + 3] = _link_param[_i * 4 + 1];

        _out_transform_mat[_i * 4 + 4] = sin(_link_param[_i * 4 + 3]) * cos(_link_param[_i * 4]);
        _out_transform_mat[_i * 4 + 5] = cos(_link_param[_i * 4 + 3]) * cos(_link_param[_i * 4]);
        _out_transform_mat[_i * 4 + 6] = -sin(_link_param[_i * 4]);
        _out_transform_mat[_i * 4 + 7] = -sin(_link_param[_i * 4]) * _link_param[_i * 4 + 2];

        _out_transform_mat[_i * 4 + 8] = sin(_link_param[_i * 4 + 3]) * sin(_link_param[_i * 4]);
        _out_transform_mat[_i * 4 + 9] = cos(_link_param[_i * 4 + 3]) * sin(_link_param[_i * 4]);
        _out_transform_mat[_i * 4 + 10] = cos(_link_param[_i * 4]);
        _out_transform_mat[_i * 4 + 11] = cos(_link_param[_i * 4]) * _link_param[_i * 4 + 2];

        _out_transform_mat[_i * 4 + 12] = 0;
        _out_transform_mat[_i * 4 + 13] = 0;
        _out_transform_mat[_i * 4 + 14] = 0;
        _out_transform_mat[_i * 4 + 15] = 1;
    }
}

/*
 * @brief:矩阵相乘计算
 */
void MatMultiply(const float* _matrix_a, const float* _matrix_b, float* _matrix_out, const int _row_a, const int _col_a, const int _col_b)
{
    float tmp;
    for (int _i = 0; _i < _row_a; ++_i)
    {
        for (int _j = 0; _j < _col_b; ++_j)
        {
            tmp = 0.0;
            for (int _k = 0; _k < _col_a; ++_k)
            {
                tmp += _matrix_a[_col_a * _i + _k] * _matrix_b[_col_b * _k + _j];
            }
            _matrix_out[_col_b * _i + _j] = tmp;
        }
    }
}

void MatTranspose(const float* _matrix_in, const int _row, const int _col, float* _matrix_out)
{
    for (int _i = 0; _i < _row; ++_i)
    {
        for (int _j = 0; _j < _col; ++_j)
        {
            _matrix_out[_i * _col + _j] = _matrix_in[_j * _col + _i];
        }
    }
}

/*
 * @brief:根据旋转矩阵求X-Y—Z固定旋转角
 */
void RotationMatToEulerAngle(const float* _rot_mat, float* _euler_angle)
{
    // 分情况讨论
    if (fabsf(_rot_mat[6]) > 1 - 0.0001)    // 等于1
    {
        if (_rot_mat[6] < 0)
        {
            _euler_angle[0] = 0;
            _euler_angle[1] = PI_2;
            _euler_angle[2] = atan2f(_rot_mat[1], _rot_mat[4]);
        }
        else
        {
            _euler_angle[0] = 0;
            _euler_angle[1] = -PI_2;
            _euler_angle[2] = -atan2f(_rot_mat[1], _rot_mat[4]);
        }
        return;
    }
    _euler_angle[1] = atan2f(-_rot_mat[6], sqrtf(_rot_mat[0] * _rot_mat[0] + _rot_mat[3] * _rot_mat[3]));
    float temp = cosf(_euler_angle[1]);
    _euler_angle[0] = atan2f(_rot_mat[3] / temp, _rot_mat[0] / temp);
    _euler_angle[2] = atan2f(_rot_mat[7] / temp, _rot_mat[8] / temp);
}

/*
 * @brief:根据X-Y—Z固定旋转角求旋转矩阵
 */
void EulerAngleToRotationMat(const float* _euler_angle, float* _rot_mat)
{
    float ca = cosf(_euler_angle[0]);
    float sa = sinf(_euler_angle[0]);
    float cb = cosf(_euler_angle[1]);
    float sb = cosf(_euler_angle[1]);
    float cr = cosf(_euler_angle[2]);
    float sr = cosf(_euler_angle[2]);

    _rot_mat[0] = ca * cb;
    _rot_mat[1] = ca * sb * sr - sa * cr;
    _rot_mat[2] = ca * sb * cr + sa * sr;

    _rot_mat[3] = sa * cb;
    _rot_mat[4] = sa * sb * sr + ca * cr;
    _rot_mat[5] = sa * sb * cr - ca * sr;

    _rot_mat[6] = -sb;
    _rot_mat[7] = cb * sr;
    _rot_mat[8] = cb * cr;
}

/*
* @brief:根据欧拉位置求取相对原点方位变换矩阵
* @param:_euler_pos[float*]:前三个代表相对零点坐标，后三个代表相对原点X-Y-Z固定角旋转角        _trans_mat[float*]:4*4矩阵
*/
void EulerPosToTranformMat(const float* _euler_pos, float* _trans_mat)
{
    _trans_mat[3] = _euler_pos[0];
    _trans_mat[7] = _euler_pos[1];
    _trans_mat[11] = _euler_pos[2];
    _trans_mat[12] = 0;
    _trans_mat[13] = 0;
    _trans_mat[14] = 0;
    _trans_mat[15] = 1;


    float ca = cosf(_euler_pos[3]);
    float sa = sinf(_euler_pos[3]);
    float cb = cosf(_euler_pos[4]);
    float sb = sinf(_euler_pos[4]);
    float cr = cosf(_euler_pos[5]);
    float sr = sinf(_euler_pos[5]);

    _trans_mat[0] = ca * cb;
    _trans_mat[1] = ca * sb * sr - sa * cr;
    _trans_mat[2] = ca * sb * cr + sa * sr;

    _trans_mat[4] = sa * cb;
    _trans_mat[5] = sa * sb * sr + ca * cr;
    _trans_mat[6] = sa * sb * cr - ca * sr;

    _trans_mat[8] = -sb;
    _trans_mat[9] = cb * sr;
    _trans_mat[10] = cb * cr;
}

/*
 * @brief:运动学正解
 * @param: _joint_rotation[float*]:连杆参数矩阵               _output_joint_six_param[float*]:输出六个参数，前三个代表相对零点坐标，后三个代表相对原点X-Y-Z固定角旋转角
 */
void RobotFK(const float* _joint_rotation, float* _output_joint_six_param)
{
    float _transform_mat_a[16];
    float _transform_mat_b[16];
    float _transform_mat_out[16];
    float _cos_a = cosf(_joint_rotation[0]);
    float _sin_a = sinf(_joint_rotation[0]);
    float _cos_c = cosf(_joint_rotation[3]);
    float _sin_c = sinf(_joint_rotation[3]);
    _transform_mat_a[0] = _cos_c;
    _transform_mat_a[1] = -_sin_c;
    _transform_mat_a[2] = 0;
    _transform_mat_a[3] = _joint_rotation[1];
    _transform_mat_a[4] = _sin_c * _cos_a;
    _transform_mat_a[5] = _cos_c * _cos_a;
    _transform_mat_a[6] = -_sin_a;
    _transform_mat_a[7] = -_sin_a * _joint_rotation[2];
    _transform_mat_a[8] = _sin_c * _sin_a;
    _transform_mat_a[9] = _cos_c * _sin_a;
    _transform_mat_a[10] = _cos_a;
    _transform_mat_a[11] = _cos_a * _joint_rotation[2];
    _transform_mat_a[12] = 0;
    _transform_mat_a[13] = 0;
    _transform_mat_a[14] = 0;
    _transform_mat_a[15] = 1;
    for (int _i = 1; _i < 6; ++_i)
    {
        _cos_a = cosf(_joint_rotation[_i * 4 + 0]);
        _sin_a = sinf(_joint_rotation[_i * 4 + 0]);
        _cos_c = cosf(_joint_rotation[_i * 4 + 3]);
        _sin_c = sinf(_joint_rotation[_i * 4 + 3]);
        _transform_mat_b[0] = _cos_c;
        _transform_mat_b[1] = -_sin_c;
        _transform_mat_b[2] = 0;
        _transform_mat_b[3] = _joint_rotation[_i * 4 + 1];
        _transform_mat_b[4] = _sin_c * _cos_a;
        _transform_mat_b[5] = _cos_c * _cos_a;
        _transform_mat_b[6] = -_sin_a;
        _transform_mat_b[7] = -_sin_a * _joint_rotation[_i * 4 + 2];
        _transform_mat_b[8] = _sin_c * _sin_a;
        _transform_mat_b[9] = _cos_c * _sin_a;
        _transform_mat_b[10] = _cos_a;
        _transform_mat_b[11] = _cos_a * _joint_rotation[_i * 4 + 2];
        _transform_mat_b[12] = 0;
        _transform_mat_b[13] = 0;
        _transform_mat_b[14] = 0;
        _transform_mat_b[15] = 1;
        MatMultiply(_transform_mat_a, _transform_mat_b, _transform_mat_out, 4, 4, 4);
        memcpy(_transform_mat_a, _transform_mat_out, 16 * sizeof(float));
    }
    _output_joint_six_param[0] = _transform_mat_out[3];
    _output_joint_six_param[1] = _transform_mat_out[7];
    _output_joint_six_param[2] = _transform_mat_out[11];
    float _temp[9];
    for (int _i = 0; _i < 3; ++_i)
    {
        _temp[_i * 3 + 0] = _transform_mat_out[_i * 4 + 0];
        _temp[_i * 3 + 1] = _transform_mat_out[_i * 4 + 1];
        _temp[_i * 3 + 2] = _transform_mat_out[_i * 4 + 2];
    }
    RotationMatToEulerAngle(_temp, &_output_joint_six_param[3]);
}

/*
 * @brief:运动学逆解
 * @param:  _joint_rotation[const float*]:末端目标点相对原点的变换矩阵                _output_solve[IK_AngleSlove*]:未经选择的六轴角度解
 */
bool RobotIK(const float* _joint_rotation, IK_AngleSolve* _output_solve, const float* _last_joint)
{
    /*
    * 此机械臂一般存在 8 个逆解。具体请看代码分析
    */
    float* _joint3 = _output_solve->_joint3;
    unsigned char _joint3_solve_num = 0;
    float* _joint1 = _output_solve->_joint1;
    float* _joint2 = _output_solve->_joint2;
    float* _joint4 = _output_solve->_joint4;
    float* _joint5 = _output_solve->_joint5;
    float* _joint6 = _output_solve->_joint6;
    for(uint8_t _i = 0; _i < 8; ++_i)
    {
        if (_i < 4)
            _joint3[_i] =  -6666.66;
        _joint1[_i] =  -6666.66;
        _joint2[_i] =  -6666.66;
        _joint4[_i] =  -6666.66;
        _joint5[_i] =  -6666.66;
        _joint6[_i] =  -6666.66;
    }

    float _x = _joint_rotation[3];
    float _y = _joint_rotation[7];
    float _z = _joint_rotation[11];
    float _r_2 = _x * _x + _y * _y + _z * _z;
    float _k3_solve_a = 1;
    float _k3_solve_b = -(2.0f * _r_2 + 4.0f * link_parameter[1][1] * link_parameter[1][1]);
    float _k3_solve_c = _r_2 * _r_2 + 4.0f * link_parameter[1][1] * link_parameter[1][1] * (powf(_z - link_parameter[0][2], 2) +
        link_parameter[1][1] * link_parameter[1][1] + 2 * link_parameter[0][2] * _z - link_parameter[0][2] * link_parameter[0][2]);
    float _k3_judge = powf(_k3_solve_b, 2) - 4.0 * _k3_solve_a * _k3_solve_c;
    if (_k3_judge > -0.000001f)
    {
        _k3_judge = fabsf(_k3_judge);
        // 存在解
        float _k3_solve_1 = (-_k3_solve_b - sqrtf(_k3_judge)) / (2.0f * _k3_solve_a);
        float _k3_solve_2 = (-_k3_solve_b + sqrtf(_k3_judge)) / (2.0f * _k3_solve_a);
        float _tmp_h = link_parameter[3][1] * link_parameter[3][1] + link_parameter[3][2] * link_parameter[3][2] +
            link_parameter[2][1] * link_parameter[2][1] + link_parameter[1][1] * link_parameter[1][1] +
            2 * link_parameter[0][2] * _z - link_parameter[0][2] * link_parameter[0][2];

        float _u3_solve_a_1 = _tmp_h - _k3_solve_1 - 2.0f * link_parameter[2][1] * link_parameter[3][1];
        float _u3_solve_b_1 = 4 * link_parameter[2][1] * link_parameter[3][2];
        float _u3_solve_c_1 = 2 * link_parameter[2][1] * link_parameter[3][1] + _tmp_h - _k3_solve_1;
        float _u_3_judge_1 = powf(_u3_solve_b_1, 2) - 4.0f * _u3_solve_a_1 * _u3_solve_c_1;

        float _u3_solve_a_2 = _tmp_h - _k3_solve_2 - 2.0f * link_parameter[2][1] * link_parameter[3][1];
        float _u3_solve_b_2 = _u3_solve_b_1;
        float _u3_solve_c_2 = 2 * link_parameter[2][1] * link_parameter[3][1] + _tmp_h - _k3_solve_2;
        float _u_3_judge_2 = powf(_u3_solve_b_2, 2) - 4.0f * _u3_solve_a_2 * _u3_solve_c_2;

        float _joint3_tmp[4]; unsigned char _joint3_tmp_solve_num = 0;
        // 分类讨论
        if (_u_3_judge_1 > -0.000001f)
        {
            _u_3_judge_1 = fabsf(_u_3_judge_1);
            float _u3_solve_1 = (-_u3_solve_b_1 - sqrtf(_u_3_judge_1)) / (2 * _u3_solve_a_1);
            float _u3_solve_2 = (-_u3_solve_b_1 + sqrtf(_u_3_judge_1)) / (2 * _u3_solve_a_1);
            // joint3角度解
            float _joint3_1 = 2 * atanf(_u3_solve_1);
            float _joint3_2 = 2 * atanf(_u3_solve_2);
            _joint3_tmp[_joint3_tmp_solve_num + 0] = _joint3_1;
            _joint3_tmp[_joint3_tmp_solve_num + 1] = _joint3_2;
            _joint3_tmp_solve_num += 2;
        }
        if (_u_3_judge_2 > -0.000001f)
        {
            _u_3_judge_2 = fabsf(_u_3_judge_2);
            float _u3_solve_3 = (-_u3_solve_b_2 - sqrtf(_u_3_judge_2)) / (2 * _u3_solve_a_2);
            float _u3_solve_4 = (-_u3_solve_b_2 + sqrtf(_u_3_judge_2)) / (2 * _u3_solve_a_2);
            // joint3角度解
            float _joint3_3 = 2 * atanf(_u3_solve_3);
            float _joint3_4 = 2 * atanf(_u3_solve_4);
            _joint3_tmp[_joint3_tmp_solve_num + 0] = _joint3_3;
            _joint3_tmp[_joint3_tmp_solve_num + 1] = _joint3_4;
            _joint3_tmp_solve_num += 2;
        }
        if (_joint3_tmp_solve_num != 0)
        {
            // 消重，角度差小于0.5度视为同一解
            for (unsigned char _i = 0; _i < _joint3_tmp_solve_num; ++_i)
            {
                for (unsigned char _j = _i; _j < _joint3_tmp_solve_num; ++_j)
                {
                    if (fabsf(_joint3_tmp[_j] + 6666.66) > 6000 && fabsf(_joint3[_i] + 6666.66) < 0.1)
                    {
                        _joint3[_i] = _joint3_tmp[_j];
                        _joint3_solve_num++;
                    }
                    if (_i != _j && fabsf(_joint3_tmp[_i] - _joint3_tmp[_j]) < 0.01)
                        _joint3_tmp[_j] = -6666.66;
                }
            }
            _output_solve->_num_joint3_solve = _joint3_solve_num;
            // 解joint2
            for (unsigned char _i = 0; _i < _joint3_solve_num; ++_i)
            {
                float _f1 = link_parameter[3][1] * cosf(_joint3[_i]) + link_parameter[3][2] * sinf(_joint3[_i]) + link_parameter[2][1];
                float _f2 = link_parameter[3][1] * sinf(_joint3[_i]) - link_parameter[3][2] * cosf(_joint3[_i]);
                float _u2_solve_a1 = _z - link_parameter[0][2] + _f2;
                float _u2_solve_b1 = -2 * _f1;
                float _u2_solve_c1 = _z - link_parameter[0][2] - _f2;
                float _u2_solve_judge = powf(_u2_solve_b1, 2) - 4 * _u2_solve_a1 * _u2_solve_c1;
                if (_u2_solve_judge > -0.000001f)
                {
                    float _u2_solve_1 = (-_u2_solve_b1 - sqrtf(_u2_solve_judge)) / (2 * _u2_solve_a1);
                    float _u2_solve_2 = (-_u2_solve_b1 + sqrtf(_u2_solve_judge)) / (2 * _u2_solve_a1);
                    // joint2角度解
                    float _joint2_solve_1 = 2 * atanf(_u2_solve_1);
                    float _joint2_solve_2 = 2 * atanf(_u2_solve_2);
                    _joint2[_i * 2] = _joint2_solve_1;
                    _joint2[_i * 2 + 1] = _joint2_solve_2;
                }
            }
            // 暂不消重

            // 解joint1
            for (unsigned char _i = 0; _i < _joint3_solve_num * 2; ++_i)
            {
                if (fabsf(_joint2[_i] + 6666.66) > 6000)
                {
                    float _tmp_h = cosf(_joint2[_i]) * (link_parameter[3][1] * cosf(_joint3[_i / 2]) + link_parameter[3][2] * sinf(_joint3[_i / 2]) + link_parameter[2][1])
                        - (sinf(_joint2[_i]) * (link_parameter[3][1] * sinf(_joint3[_i / 2]) - link_parameter[3][2] * cosf(_joint3[_i / 2])))
                        + link_parameter[1][1];
                    // 将误差控制在0.5度左右
                    if (fabsf(_tmp_h) != 0)
                    {
                        // joint1角度解
                        if (fabsf(_x / _tmp_h) <= 1)
                            _joint1[_i] = acosf(_x / _tmp_h);
                        else if (fabsf(_x / _tmp_h) < 1.00005)
                            _joint1[_i] = acosf((int)(_x / _tmp_h));
                    }
                }
            }

            // 解joint4
            for (unsigned char _i = 0; _i < _joint3_solve_num * 2; ++_i)
            {
                if (fabsf(_joint2[_i] + 6666.66) > 6000 && fabsf(_joint1[_i] + 6666.66) > 6000 && fabsf(_joint3[_i] + 6666.66) > 6000)
                {
                    float _c5_0_r13 = cosf(_joint1[_i]) * sinf(_joint2[_i] + _joint3[_i / 2]);
                    float _c5_0_r23 = sinf(_joint1[_i]) * sinf(_joint2[_i] + _joint3[_i / 2]);
                    float _c5_0_r33 = cosf(_joint2[_i] + _joint3[_i / 2]);
                    // joint5旋转角为0的情况
                    if (fabsf(_c5_0_r13 - _joint_rotation[2]) < 0.001 &&
                        fabsf(_c5_0_r23 - _joint_rotation[6]) < 0.001 &&
                        fabsf(_c5_0_r33 - _joint_rotation[10]) < 0.001)
                    {
                        // 令joint4不改变
                        _joint5[_i] = 0;
                        _joint4[_i] = _last_joint[3];
                        float _sin6 = _joint_rotation[0] * (sinf(_joint1[_i]) * cosf(_joint4[_i]) - cosf(_joint1[_i]) * cosf(_joint2[_i] + _joint3[_i / 2]))
                            - _joint_rotation[4] * (sinf(_joint1[_i]) * cosf(_joint2[_i] + _joint3[_i / 2]) * sinf(_joint4[_i]) + cosf(_joint1[_i]) * cosf(_joint4[_i]))
                            - _joint_rotation[8] * (sinf(_joint2[_i] + _joint3[_i / 2]) * sinf(_joint4[_i]));
                        float _cos6 = _joint_rotation[1] * (sinf(_joint1[_i]) * cosf(_joint4[_i]) - cosf(_joint1[_i]) * cosf(_joint2[_i] + _joint3[_i / 2]))
                            - _joint_rotation[5] * (sinf(_joint1[_i]) * cosf(_joint2[_i] + _joint3[_i / 2]) * sinf(_joint4[_i]) + cosf(_joint1[_i]) * cosf(_joint4[_i]))
                            - _joint_rotation[9] * (sinf(_joint2[_i] + _joint3[_i / 2]) * sinf(_joint4[_i]));
                        _joint6[_i] = atanf(_sin6 / _cos6);
                    }
                    // joint5旋转角不为0的情况
                    else
                    {
                        float _t4_molecule = sinf(_joint1[_i]) * _joint_rotation[2] - cosf(_joint1[_i]) * _joint_rotation[6];
                        float _t4_denominator = cosf(_joint1[_i]) * cosf(_joint2[_i] + _joint3[_i / 2]) * _joint_rotation[2]
                            + sinf(_joint1[_i]) * cosf(_joint2[_i] + _joint3[_i / 2]) * _joint_rotation[6]
                            + sinf(_joint2[_i] + _joint3[_i / 2]) * _joint_rotation[10];
                        _joint4[_i] = atanf(_t4_molecule / _t4_denominator);
                        _joint5[_i] = asinf(-_t4_denominator / cosf(_joint4[_i]));
                        float _sin6 = _joint_rotation[0] * (sinf(_joint1[_i]) * cosf(_joint4[_i]) - cosf(_joint1[_i]) * cosf(_joint2[_i] + _joint3[_i / 2]))
                            - _joint_rotation[4] * (sinf(_joint1[_i]) * cosf(_joint2[_i] + _joint3[_i / 2]) * sinf(_joint4[_i]) + cosf(_joint1[_i]) * cosf(_joint4[_i]))
                            - _joint_rotation[8] * (sinf(_joint2[_i] + _joint3[_i / 2]) * sinf(_joint4[_i]));
                        float _cos6 = _joint_rotation[1] * (sinf(_joint1[_i]) * cosf(_joint4[_i]) - cosf(_joint1[_i]) * cosf(_joint2[_i] + _joint3[_i / 2]))
                            - _joint_rotation[5] * (sinf(_joint1[_i]) * cosf(_joint2[_i] + _joint3[_i / 2]) * sinf(_joint4[_i]) + cosf(_joint1[_i]) * cosf(_joint4[_i]))
                            - _joint_rotation[9] * (sinf(_joint2[_i] + _joint3[_i / 2]) * sinf(_joint4[_i]));
                        _joint6[_i] = atanf(_sin6 / _cos6);
                    }
                }

            }
        }
        else
        {
            // 不存在解
            return false;
        }
    }
    else
    {
        // 不存在解
        return false;
    }
    return true;
}

/*
 * @brief:检查所得到的关节关于运动学平衡的旋转角度是否在可达范围内
 */
bool CheckSolveAvailable(const float _joint_rad, const uint8_t _joint_index)
{
    float _joint_angle = RadToDeg(_joint_rad);
    switch (_joint_index)
    {
    case 0:
    case 3:
    case 5:
    {
        return true;
    }
    case 1:
    {
        if (_joint_angle >= JOINT2_MIN_KINEMATICS_ANGLE && _joint_angle <= JOINT2_MAX_KINEMATICS_ANGLE)
            return true;
        break;
    }
    case 2:
    {
        if (_joint_angle >= JOINT3_MIN_KINEMATICS_ANGLE && _joint_angle <= JOINT4_MAX_KINEMATICS_ANGLE)
            return true;
        break;
    }
    case 4:
    {
        if (_joint_angle >= JOINT5_MIN_KINEMATICS_ANGLE && _joint_angle <= JOINT5_MAX_KINEMATICS_ANGLE)
            return true;
        break;
    }
    }
    return false;
}

void JointAngleToRad(const float* _in_joint_angle, float* _out_joint_rad)
{
    for (uint8_t _i = 0; _i < 6; ++_i)
    {
        _out_joint_rad[_i] = DegToRad(_in_joint_angle[_i]);
    }
}

void JointRadToAngle(const float* _in_joint_rad, float* _out_joint_angle)
{
    for (uint8_t _i = 0; _i < 6; ++_i)
    {
        _out_joint_angle[_i] = RadToDeg(_in_joint_rad[_i]);
    }
}

/*
 * @param:  _euler_pos[const float*]:前三个代表相对零点坐标，后三个代表相对原点X-Y-Z固定角旋转角(弧度)           _joint_angles[float*]:输出机械臂六个轴旋转角度
 */
bool EulerPosToJointAngle(const float* _euler_pos, float* _joint_angles)
{
    float _tmp_joint_transform_mat[16];
    float _joint_transform_mat[16];
    bool _exit_solve[8];
    memset(_exit_solve, false, 8);
    EulerPosToTranformMat(_euler_pos, _tmp_joint_transform_mat);
    MatMultiply(_tmp_joint_transform_mat, PosePieperTranformMat, _joint_transform_mat, 4, 4, 4);
    float _joint_rad_rotation_now[6];
    JointAngleToRad(JointRotationNow, _joint_rad_rotation_now);
    bool _is_exit_solve = RobotIK(_joint_transform_mat, &IK_Angles, _joint_rad_rotation_now);
    if (_is_exit_solve)
    {
        uint8_t _num = IK_Angles._num_joint3_solve * 2;
        uint8_t _num_available_solve = 0;
        for (uint8_t _i = 0; _i < _num; ++_i)
        {
            if (fabsf(IK_Angles._joint6[_i] + 6666.66) > 6000)
            {
                _num_available_solve++;
                _exit_solve[_i] = true;
                if (false == CheckSolveAvailable(IK_Angles._joint6[_i], 5))
                {
                    _exit_solve[_i] = false;
                    _num_available_solve--;
                    continue;
                }
                if (false == CheckSolveAvailable(IK_Angles._joint5[_i], 4))
                {
                    _exit_solve[_i] = false;
                    _num_available_solve--;
                    continue;
                }
                if (false == CheckSolveAvailable(IK_Angles._joint4[_i], 3))
                {
                    _exit_solve[_i] = false;
                    _num_available_solve--;
                    continue;
                }
                if (false == CheckSolveAvailable(IK_Angles._joint1[_i], 0))
                {
                    _exit_solve[_i] = false;
                    _num_available_solve--;
                    continue;
                }
                if (false == CheckSolveAvailable(IK_Angles._joint2[_i], 1))
                {
                    _exit_solve[_i] = false;
                    _num_available_solve--;
                    continue;
                }
                if (false == CheckSolveAvailable(IK_Angles._joint3[_i / 2], 2))
                {
                    _exit_solve[_i] = false;
                    _num_available_solve--;
                    continue;
                }
            }
        }
        if (_num_available_solve == 0)
        {
            uint8_t _eth_err_msg_len = 12;
            const char* _eth_err_msg = "NO SOLUTION!";
            WCHNET_SocketSend((uint8_t)0, _eth_err_msg, &_eth_err_msg_len);
            return false;
        }
        bool _is_available_for_joint2[8];
        uint8_t _num_available_for_joint2 = 0;
        memset(_is_available_for_joint2, false, 8);
        // 优先搜索更符合的joint2旋转
        for (uint8_t _i = 0; _i < _num; ++_i)
        {
            if (true == _exit_solve[_i])
            {
                if (JointRotationNow[1] <= 90)
                {
                    float _tmp_angle = RadToDeg(IK_Angles._joint2[_i]);
                    if (_tmp_angle <= 90)
                    {
                        _is_available_for_joint2[_i] = true;
                        _num_available_for_joint2++;
                    }
                }
                else {
                    float _tmp_angle = RadToDeg(IK_Angles._joint2[_i]);
                    if (_tmp_angle > 90)
                    {
                        _is_available_for_joint2[_i] = true;
                        _num_available_for_joint2++;
                    }
                }
            }
        }
        // 不存在更符合的joint2解
        if (_num_available_for_joint2 == 0)
        {
            for (uint8_t _i = 0; _i < _num; ++_i)
            {
                if (true == _exit_solve[_i])
                {
                    _joint_angles[0] = IK_Angles._joint1[_i];
                    _joint_angles[1] = IK_Angles._joint2[_i];
                    _joint_angles[2] = IK_Angles._joint3[_i / 2];
                    _joint_angles[3] = IK_Angles._joint4[_i];
                    _joint_angles[4] = IK_Angles._joint5[_i];
                    _joint_angles[5] = IK_Angles._joint6[_i];
                    JointRadToAngle(_joint_angles, _joint_angles);
                    return true;
                }
            }
        }
        else
        {
            // 筛选更符合要求的解
            for (uint8_t _i = 0; _i < _num; ++_i)
            {
                if (true == _is_available_for_joint2[_i])
                {
                    _joint_angles[0] = IK_Angles._joint1[_i];
                    _joint_angles[1] = IK_Angles._joint2[_i];
                    _joint_angles[2] = IK_Angles._joint3[_i / 2];
                    _joint_angles[3] = IK_Angles._joint4[_i];
                    _joint_angles[4] = IK_Angles._joint5[_i];
                    _joint_angles[5] = IK_Angles._joint6[_i];
                    JointRadToAngle(_joint_angles, _joint_angles);
                    return true;
                }
            }
        }
    }
    else
    {
        uint8_t _eth_err_msg_len = 12;
        const char* _eth_err_msg = "NO SOLUTION!";
        WCHNET_SocketSend((uint8_t)0, _eth_err_msg, &_eth_err_msg_len);
        return false;
    }
    return false;
}
