/*
 * msg_process.c
 *
 *  Created on: Jun 30, 2022
 *      Author: 随风
 */

/*
 * ********命令********
 */
#include "msg_process.h"
#include <stdlib.h>


extern float EulerPosNew[6];
uint8_t* CAN_MSG[8];


/*
 * @brief:ETH消息处理
 * @note: Joint2:CCW往上
 */
void ETH_MsgProcess(char* _eth_msg)
{
    tft180_show_string(5, 0, _eth_msg);
    char* _main_msg = strtok(_eth_msg, "#");        // 命令结束分隔符
    char* _head_cmd = strtok(_main_msg, " ");
    if (_head_cmd)
    {
        if (strcmp(_head_cmd, "READ") == 0)
        {
            char* _sec_cmd = strtok(NULL, " ");
            if (_sec_cmd[0] == 'J')
            {
                if (_sec_cmd[1] >= '1' && _sec_cmd[1] <= '6')
                {
                    CAN_Send_Msg( "S J#", 7, ((JOINT_ID_BASE + JOINT_ID_OFFSET * (_sec_cmd[1] % '1')) >> 5));
                }
            }
        }
        else if (strcmp(_head_cmd, "ROT") == 0)
        {
            char* _sec_cmd = strtok(NULL, " ");
            if (_sec_cmd[0] == 'J')
            {
                if (_sec_cmd[1] >= '1' && _sec_cmd[1] <= '6')
                {
                    uint8_t _joint_index = _sec_cmd[1] % '1';
                    char* _third_cmd = strtok(NULL, " ");
                    // 顺时针
                    if (strcmp(_third_cmd, "CW") == 0)
                    {
                        char* _fourth_cmd = strtok(NULL, " ");
                        char _send_joint_msg_tmp[8] = {'\0'};
                        memcpy(_send_joint_msg_tmp, "S C ", 4);
                        uint8_t _i = 0;
                        for ( _i = 0; _i < 2 && _fourth_cmd[_i] != '\0'; ++_i)
                        {
                            _send_joint_msg_tmp[4 + _i] = _fourth_cmd[_i];
                        }
                        tft180_show_string(0, 50, _send_joint_msg_tmp);
                        CAN_Send_Msg(_send_joint_msg_tmp, _i + 4, ((JOINT_ID_BASE + JOINT_ID_OFFSET * _joint_index) >> 5));
                    }
                    else if (strcmp(_third_cmd, "CCW") == 0)        // 逆时针
                    {
                        char* _fourth_cmd = strtok(NULL, " ");
                        char _send_joint_msg_tmp[8] = {'\0'};
                        memcpy(_send_joint_msg_tmp, "S V ", 4);
                        uint8_t _i = 0;
                        for ( _i = 0; _i < 2 && _fourth_cmd[_i] != '\0'; ++_i)
                        {
                            _send_joint_msg_tmp[4 + _i] = _fourth_cmd[_i];
                        }
                        CAN_Send_Msg(_send_joint_msg_tmp, _i + 4, ((JOINT_ID_BASE + JOINT_ID_OFFSET * _joint_index) >> 5));
                    }
                }
            }
        }
        else if (strcmp(_head_cmd, "MOV") == 0)
        {
            char* _pos1_cmd = strtok(NULL, ",");
            EulerPosNew[0] = strtof(_pos1_cmd, NULL);
            char* _pos2_cmd = strtok(NULL, ",");
            EulerPosNew[1] = strtof(_pos2_cmd, NULL);
            char* _pos3_cmd = strtok(NULL, ",");
            EulerPosNew[2] = strtof(_pos3_cmd, NULL);
            char* _pos4_cmd = strtok(NULL, ",");
            EulerPosNew[3] = strtof(_pos4_cmd, NULL);
            char* _pos5_cmd = strtok(NULL, ",");
            EulerPosNew[4] = strtof(_pos5_cmd, NULL);
            char* _pos6_cmd = strtok(NULL, "#");
            EulerPosNew[5] = strtof(_pos6_cmd, NULL);
        }
    }
}

/*
 * @brief:CAN信息处理
 */
void CAN_MsgProcess(char* _can_msg)
{
    tft180_show_string(0, 0, _can_msg);
    char* _main_msg = strtok(_can_msg, "#");        // 命令结束分隔符
    char* _head_cmd = strtok(_main_msg, " ");
    if (_head_cmd)
    {
        if (strcmp(_head_cmd, "P") == 0)
        {
            char* _sec_cmd = strtok(NULL, " ");
            if (*_sec_cmd >= '1' && *_sec_cmd <= '7')
            {
                char _joint_index = *_sec_cmd;
                char* _third_cmd = strtok(NULL, "#");
                if (_third_cmd)
                {
                    char _eth_send_msg[16] = {'\0'};
                    memcpy(_eth_send_msg, "POS J", 5);
                    _eth_send_msg[5] = _joint_index;
                    _eth_send_msg[6] = ' ';
                    memcpy(&_eth_send_msg[7], _third_cmd, strlen(_third_cmd));
                    _eth_send_msg[strlen(_eth_send_msg)] = '\0';
                    uint32_t _len = strlen(_eth_send_msg);
                    WCHNET_SocketSend((uint8_t)0, _eth_send_msg, &_len);
                    tft180_show_string(0, 25, _eth_send_msg);
                }
            }
        }
    }
}
