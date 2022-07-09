/*
 * msg_process.c
 *
 *  Created on: 2022年7月5日
 *      Author: 随风
 */
#include "headfile.h"
#include "msg_process.h"
#include "MyCan.h"
#include "MT6816.h"
#include "stdlib.h"
#include "Motor.h"

uint8_t* CAN_MSG[8];
extern bool is_stop;
extern JointRotationPos joint_rotation_pos;

void CAN_MsgProcess(char* _can_msg)
{
    char* _main_msg = strtok(_can_msg, "#");        // 命令结束分隔符
    if (_main_msg)
    {
        if (strcmp(_main_msg, "INIT") == 0)
        {
            InitPos();
            return;
        }
        else if (strcmp(_main_msg, "BACK") == 0)
        {
            joint_rotation_pos._target_offset_balance = joint_rotation_pos._init_pos_offset_balance;
            return;
        }
        char* _head_cmd = strtok(_main_msg, " ");
        if (_head_cmd)
        {
            if (strcmp(_head_cmd, "S") == 0)
            {
                char* _sec_cmd = strtok(NULL, " ");
                if (strcmp(_sec_cmd, "C") == 0)
                {
                    char* _third_cmd = strtok(NULL, " ");
                    if (_third_cmd)
                        CV_MotorStep(atoi(_third_cmd), 25);
                }
                else if (strcmp(_sec_cmd, "V") == 0)
                {
                    char* _third_cmd = strtok(NULL, " ");
                    if (_third_cmd)
                        CCV_MotorStep(atoi(_third_cmd), 25);
                }
                else if (strcmp(_sec_cmd, "J") == 0)
                {
                    MT6816_Structure _data;
                    MT6816_ReadAngle(&_data);
                    uint8_t _send_back_pos[8];
                    char _trans_num[8] = {'\0'};
                    uint8_t _num = 4;
                    _send_back_pos[0] = 'P';
                    _send_back_pos[1] = ' ';
                    _send_back_pos[2] = (uint8_t)JOINT_INDEX + '0';
                    _send_back_pos[3] = ' ';
                    itoa(_data._decode_angle, _trans_num, 10);
                    for (uint8_t _i = 0; _trans_num[_i] != '\0' && _i < 8; ++_i)
                    {
                        _send_back_pos[_num] = _trans_num[_i];
                        ++_num;
                    }
                    if (_num < 8)
                    {
                        _send_back_pos[_num] = '#';
                        CAN_Send_Msg(_send_back_pos, _num + 1);
                    }
                }
            }
            else if (strcmp(_head_cmd, "STOP") == 0)
            {
                is_stop = true;
            }
            else if (strcmp(_head_cmd, "TO") == 0)
            {
                char* _sec_cmd = strtok(NULL, "#");
                // 相对于平衡位置的旋转角度
                if (_sec_cmd)
                {
                    SetPos(atoi(_sec_cmd));
                }

            }
        }
    }

}

/*
 * @brief:返回编码器变换量
 */
void SendBackChangeEncoder(const RotionDir _dir, int _num)
{
    char _send_back_msg[8] = {'\0'};
    if (_dir == INCREASE_ENCODER)
    {
        _send_back_msg[0] = 'A';
        _send_back_msg[1] = JOINT_INDEX + '0';
        _send_back_msg[2] = ' ';
        char _num_str[8] = {'\0'};
        itoa(_num, _num_str, 10);
        memcpy(&_send_back_msg[3], _num_str, strlen(_num_str) * sizeof(char));
        _send_back_msg[3 + strlen(_num_str)] = '#';
        CAN_Send_Msg(_send_back_msg, 4 + strlen(_num_str));
    }
    else {
        _send_back_msg[0] = 'S';
        _send_back_msg[1] = JOINT_INDEX + '0';
        _send_back_msg[2] = ' ';
        char _num_str[8] = {'\0'};
        itoa(_num, _num_str, 10);
        memcpy(&_send_back_msg[3], _num_str, strlen(_num_str) * sizeof(char));
        _send_back_msg[3 + strlen(_num_str)] = '#';
        CAN_Send_Msg(_send_back_msg, 4 + strlen(_num_str));
    }
}
