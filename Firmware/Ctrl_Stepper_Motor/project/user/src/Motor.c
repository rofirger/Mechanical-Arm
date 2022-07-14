/*
 * Motor.c
 *
 *  Created on: 2022年4月21日
 *      Author: 随风
 */


#include "Motor.h"
#include "MT6816.h"
#include "msg_process.h"
#include "stdlib.h"
#include "MyCan.h"
#include "math.h"

extern bool is_stop;
extern bool is_start;
extern bool back_init_pos;
volatile bool rot_done = true;
JointRotationPos joint_rotation_pos;
RotionStatus rotion_status;
JointStatus joint_status = TO_BE_INITED;

// 顺时针
void CV_MotorStep(uint16_t _times, uint16_t _ms_interval)
{
    rot_done = false;
    static uint8_t _motor_status = 0x0C;        // (1100)b
    static MT6816_Structure _data;
    for (uint16_t _i = 0; _i < _times && !is_stop; ++_i)
    {
        // 发送广播信息
        RotingSendBroadcastMsg();

        gpio_set_level(AP_STEP, (_motor_status & 0x08) >> 3);
        gpio_set_level(BP_STEP, (_motor_status & 0x04) >> 2);
        gpio_set_level(AN_STEP, (_motor_status & 0x02) >> 1);
        gpio_set_level(BN_STEP, (_motor_status & 0x01));
        _motor_status = (_motor_status >> 1) | ((_motor_status & 0x01) << 3);
        MT6816_ReadAngle(&_data);
        float _new_pos = _data._decode_angle;
#if (AXIS6 == 0)
        if (_new_pos - joint_rotation_pos._now_pos < -300)
        {
            joint_rotation_pos._now_offset_balance += (_new_pos - joint_rotation_pos._now_pos) + 360;
        }
        else
        {
            joint_rotation_pos._now_offset_balance += (_new_pos - joint_rotation_pos._now_pos);
        }
#if (AXIS2 == 1)
        if (joint_rotation_pos._now_offset_balance < -85 * SPEED_RATIO)
            _ms_interval = 180;
        else {
            _ms_interval = 48;
        }
#endif
#else
        if (_new_pos - joint_rotation_pos._now_pos > 300)
        {
            joint_rotation_pos._now_offset_balance += (_new_pos - (joint_rotation_pos._now_pos + 360));
        }
        else
        {
            joint_rotation_pos._now_offset_balance += (_new_pos - joint_rotation_pos._now_pos);
        }
#endif
        joint_rotation_pos._now_pos = _new_pos;
        system_delay_ms(_ms_interval);
    }
    rot_done = true;
}

// 逆时针
void CCV_MotorStep(uint16_t _times, uint16_t _ms_interval)
{
    static uint8_t _motor_status = 0x0C;        // (1100)b
    static MT6816_Structure _data;
    for (uint16_t _i = 0; _i < _times && !is_stop; ++_i)
    {
        // 发送广播信息
        RotingSendBroadcastMsg();

        gpio_set_level(AP_STEP, (_motor_status & 0x1));
        gpio_set_level(BP_STEP, (_motor_status & 0x02) >> 1);
        gpio_set_level(AN_STEP, (_motor_status & 0x04) >> 2);
        gpio_set_level(BN_STEP, (_motor_status & 0x08) >> 3);
        _motor_status = (_motor_status >> 1) | ((_motor_status & 0x01) << 3);
        MT6816_ReadAngle(&_data);
        float _new_pos = _data._decode_angle;
#if (AXIS6 == 0)
        if (_new_pos - joint_rotation_pos._now_pos > 300)
        {
            joint_rotation_pos._now_offset_balance += (_new_pos - (joint_rotation_pos._now_pos + 360));
        }
        else
        {
            joint_rotation_pos._now_offset_balance += (_new_pos - joint_rotation_pos._now_pos);
        }
#if (AXIS2 == 1)
        if (joint_rotation_pos._now_offset_balance < -85 * SPEED_RATIO)
            _ms_interval = 180;
        else {
            _ms_interval = 48;
        }
#endif
#else
        if (_new_pos - joint_rotation_pos._now_pos < -300)
        {
            joint_rotation_pos._now_offset_balance += (_new_pos - joint_rotation_pos._now_pos) + 360;
        }
        else
        {
            joint_rotation_pos._now_offset_balance += (_new_pos - joint_rotation_pos._now_pos);
        }
#endif
        joint_rotation_pos._now_pos = _new_pos;
        system_delay_ms(_ms_interval);
    }
}


// pid 参数
typedef struct PID
{
    float P, I, D;
} PID;

// 增量式
typedef struct Error
{
    float currentError;   //当前误差
    float lastError;      //上一次误差
    float previoursError; //上上次误差
} Error;
// 位置式
typedef struct PosErr
{
    Error err;
    float loc_sum;
} PosErr;
/*<!
 *  @brief      位置式PID
 *  *sptr ：误差参数
 *  *pid:  PID参数
 *  now_point：实际值
 *  target_point：   期望值
 */
float PID_Pos(PosErr* sptr, PID* pid, float now_point, float target_point)
{
    float pos_;                                                       // 位置
    sptr->err.currentError = target_point - now_point;                // 计算当前误差
    sptr->loc_sum += sptr->err.currentError;                          // 累计误差
    pos_ = pid->P * sptr->err.currentError                            // 比列P
        + pid->I * sptr->loc_sum                                   // 积分I
        + pid->D * (sptr->err.currentError - sptr->err.lastError); // 微分D
    sptr->err.lastError = sptr->err.currentError;                     // 更新上次误差
    return pos_;
}

void KeepPos()
{
    static MT6816_Structure _data;
    static PosErr _pid_err = { {0, 0, 0}, 0 };
    static PID _pid = { 0.53, 0, 0.0002 };
    MT6816_ReadAngle(&_data);
    float _new_pos = _data._decode_angle;
    joint_rotation_pos._now_offset_balance += (_new_pos - joint_rotation_pos._now_pos);
    joint_rotation_pos._now_pos = _new_pos;
    // 发布广播信息
    KeepPosSendBroadcastMsg();
    if (!is_stop)
    {
        float _ccw_incr = PID_Pos(&_pid_err, &_pid, joint_rotation_pos._now_offset_balance, joint_rotation_pos._target_offset_balance);
        _pid_err.loc_sum = 0;
        if (joint_status == ROTING_TO_NEW_POS)
        {
            if (fabsf(_ccw_incr) < 5)
            {
                joint_status = STAY_IN_POS;
            }
        }
        if (_ccw_incr > 0)
        {
            // 顺时针旋转
#if (AXIS6 == 0)
#if (AXIS2 == 1)
            SendBackChangeEncoder(INCREASE_ENCODER, _ccw_incr);
            if (joint_rotation_pos._now_offset_balance < -90 * SPEED_RATIO)
                CV_MotorStep(_ccw_incr, 80);
            else
                CV_MotorStep(_ccw_incr, 48);
#elif (AXIS5 == 1 || AXIS4 == 1)
            SendBackChangeEncoder(INCREASE_ENCODER, _ccw_incr);
            CV_MotorStep(_ccw_incr, 20);
#elif (AXIS1 == 1 || AXIS3 == 1)
            SendBackChangeEncoder(INCREASE_ENCODER, _ccw_incr);
            CV_MotorStep(_ccw_incr, 30);
#endif
#else
            SendBackChangeEncoder(INCREASE_ENCODER, _ccw_incr);
            CCV_MotorStep(_ccw_incr, 25);
#endif
        }
        else if (_ccw_incr < 0)
        {
            // 逆时针旋转
#if (AXIS6 == 0)
#if (AXIS2 == 1)
            SendBackChangeEncoder(DECREASE_ENCODER, -_ccw_incr);
            if (joint_rotation_pos._now_offset_balance < -90 * SPEED_RATIO)
                CCV_MotorStep(-_ccw_incr, 80);
            else {
                CCV_MotorStep(-_ccw_incr, 48);
            }
#elif (AXIS5 == 1 || AXIS4 == 1)
            SendBackChangeEncoder(DECREASE_ENCODER, -_ccw_incr);
            CCV_MotorStep(-_ccw_incr, 20);
#elif (AXIS1 == 1 || AXIS3 == 1)
            SendBackChangeEncoder(DECREASE_ENCODER, -_ccw_incr);
            CCV_MotorStep(-_ccw_incr, 30);
#endif
#else
            SendBackChangeEncoder(DECREASE_ENCODER, -_ccw_incr);
            CV_MotorStep(-_ccw_incr, 25);
#endif
        }
    }

}


void InitPos()
{
    joint_rotation_pos._balance_pos = BALANCE_POS_ANGLE;
    MT6816_Structure _data;
    MT6816_ReadAngle(&_data);
    joint_rotation_pos._now_pos = _data._decode_angle;
#if (AXIS1 == 1)
    joint_rotation_pos._now_offset_balance = joint_rotation_pos._now_pos - BALANCE_POS_ANGLE;
    joint_rotation_pos._init_pos_offset_balance = INIT_POS_ANGLE - BALANCE_POS_ANGLE;
    rotion_status._last_rotion_dir = INCREASE_ENCODER;
#endif

#if (AXIS2 == 1)
    if (joint_rotation_pos._now_pos > 150)
        joint_rotation_pos._now_offset_balance = -(BALANCE_POS_ANGLE + 360 - joint_rotation_pos._now_pos);
    else if (joint_rotation_pos._now_pos < 100){
        joint_rotation_pos._now_offset_balance = -(BALANCE_POS_ANGLE - joint_rotation_pos._now_pos);
    }
    joint_rotation_pos._init_pos_offset_balance = -(BALANCE_POS_ANGLE + 360 - INIT_POS_ANGLE);
    rotion_status._last_rotion_dir = DECREASE_ENCODER;
#endif

#if (AXIS3 == 1)
    if (joint_rotation_pos._now_pos > 200)
        joint_rotation_pos._now_offset_balance = -(BALANCE_POS_ANGLE + 360 - joint_rotation_pos._now_pos);
    else
        joint_rotation_pos._now_offset_balance = -(BALANCE_POS_ANGLE - joint_rotation_pos._now_pos);
    joint_rotation_pos._init_pos_offset_balance = -(BALANCE_POS_ANGLE - INIT_POS_ANGLE);
    rotion_status._last_rotion_dir = INCREASE_ENCODER;
#endif

#if (AXIS4 == 1)
    joint_rotation_pos._now_offset_balance = joint_rotation_pos._now_pos - BALANCE_POS_ANGLE;
    joint_rotation_pos._init_pos_offset_balance = INIT_POS_ANGLE - BALANCE_POS_ANGLE;
    rotion_status._last_rotion_dir = INCREASE_ENCODER;
#endif

#if (AXIS5 == 1)
    joint_rotation_pos._now_offset_balance = joint_rotation_pos._now_pos - BALANCE_POS_ANGLE;
    joint_rotation_pos._init_pos_offset_balance = INIT_POS_ANGLE - BALANCE_POS_ANGLE;
    rotion_status._last_rotion_dir = DECREASE_ENCODER;
#endif

#if (AXIS6 == 1)
    joint_rotation_pos._now_offset_balance = joint_rotation_pos._now_pos - BALANCE_POS_ANGLE;
    joint_rotation_pos._init_pos_offset_balance = INIT_POS_ANGLE - BALANCE_POS_ANGLE;
    rotion_status._last_rotion_dir = DECREASE_ENCODER;
#endif
    joint_rotation_pos._target_offset_balance = joint_rotation_pos._init_pos_offset_balance;
    is_start = true;
    joint_status = INITED;
}

/*
 * @brief:注意该_motor_angle是已经经过    SPEED_RATIO
 */
void SetPos(const float _motor_angle)
{
#if (AXIS1 == 1)
    joint_rotation_pos._target_offset_balance = -_motor_angle;
#endif

#if (AXIS2 == 1)
    joint_rotation_pos._target_offset_balance = _motor_angle - (180 * SPEED_RATIO);
#endif

#if (AXIS3 == 1)
    joint_rotation_pos._target_offset_balance = _motor_angle + (90 * SPEED_RATIO);
#endif

#if (AXIS4 == 1)
    joint_rotation_pos._target_offset_balance = -_motor_angle;
#endif

#if (AXIS5 == 1)
    joint_rotation_pos._target_offset_balance = _motor_angle;
#endif

#if (AXIS6 == 1)
    joint_rotation_pos._target_offset_balance = -_motor_angle;
#endif

    ErrorCompensation(joint_rotation_pos._now_offset_balance, &joint_rotation_pos._target_offset_balance);
    joint_status = ROTING_TO_NEW_POS;
}

/*
 * @brief:因减速器自身精度问题，该函数用于补偿关节旋转误差
 */
void ErrorCompensation(const int _now_offset_balance, int* _target_offset_balance)
{
#if (AXIS6 == 1)
    if (*_target_offset_balance == _now_offset_balance)
    {
        rotion_status._next_rotion_dir = rotion_status._last_rotion_dir;
    }
    else if (*_target_offset_balance > _now_offset_balance)
    {
        rotion_status._next_rotion_dir = DECREASE_ENCODER;
        if (rotion_status._last_rotion_dir != rotion_status._next_rotion_dir)
        {
            *_target_offset_balance += INVALID_ROTION_ENCODER;
        }
    }
    else if (*_target_offset_balance < _now_offset_balance)
    {
        rotion_status._next_rotion_dir = INCREASE_ENCODER;
        if (rotion_status._last_rotion_dir != rotion_status._next_rotion_dir)
        {
            *_target_offset_balance -= INVALID_ROTION_ENCODER;
        }
    }
#else
    if (*_target_offset_balance == _now_offset_balance)
    {
        rotion_status._next_rotion_dir = rotion_status._last_rotion_dir;
    }
    else if (*_target_offset_balance > _now_offset_balance)
    {
        rotion_status._next_rotion_dir = INCREASE_ENCODER;
#if (AXIS1 == 1)
        if (rotion_status._last_rotion_dir != rotion_status._next_rotion_dir)
        {
            *_target_offset_balance += INVALID_ROTION_ENCODER;
        }
#endif
    }
    else if (*_target_offset_balance < _now_offset_balance)
    {
        rotion_status._next_rotion_dir = DECREASE_ENCODER;
#if (AXIS1 == 1)
        if (rotion_status._last_rotion_dir != rotion_status._next_rotion_dir)
        {
            *_target_offset_balance -= INVALID_ROTION_ENCODER;
        }
#endif
    }
#endif
#if (AXIS2 == 1)
    if (*_target_offset_balance / SPEED_RATIO > -90 && _now_offset_balance / SPEED_RATIO < -90)
    {
        *_target_offset_balance -= INVALID_ROTION_ENCODER * 1.8;
    }
    if (*_target_offset_balance / SPEED_RATIO < -90 && _now_offset_balance / SPEED_RATIO > -90)
    {
        *_target_offset_balance += INVALID_ROTION_ENCODER * 1.8;
    }
#endif
#if (AXIS5 == 1)
    if (*_target_offset_balance / SPEED_RATIO > 90 && _now_offset_balance / SPEED_RATIO < 90)
    {
        *_target_offset_balance -= INVALID_ROTION_ENCODER;
    }
    if (*_target_offset_balance / SPEED_RATIO < 90 && _now_offset_balance / SPEED_RATIO > 90)
    {
        *_target_offset_balance += INVALID_ROTION_ENCODER;
    }
#endif
    rotion_status._last_rotion_dir = rotion_status._next_rotion_dir;
}


