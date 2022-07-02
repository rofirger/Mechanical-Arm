/*
 * MyCan.h
 *
 *  Created on: 2022年5月3日
 *      Author: 随风
 */

#ifndef MYCAN_H_
#define MYCAN_H_
#include "zf_common_headfile.h"
#define AXIS1   0
#define AXIS2   0
#define AXIS3   0
#define AXIS4   0
#define AXIS5   0
#define AXIS6   1
#define AXIS7   0

#if (AXIS1 == 1)
#define JOINT_INDEX 1
#endif
#if (AXIS2 == 1)
#define JOINT_INDEX 2
#endif
#if (AXIS3 == 1)
#define JOINT_INDEX 3
#endif
#if (AXIS4 == 1)
#define JOINT_INDEX 4
#endif
#if (AXIS5 == 1)
#define JOINT_INDEX 5
#endif
#if (AXIS6 == 1)
#define JOINT_INDEX 6
#endif

/*
 * 过滤器ID
 */

//  主控板ID
#define MAIN_CONTROLER_FILTER_ID_A          (0x00)
#define MAIN_CONTROLER_FILTER_ID_B          (MAIN_CONTROLER_FILTER_ID_A + (1 << 5))
#define MAIN_CONTROLER_FILTER_ID_C          (MAIN_CONTROLER_FILTER_ID_A + 2 * (1 << 5))
#define MAIN_CONTROLER_FILTER_ID_D          (MAIN_CONTROLER_FILTER_ID_A + 3 * (1 << 5))


#if (AXIS1 == 1)
// (1 00 00000)
#define FILTER_ID_AXIS_A                   (0x80)
// (1 01 00000)
#define FILTER_ID_AXIS_B                   (FILTER_ID_AXIS_A + (1 << 5))
// (1 10 00000)
#define FILTER_ID_AXIS_C                   (FILTER_ID_AXIS_A + 2 * (1 << 5))
// (1 11 00000)
#define FILTER_ID_AXIS_D                   (FILTER_ID_AXIS_A + 3 * (1 << 5))
#endif

#if (AXIS2 == 1)
// (10 00 00000)
#define FILTER_ID_AXIS_A                   (0x100)
// (10 01 00000)
#define FILTER_ID_AXIS_B                   (FILTER_ID_AXIS_A + (1 << 5))
// (10 10 00000)
#define FILTER_ID_AXIS_C                   (FILTER_ID_AXIS_A + 2 * (1 << 5))
// (10 11 00000)
#define FILTER_ID_AXIS_D                   (FILTER_ID_AXIS_A + 3 * (1 << 5))
#endif

#if (AXIS3 == 1)
// (11 00 00000)
#define FILTER_ID_AXIS_A                   0x180
// (11 01 00000)
#define FILTER_ID_AXIS_B                   (FILTER_ID_AXIS_A + (1 << 5))
// (11 10 00000)
#define FILTER_ID_AXIS_C                   (FILTER_ID_AXIS_A + 2 * (1 << 5))
// (11 11 00000)
#define FILTER_ID_AXIS_D                   (FILTER_ID_AXIS_A + 3 * (1 << 5))
#endif

#if (AXIS4 == 1)
// (100 00 00000)
#define FILTER_ID_AXIS_A                   0x200
// (100 01 00000)
#define FILTER_ID_AXIS_B                   (FILTER_ID_AXIS_A + (1 << 5))
// (100 10 00000)
#define FILTER_ID_AXIS_C                   (FILTER_ID_AXIS_A + 2 * (1 << 5))
// (100 11 00000)
#define FILTER_ID_AXIS_D                   (FILTER_ID_AXIS_A + 3 * (1 << 5))
#endif

#if (AXIS5 == 1)
// (101 00 00000)
#define FILTER_ID_AXIS_A                   0x280
// (101 01 00000)
#define FILTER_ID_AXIS_B                   (FILTER_ID_AXIS_A + (1 << 5))
// (101 10 00000)
#define FILTER_ID_AXIS_C                   (FILTER_ID_AXIS_A + 2 * (1 << 5))
// (101 11 00000)
#define FILTER_ID_AXIS_D                   (FILTER_ID_AXIS_A + 3 * (1 << 5))
#endif

#if (AXIS6 == 1)
// (110 00 00000)
#define FILTER_ID_AXIS_A                   0x300
// (110 01 00000)
#define FILTER_ID_AXIS_B                   (FILTER_ID_AXIS_A + (1 << 5))
// (110 10 00000)
#define FILTER_ID_AXIS_C                   (FILTER_ID_AXIS_A + 2 * (1 << 5))
// (110 11 00000)
#define FILTER_ID_AXIS_D                   (FILTER_ID_AXIS_A + 3 * (1 << 5))
#endif

#if (AXIS7 == 1)
// (111 00 00000)
#define FILTER_ID_AXIS_A                   0x380
// (111 01 00000)
#define FILTER_ID_AXIS_B                   (FILTER_ID_AXIS_A + (1 << 5))
// (111 10 00000)
#define FILTER_ID_AXIS_C                   (FILTER_ID_AXIS_A + 2 * (1 << 5))
// (111 11 00000)
#define FILTER_ID_AXIS_D                   (FILTER_ID_AXIS_A + 3 * (1 << 5))
#endif
void CAN_Mode_Init(uint8_t tsjw, uint8_t tbs2, uint8_t tbs1, uint16_t brp, uint8_t mode );
uint8_t CAN_Send_Msg(uint8_t *msg, uint8_t len);
uint8_t CAN_Receive_Msg(uint8_t *buf );
#endif /* MYCAN_H_ */
