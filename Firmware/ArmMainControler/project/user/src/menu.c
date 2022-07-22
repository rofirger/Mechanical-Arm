/*
 *      @File: menu.c
 *
 *      @Team: 删库跑路队
 *      @Author: 随风
 */
#include "menu.h"


// 当前机械臂末端的欧拉位置, 前三个代表相对零点坐标，后三个代表相对原点X-Y-Z固定角旋转角
extern float EulerPosNow[6];
// 新目标机械臂末端的欧拉位置, 前三个代表相对零点坐标，后三个代表相对原点X-Y-Z固定角旋转角
extern float EulerPosNew[6];
// 当前机械臂关节的旋转角
extern float JointRotationNow[6];
// 目标机械臂关节旋转角
extern float JointRotationNew[6];

// 一行不能超过14个字符
char menu[7][8][18];

MenuFocus menu_focus;
uint8_t menu_page_rows[10];

void InitMenu(void)
{
    tft180_clear(RGB565_WHITE);
    menu_focus._menu_index = 0;
    menu_focus._menu_row = 0;
    memcpy(menu[0][0], "|MAIN_PAGE|", sizeof(char) * 12);
    memcpy(menu[0][1], "EulerPosNew", sizeof(char) * 12);
    memcpy(menu[0][2], "EulerPosNow", sizeof(char) * 12);
    memcpy(menu[0][3], "NowRotion", sizeof(char) * 10);
    memcpy(menu[0][4], "TargetRotion", sizeof(char) * 13);
    memcpy(menu[0][5], "JointStatus", sizeof(char) * 12);
    menu_page_rows[0] = 6;
    for (uint8_t _i = 0; _i < menu_page_rows[0]; ++_i)
    {
        tft180_show_string(0, 16 * _i, menu[0][_i]);
    }
    tft180_show_uint(0, 8 * 16, menu_focus._menu_row, 3);
}

void Refresh()
{
    tft180_clear(RGB565_WHITE);
    uint8_t _rows = menu_page_rows[menu_focus._menu_index];
    for (uint8_t _i = 0; _i < _rows; ++_i)
    {
        tft180_show_string(0, 16 * _i, menu[menu_focus._menu_index][_i]);
    }
    tft180_show_uint(0, 8 * 16, menu_focus._menu_row, 3);
}

void KeyUp()
{
    if (menu_focus._menu_row == 0)
    {
        menu_focus._menu_row = 0;
        return;
    }
    --menu_focus._menu_row;
    Refresh();
}

void KeyDown()
{
    if (menu_focus._menu_row == menu_page_rows[menu_focus._menu_index] - 2)
    {
        return;
    }
    ++menu_focus._menu_row;
    Refresh();
}

void KeyLeft()
{
    if (menu_focus._menu_index != 0)
    {
        menu_focus._menu_index = 0;
        menu_focus._menu_row = 0;
        Refresh();
    }
    else
    {
        menu_focus._menu_index = menu_focus._menu_row + 1;
        switch (menu_focus._menu_row)
        {
        case 0:
        {
            menu_page_rows[1] = 7;
            memcpy(menu[menu_focus._menu_index][0], "|EulerPosNew|", sizeof(char) * 14);
            for (uint8_t _i = 0; _i < 6; ++_i)
            {
                sprintf(menu[menu_focus._menu_index][_i + 1], "%.3f", EulerPosNew[_i]);
            }
            break;
        }
        case 1:
        {
            menu_page_rows[2] = 7;
            memcpy(menu[menu_focus._menu_index][0], "|EulerPosNow|", sizeof(char) * 14);
            for (uint8_t _i = 0; _i < 6; ++_i)
            {
                sprintf(menu[menu_focus._menu_index][_i + 1], "%.3f", EulerPosNow[_i]);
            }
            break;
        }
        case 2:
        {
            menu_page_rows[3] = 7;
            memcpy(menu[menu_focus._menu_index][0], "|NowRotion|", sizeof(char) * 12);
            for (uint8_t _i = 0; _i < 6; ++_i)
            {
                sprintf(menu[menu_focus._menu_index][_i + 1], "%.3f", JointRotationNow[_i]);
            }
            break;
        }
        case 3:
        {
            menu_page_rows[4] = 7;
            memcpy(menu[menu_focus._menu_index][0], "|TargetRotion|", sizeof(char) * 15);
            for (uint8_t _i = 0; _i < 6; ++_i)
            {
                sprintf(menu[menu_focus._menu_index][_i + 1], "%.3f", JointRotationNew[_i]);
            }
            break;
        }
        case 4:
        {
            menu_page_rows[5] = 7;
            memcpy(menu[menu_focus._menu_index][0], "|JointStatus|", sizeof(char) * 14);
            for (uint8_t _i = 0; _i < 6; ++_i)
            {
                switch(joint_status[_i])
                {
                case TO_BE_INITED:
                {
                    memcpy(menu[menu_focus._menu_index][_i + 1], "TO_BE_INITED", sizeof(char) * 13);
                    break;
                }
                case INITED:
                {
                    memcpy(menu[menu_focus._menu_index][_i + 1], "INITED", sizeof(char) * 7);
                    break;
                }
                case ROTING_TO_NEW_POS:
                {
                    memcpy(menu[menu_focus._menu_index][_i + 1], "ROTING", sizeof(char) * 7);
                    break;
                }
                case STAY_IN_POS:
                {
                    memcpy(menu[menu_focus._menu_index][_i + 1], "STAY_IN_POS", sizeof(char) * 12);
                    break;
                }
                }
            }
        }
        }
        menu_focus._menu_row = 0;
        Refresh();
    }
}

