/*
 *      @File: msg_process.c
 *
 *      @Team: 删库跑路队
 *      @Author: 随风
 */
#include "headfile.h"
#include "zf_common_headfile.h"
#include "msg_process.h"
#include "img_process.h"
#include "MyCan.h"

uint8_t* CAN_MSG[8];
bool is_scan = false;

void CAN_MsgProcess(char* _can_msg)
{
    char* _main_msg = strtok(_can_msg, "#");        // 命令结束分隔符
    if (_main_msg)
    {
        if (strcmp(_main_msg, "SCAN") == 0)
        {
            is_scan = true;
        }
        else if(strcmp(_main_msg, "GET") == 0)
        {
            GetGoods();
        }
        else if (strcmp(_main_msg, "PUT") == 0)
        {
            PutGoods();
        }
    }
}

void GetGoods()
{
    //Delay_Ms(6000);
    pwm_set_duty(TIM5_PWM_CH1_A0, 415);
    Delay_Ms(6000);
    CAN_Send_Msg("PICK#", 5, MAIN_CONTROLER_FILTER_ID_A);
}

void PutGoods()
{
    pwm_set_duty(TIM5_PWM_CH1_A0, 1000);
}
