/*
 * MyCan.h
 *
 *  Created on: 2022年5月14日
 *      Author: 随风
 */

#ifndef MYCAN_H_
#define MYCAN_H_
void CAN_Mode_Init(uint8_t tsjw, uint8_t tbs2, uint8_t tbs1, uint16_t brp, uint8_t mode );
uint8_t CAN_Send_Msg(uint8_t *msg, uint8_t len, uint32_t id);
uint8_t CAN_Receive_Msg(uint8_t *buf );
/*
 * 过滤器ID
 */

//  主控板ID
#define MAIN_CONTROLER_FILTER_ID_A          (0x00)
#define MAIN_CONTROLER_FILTER_ID_B          (MAIN_CONTROLER_FILTER_ID_A + (1 << 5))
#define MAIN_CONTROLER_FILTER_ID_C          (MAIN_CONTROLER_FILTER_ID_A + 2 * (1 << 5))
#define MAIN_CONTROLER_FILTER_ID_D          (MAIN_CONTROLER_FILTER_ID_A + 3 * (1 << 5))


// (1 00 00000)
#define FILTER_ID_AXIS1_A                   (0x80)
// (1 01 00000)
#define FILTER_ID_AXIS1_B                   (FILTER_ID_AXIS1_A + (1 << 5))
// (1 10 00000)
#define FILTER_ID_AXIS1_C                   (FILTER_ID_AXIS1_A + 2 * (1 << 5))
// (1 11 00000)
#define FILTER_ID_AXIS1_D                   (FILTER_ID_AXIS1_A + 3 * (1 << 5))

// (10 00 00000)
#define FILTER_ID_AXIS2_A                   (0x100)
// (10 01 00000)
#define FILTER_ID_AXIS2_B                   (FILTER_ID_AXIS2_A + (1 << 5))
// (10 10 00000)
#define FILTER_ID_AXIS2_C                   (FILTER_ID_AXIS2_A + 2 * (1 << 5))
// (10 11 00000)
#define FILTER_ID_AXIS2_D                   (FILTER_ID_AXIS2_A + 3 * (1 << 5))

// (11 00 00000)
#define FILTER_ID_AXIS3_A                   0x180
// (11 01 00000)
#define FILTER_ID_AXIS3_B                   (FILTER_ID_AXIS3_A + (1 << 5))
// (11 10 00000)
#define FILTER_ID_AXIS3_C                   (FILTER_ID_AXIS3_A + 2 * (1 << 5))
// (11 11 00000)
#define FILTER_ID_AXIS3_D                   (FILTER_ID_AXIS3_A + 3 * (1 << 5))

// (100 00 00000)
#define FILTER_ID_AXIS4_A                   0x200
// (100 01 00000)
#define FILTER_ID_AXIS4_B                   (FILTER_ID_AXIS4_A + (1 << 5))
// (100 10 00000)
#define FILTER_ID_AXIS4_C                   (FILTER_ID_AXIS4_A + 2 * (1 << 5))
// (100 11 00000)
#define FILTER_ID_AXIS4_D                   (FILTER_ID_AXIS4_A + 3 * (1 << 5))

// (101 00 00000)
#define FILTER_ID_AXIS5_A                   0x280
// (101 01 00000)
#define FILTER_ID_AXIS5_B                   (FILTER_ID_AXIS5_A + (1 << 5))
// (101 10 00000)
#define FILTER_ID_AXIS5_C                   (FILTER_ID_AXIS5_A + 2 * (1 << 5))
// (101 11 00000)
#define FILTER_ID_AXIS5_D                   (FILTER_ID_AXIS5_A + 3 * (1 << 5))

// (110 00 00000)
#define FILTER_ID_AXIS6_A                   0x300
// (110 01 00000)
#define FILTER_ID_AXIS6_B                   (FILTER_ID_AXIS6_A + (1 << 5))
// (110 10 00000)
#define FILTER_ID_AXIS6_C                   (FILTER_ID_AXIS6_A + 2 * (1 << 5))
// (110 11 00000)
#define FILTER_ID_AXIS6_D                   (FILTER_ID_AXIS6_A + 3 * (1 << 5))

// (111 00 00000)
#define FILTER_ID_AXIS7_A                   0x380
// (111 01 00000)
#define FILTER_ID_AXIS7_B                   (FILTER_ID_AXIS7_A + (1 << 5))
// (111 10 00000)
#define FILTER_ID_AXIS7_C                   (FILTER_ID_AXIS7_A + 2 * (1 << 5))
// (111 11 00000)
#define FILTER_ID_AXIS7_D                   (FILTER_ID_AXIS7_A + 3 * (1 << 5))


#endif /* MYCAN_H_ */
