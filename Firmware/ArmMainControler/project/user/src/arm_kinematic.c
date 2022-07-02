/*
 * arm_kinematic.c
 *
 *  Created on: Jun 21, 2022
 *      Author: 随风
 */
#include "arm_kinematic.h"
#include "math.h"
#include "Config.h"
#include "zf_common_headfile.h"

// 连杆参数表
const float link_parameter[6][4] = {
        {0, 0, DH_BASE_HEIGHT, 0},
        {PI_2, DH_BASE_R1_L, 0, 0},
        {0, DH_R1_R2_L, 0, 0},
        {PI_2, DH_R2_R3_L, DH_R3_R4_L, 0},
        {PI_2, 0, 0, 0},
        {-PI_2, 0, DH_R4_R5_L, 0},
};



/*
 * @brief:角度换算弧度
 */
inline float DegToRad(const float _deg)
{
    return _deg / RAD_TO_DEG;
}

/*
 * @brief:     根据连杆参数求连杆变换矩阵
 * @param:     _link_param[const float*]  6*4连杆参数表;       _out_transform_mat[float*]  6连杆变换矩阵
 */
void LinkToTransformMat(const float* _link_param, float* _out_transform_mat)
{
    for (uint8_t _i = 0; _i < 6; ++_i)
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

/*
 * @brief:根据旋转矩阵求X-Y—Z固定旋转角
 */
void RotationMatToEulerAngle(const float* _rot_mat, float* _euler_angle)
{
    // 分情况讨论
    if (fabsf(_rot_mat[6]) > 1 - 0.0001)    // 等于1
    {
        if(_rot_mat[6] < 0)
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
    _euler_angle[1] = atan2f(-_rot_mat[6], sqrt(_rot_mat[0] * _rot_mat[0] + _rot_mat[3] * _rot_mat[3]));
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
    float sb = cosf(_euler_pos[4]);
    float cr = cosf(_euler_pos[5]);
    float sr = cosf(_euler_pos[5]);

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
void RobotIK(const float* _joint_rotation, IK_AngleSlove* _output_solve)
{
    float _joint3[4] = { -6666.66 ,-6666.66 ,-6666.66 ,-6666.66 };
    unsigned char _joint3_solve_num = 0;
    float _joint2[8] = { -6666.66 ,-6666.66 ,-6666.66 ,-6666.66 , -6666.66 ,-6666.66 ,-6666.66 ,-6666.66 };
    unsigned char _joint2_solve_num = 0;
    float _joint1[8] = { -6666.66 ,-6666.66 ,-6666.66 ,-6666.66 , -6666.66 ,-6666.66 ,-6666.66 ,-6666.66 };
    unsigned char _joint1_solve_num = 0;

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
                    _joint2_solve_num += 2;
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
                // 先判断joint5的旋转角度是否为0
            }



            int i = 0;
            i = 10;
        }
        else
        {
            // 不存在解
        }
    }
    else
    {
        // 不存在解
    }
}
