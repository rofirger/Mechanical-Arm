/*
 * ETH.h
 *
 *  Created on: 2022年6月1日
 *      Author: 随风
 */

#ifndef ETH_H_
#define ETH_H_

void Ethernet_LED_Configuration(void);
void Ethernet_LED_LINKSET(u8 setbit);
void Ethernet_LED_DATASET(u8 setbit);
void mStopIfError(u8 iError);
u8 WCHNET_LibInit(const u8 *ip,const u8 *gwip,const u8 *mask,const u8 *macaddr);
void SET_MCO(void);
void TIM2_Init( void );
void WCHNET_CreatTcpSocket(void);
void WCHNET_HandleSockInt(u8 sockeid,u8 initstat);
void WCHNET_HandleGlobalInt(void);
void Eth();

#endif /* ETH_H_ */
