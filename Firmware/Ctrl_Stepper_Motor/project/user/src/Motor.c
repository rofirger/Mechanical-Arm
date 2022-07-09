/*
 * Motor.c
 *
 *  Created on: 2022年4月21日
 *      Author: 随风
 */


#include "Motor.h"
#include "MT6816.h"

extern bool is_stop;
extern bool is_start;
JointRotationPos joint_rotation_pos;

// 顺时针
void CV_MotorStep(uint16_t _times, uint16_t _ms_interval)
{
    static uint8_t _motor_status = 0x0C;        // (1100)b
    static MT6816_Structure _data;
    for (uint16_t _i = 0; _i < _times; ++_i)
    {
        gpio_set_level(AP_STEP, (_motor_status & 0x08) >> 3);
        gpio_set_level(BP_STEP, (_motor_status & 0x04) >> 2);
        gpio_set_level(AN_STEP, (_motor_status & 0x02) >> 1);
        gpio_set_level(BN_STEP, (_motor_status & 0x01));
        _motor_status = (_motor_status >> 1) | ((_motor_status & 0x01) << 3);
        MT6816_ReadAngle(&_data);
        float _new_pos = _data._decode_angle;
#if (AXIS6 == 0)
        if (_new_pos - joint_rotation_pos._now_pos < -300)
            joint_rotation_pos._now_offset_balance  += (_new_pos - joint_rotation_pos._now_pos) + 360;
        else
            joint_rotation_pos._now_offset_balance  += (_new_pos - joint_rotation_pos._now_pos);
#else
        if (_new_pos - joint_rotation_pos._now_pos > 300)
            joint_rotation_pos._now_offset_balance  += (_new_pos - (joint_rotation_pos._now_pos + 360));
        else
            joint_rotation_pos._now_offset_balance  += (_new_pos - joint_rotation_pos._now_pos);
#endif
        joint_rotation_pos._now_pos = _new_pos;
        system_delay_ms(_ms_interval);
    }
}

// 逆时针
void CCV_MotorStep(uint16_t _times, uint16_t _ms_interval)
{
    static uint8_t _motor_status = 0x0C;        // (1100)b
    static MT6816_Structure _data;
    for (uint16_t _i = 0; _i < _times; ++_i)
    {
        gpio_set_level(AP_STEP, (_motor_status & 0x1));
        gpio_set_level(BP_STEP, (_motor_status & 0x02) >> 1);
        gpio_set_level(AN_STEP, (_motor_status & 0x04) >> 2);
        gpio_set_level(BN_STEP, (_motor_status & 0x08) >> 3);
        _motor_status = (_motor_status >> 1) | ((_motor_status & 0x01) << 3);
        MT6816_ReadAngle(&_data);
        float _new_pos = _data._decode_angle;
#if (AXIS6 == 0)
        if (_new_pos - joint_rotation_pos._now_pos > 300)
            joint_rotation_pos._now_offset_balance  += (_new_pos - (joint_rotation_pos._now_pos + 360));
        else
            joint_rotation_pos._now_offset_balance  += (_new_pos - joint_rotation_pos._now_pos);
#else
        if (_new_pos - joint_rotation_pos._now_pos < -300)
            joint_rotation_pos._now_offset_balance  += (_new_pos - joint_rotation_pos._now_pos) + 360;
        else
            joint_rotation_pos._now_offset_balance  += (_new_pos - joint_rotation_pos._now_pos);
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
float PID_Pos (PosErr *sptr, PID *pid, float now_point, float target_point)
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
    static PosErr _pid_err = {{0, 0, 0}, 0};
    static PID _pid = {0.53, 0, 0.00002};
    MT6816_ReadAngle(&_data);
    float _new_pos = _data._decode_angle;
    joint_rotation_pos._now_offset_balance  += (_new_pos - joint_rotation_pos._now_pos);
    joint_rotation_pos._now_pos = _new_pos;
    float _ccw_incr = PID_Pos(&_pid_err, &_pid, joint_rotation_pos._now_offset_balance, joint_rotation_pos._target_offset_balance);
    _pid_err.loc_sum = 0;
    if (_ccw_incr > 0)
    {
        // 顺时针旋转
#if (AXIS6 == 0)
        CV_MotorStep(_ccw_incr, 25);
#else
        CCV_MotorStep(-_ccw_incr, 25);
#endif
    }
    else if (_ccw_incr < 0)
    {
        // 逆时针旋转
#if (AXIS6 == 0)
        CCV_MotorStep(-_ccw_incr, 25);
#else
        CV_MotorStep(_ccw_incr, 25);
#endif
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
#endif

#if (AXIS2 == 1)
    joint_rotation_pos._now_offset_balance = -(BALANCE_POS_ANGLE + 360 - joint_rotation_pos._now_pos);
    joint_rotation_pos._init_pos_offset_balance = -(BALANCE_POS_ANGLE + 360 - INIT_POS_ANGLE);
#endif

#if (AXIS3 == 1)
    joint_rotation_pos._now_offset_balance = joint_rotation_pos._now_pos - BALANCE_POS_ANGLE;
    joint_rotation_pos._init_pos_offset_balance = INIT_POS_ANGLE - BALANCE_POS_ANGLE;
#endif

#if (AXIS4 == 1)
    joint_rotation_pos._now_offset_balance = joint_rotation_pos._now_pos - BALANCE_POS_ANGLE;
    joint_rotation_pos._init_pos_offset_balance = INIT_POS_ANGLE - BALANCE_POS_ANGLE;
#endif

#if (AXIS5 == 1)
    joint_rotation_pos._now_offset_balance = joint_rotation_pos._now_pos - BALANCE_POS_ANGLE;
    joint_rotation_pos._init_pos_offset_balance = INIT_POS_ANGLE - BALANCE_POS_ANGLE;
#endif

#if (AXIS6 == 1)
    joint_rotation_pos._now_offset_balance = joint_rotation_pos._now_pos - BALANCE_POS_ANGLE;
    joint_rotation_pos._init_pos_offset_balance = INIT_POS_ANGLE - BALANCE_POS_ANGLE;
#endif
    joint_rotation_pos._target_offset_balance = joint_rotation_pos._init_pos_offset_balance;
    is_start = true;
}

/*
 * @brief:注意该_motor_angle是已经经过    SPEED_RATIO
 */
void SetPos(const float _motor_angle)
{
#if (AXIS1 == 1)
    joint_rotation_pos._target_offset_balance = _motor_angle;
#endif

#if (AXIS2 == 1)
    joint_rotation_pos._target_offset_balance = _motor_angle - (180 * SPEED_RATIO);
#endif

#if (AXIS3 == 1)
    joint_rotation_pos._target_offset_balance = _motor_angle + (90 * SPEED_RATIO);
#endif

#if (AXIS4 == 1)
    joint_rotation_pos._target_offset_balance = _motor_angle;
#endif

#if (AXIS5 == 1)
    joint_rotation_pos._target_offset_balance = _motor_angle;
#endif

#if (AXIS6 == 1)
    joint_rotation_pos._target_offset_balance = _motor_angle;
#endif


}
