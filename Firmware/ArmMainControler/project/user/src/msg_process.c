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
#include "zf_common_headfile.h"
#include "zf_common_font.h"
#include "arm_kinematic.h"
#include "joint.h"
#include "MyCan.h"

extern float EulerPosNew[6];
uint8_t* CAN_MSG[8];

// 当前机械臂末端的欧拉位置, 前三个代表相对零点坐标，后三个代表相对原点X-Y-Z固定角旋转角
extern float EulerPosNow[6];
// 新目标机械臂末端的欧拉位置, 前三个代表相对零点坐标，后三个代表相对原点X-Y-Z固定角旋转角
extern float EulerPosNew[6];
// 当前机械臂关节的旋转角
extern float JointRotationNow[6];
// 目标机械臂关节旋转角
extern float JointRotationNew[6];
extern bool is_open_wifi_uart;

// 物品放置位置
float EulerPosGoods[3][6];
int get_good_index = 0;

bool is_back = false;

/*
 * @brief:ETH消息处理
 * @note: Joint2:CCW往上
 */
void ETH_MsgProcess(char* _eth_msg)
{

    char* _main_msg = strtok(_eth_msg, "#");        // 命令结束分隔符
    if (_main_msg)
    {
        if (strcmp(_main_msg, "INIT ROBOT") == 0)
        {
            InitRobot();
        }
        else if (strcmp(_main_msg, "BACK ROBOT") == 0)
        {
            BackRobot();
        }
        else if (strcmp(_main_msg, "WAKE ROBOT") == 0)
        {
            WakeRobot();
        }
        else if (strcmp(_main_msg, "START UART") == 0)
        {
            StartUart();
        }
        else if (strcmp(_main_msg, "CLOSE UART") == 0)
        {
            CloseUart();
        }
        else if (strcmp(_main_msg, "SCAN GOODS") == 0)
        {
            CAN_Send_Msg("SCAN#", 5, FILTER_ID_AXIS7_A >> 5);
        }
        else if (strcmp(_main_msg, "PICK GOODS") == 0)
        {
            is_back = true;
            CAN_Send_Msg("GET#", 5, FILTER_ID_AXIS7_A >> 5);
        }
        else if (strcmp(_main_msg, "PUT GOODS") == 0)
        {
            CAN_Send_Msg("PUT#", 5, FILTER_ID_AXIS7_A >> 5);
        }
        else if (strcmp(_main_msg, "R") == 0)
        {
            is_back = false;
            char _send_joint_to_angle[8] = {'\0'};
            for (uint8_t _i = 0; _i < 6 && is_back == false; ++_i)
            {
                if (_i != 1)
                {
                    memset(_send_joint_to_angle, 0, 8);
                    memcpy(_send_joint_to_angle, "TO ", 3);
                    itoa(JointRotationNew[_i] * SPEED_RATIO, &_send_joint_to_angle[3], 10);
                    uint8_t _size = strlen(_send_joint_to_angle);
                    _send_joint_to_angle[_size++] = '#';
                    CAN_Send_Msg(_send_joint_to_angle, _size, ((JOINT_ID_BASE + JOINT_ID_OFFSET * _i) >> 5));
                }
                //tft180_show_float(0, _i * 16, JointRotationNew[_i], 4, 4);
            }
        }
    }
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
                    CAN_Send_Msg( "S J#", 4, ((JOINT_ID_BASE + JOINT_ID_OFFSET * (_sec_cmd[1] % '1')) >> 5));
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
                        _send_joint_msg_tmp[4 + _i] = '#';
                        CAN_Send_Msg(_send_joint_msg_tmp, _i + 5, ((JOINT_ID_BASE + JOINT_ID_OFFSET * _joint_index) >> 5));
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
                        _send_joint_msg_tmp[4 + _i] = '#';
                        CAN_Send_Msg(_send_joint_msg_tmp, _i + 5, ((JOINT_ID_BASE + JOINT_ID_OFFSET * _joint_index) >> 5));
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
            EulerPosNew[3] = DegToRad(strtof(_pos4_cmd, NULL));
            char* _pos5_cmd = strtok(NULL, ",");
            EulerPosNew[4] = DegToRad(strtof(_pos5_cmd, NULL));
            char* _pos6_cmd = strtok(NULL, "#");
            EulerPosNew[5] = DegToRad(strtof(_pos6_cmd, NULL));
            bool is_exit_solve = EulerPosToJointAngle(EulerPosNew, JointRotationNew);
            if (is_exit_solve)
            {
                char _send_joint_to_angle[8] = {'\0'};
                tft180_clear(RGB565_WHITE);
                for (uint8_t _i = 0; _i < 6 && is_back == false; ++_i)
                {
                    memset(_send_joint_to_angle, 0, 8);
                    memcpy(_send_joint_to_angle, "TO ", 3);
                    itoa(JointRotationNew[_i] * SPEED_RATIO, &_send_joint_to_angle[3], 10);
                    uint8_t _size = strlen(_send_joint_to_angle);
                    _send_joint_to_angle[_size++] = '#';
                    CAN_Send_Msg(_send_joint_to_angle, _size, ((JOINT_ID_BASE + JOINT_ID_OFFSET * _i) >> 5));
                    //tft180_show_float(0, _i * 16, JointRotationNew[_i], 4, 4);
                }
                if (true == is_back)
                {
                    int _i = 1;
                    memset(_send_joint_to_angle, 0, 8);
                    memcpy(_send_joint_to_angle, "TO ", 3);
                    itoa(JointRotationNew[_i] * SPEED_RATIO, &_send_joint_to_angle[3], 10);
                    uint8_t _size = strlen(_send_joint_to_angle);
                    _send_joint_to_angle[_size++] = '#';
                    CAN_Send_Msg(_send_joint_to_angle, _size, ((JOINT_ID_BASE + JOINT_ID_OFFSET * _i) >> 5));
                }
            }
        }
    }
}

/*
 * @brief:CAN信息处理
 */
void CAN_MsgProcess(char* _can_msg)
{
    char* _main_msg = strtok(_can_msg, "#");        // 命令结束分隔符
    if (_main_msg)
    {
        if (strcmp(_main_msg, "PICK") == 0)
        {
            //MoveToNewPos(EulerPosGoods[get_good_index]);
        }
    }
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
                }
            }
        }
        else if (_head_cmd[0] == 'A')       // 关节旋转角度增加
        {
            int _joint_index = _head_cmd[1] - '1';
            if (_joint_index >= 0 && _joint_index <= 6)
            {
                char* _sec_cmd = strtok(NULL, "#");
                if (_sec_cmd)
                {
                    JointRotationNow[_joint_index] += atoi(_sec_cmd) / SPEED_RATIO;
                }
            }
        }
        else if (_head_cmd[0] == 'S')       // 关节旋转角度减小
        {
            int _joint_index = _head_cmd[1] - '1';
            if (_joint_index >= 0 && _joint_index <= 6)
            {
                char* _sec_cmd = strtok(NULL, "#");
                if (_sec_cmd)
                {
                    JointRotationNow[_joint_index] -= atoi(_sec_cmd) / SPEED_RATIO;
                }
            }
        }
        // 注意此关键字是关节的状态
        else if (_head_cmd[0] == 'T')
        {
            int _joint_index = _head_cmd[1] - '1';
            if (_joint_index >= 0 && _joint_index <= 6)
            {
                char* _sec_cmd = strtok(NULL, "#");
                if (_sec_cmd)
                {
                    if (strcmp(_sec_cmd, "UNI") == 0)
                    {
                        joint_status[_joint_index] = TO_BE_INITED;
                    }
                    else if(strcmp(_sec_cmd, "INI") == 0)
                    {
                        joint_status[_joint_index] = INITED;
                    }
                    else if (strcmp(_sec_cmd, "STA") == 0)
                    {
                        joint_status[_joint_index] = STAY_IN_POS;
                    }
                    else if (strcmp(_sec_cmd, "ROT") == 0)
                    {
                        joint_status[_joint_index] = ROTING_TO_NEW_POS;
                    }
                }
            }
            bool is_ok = true;
            for (uint8_t i = 0; i < 6; ++i)
            {
                if (joint_status[i] != STAY_IN_POS)
                    is_ok = false;
            }
//            if (joint_status[1] == STAY_IN_POS)
//            {
//                CAN_Send_Msg("SCAN#", 5, FILTER_ID_AXIS7_A >> 5);
//                tft180_show_string(0, 100, "OK");
//            }
        }
//        else if (strcmp(_head_cmd, "PIC") == 0)
//        {
//            char* _sec_cmd = strtok(NULL, "#");
//            get_good_index = _sec_cmd[0];
//            CAN_Send_Msg("GET#", 5, FILTER_ID_AXIS7_A >> 5);
//            float _new_pos[6];
//            _new_pos[0] = EulerPosNew[0] + 20;
//            _new_pos[1] = EulerPosNew[1];
//            _new_pos[2] = EulerPosNew[2] - 10;
//            _new_pos[3] = EulerPosNew[3];
//            _new_pos[4] = EulerPosNew[4];
//            _new_pos[5] = EulerPosNew[5];
//            MoveToNewPos(_new_pos);
//            tft180_show_int(0, 110, get_good_index, 3);
//        }
    }
}


void InitGoodsInfo()
{
    EulerPosGoods[0][0] = 0;
    EulerPosGoods[0][1] = -350;
    EulerPosGoods[0][2] = 400;
    EulerPosGoods[0][3] = PI_2;
    EulerPosGoods[0][4] = 0;
    EulerPosGoods[0][5] = PI_2;

    EulerPosGoods[1][0] = 0;
    EulerPosGoods[1][1] = -350;
    EulerPosGoods[1][2] = 400;
    EulerPosGoods[1][3] = PI_2;
    EulerPosGoods[1][4] = 0;
    EulerPosGoods[1][5] = PI_2;

    EulerPosGoods[2][0] = 0;
    EulerPosGoods[2][1] = -350;
    EulerPosGoods[2][2] = 400;
    EulerPosGoods[2][3] = PI_2;
    EulerPosGoods[2][4] = 0;
    EulerPosGoods[2][5] = PI_2;
}

void InitRobot(void)
{
    CAN_Send_Msg("INIT#", 5, JOINT_GENERAL_ID >> 5);
    // 更新   JointRotationNew
    JointRotationNow[0] = 0;
    JointRotationNow[1] = 180 - 293 / SPEED_RATIO;
    JointRotationNow[2] = -90 - 50 / SPEED_RATIO;
    JointRotationNow[3] = 0;
    JointRotationNow[4] = 0;
    JointRotationNow[5] = 0;
    InitGoodsInfo();
}

void BackRobot(void)
{
    CAN_Send_Msg("BACK#", 5, JOINT_GENERAL_ID >> 5);
}

void WakeRobot(void)
{
    CAN_Send_Msg("WAKE#", 5, JOINT_GENERAL_ID >> 5);
}

void StartUart()
{
    is_open_wifi_uart = true;
}

void CloseUart()
{
    is_open_wifi_uart = false;
}

void QueryJointStatus()
{
    static char _send_joint_to_angle[] = "STATUS#";
    for (uint8_t _i = 0; _i < 6; ++_i)
    {
        CAN_Send_Msg(_send_joint_to_angle, 7, ((JOINT_ID_BASE + JOINT_ID_OFFSET * _i) >> 5));
        Delay_Ms(10);
    }
}
