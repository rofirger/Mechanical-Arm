/*
 * menu.h
 *
 *  Created on: 2022��7��13��
 *      Author: ���
 */

#ifndef MENU_H_
#define MENU_H_
#include "zf_common_headfile.h"
#include "msg_process.h"
#include "joint.h"

typedef struct MenuFocus
{
    uint8_t _menu_index;
    uint8_t _menu_row;
}MenuFocus;
void InitMenu(void);
void KeyUp();
void KeyLeft();
void KeyDown();
#endif /* MENU_H_ */
