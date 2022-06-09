/*
 * ETH.c
 *
 *  Created on: 2022��5��15��
 *      Author: ���
 */


#include "WCHNET.h"
#include "zf_common_headfile.h"
#include "Config.h"

__attribute__((__aligned__(4))) ETH_DMADESCTypeDef DMARxDscrTab[ETH_RXBUFNB];                        /* MAC���������� ��4�ֽڶ���*/
 __attribute__((__aligned__(4))) ETH_DMADESCTypeDef DMATxDscrTab[ETH_TXBUFNB];                        /* MAC������������4�ֽڶ��� */

 __attribute__((__aligned__(4))) u8  MACRxBuf[ETH_RXBUFNB*ETH_MAX_PACKET_SIZE];                       /* MAC���ջ�������4�ֽڶ��� */
 __attribute__((__aligned__(4))) u8  MACTxBuf[ETH_TXBUFNB*ETH_MAX_PACKET_SIZE];                       /* MAC���ͻ�������4�ֽڶ��� */


__attribute__((__aligned__(4))) SOCK_INF SocketInf[WCHNET_MAX_SOCKET_NUM];                           /* Socket��Ϣ����4�ֽڶ��� */
const u16 MemNum[8] = {WCHNET_NUM_IPRAW,
                         WCHNET_NUM_UDP,
                         WCHNET_NUM_TCP,
                         WCHNET_NUM_TCP_LISTEN,
                         WCHNET_NUM_TCP_SEG,
                         WCHNET_NUM_IP_REASSDATA,
                         WCHNET_NUM_PBUF,
                         WCHNET_NUM_POOL_BUF
                         };
const u16 MemSize[8] = {WCHNET_MEM_ALIGN_SIZE(WCHNET_SIZE_IPRAW_PCB),
                          WCHNET_MEM_ALIGN_SIZE(WCHNET_SIZE_UDP_PCB),
                          WCHNET_MEM_ALIGN_SIZE(WCHNET_SIZE_TCP_PCB),
                          WCHNET_MEM_ALIGN_SIZE(WCHNET_SIZE_TCP_PCB_LISTEN),
                          WCHNET_MEM_ALIGN_SIZE(WCHNET_SIZE_TCP_SEG),
                          WCHNET_MEM_ALIGN_SIZE(WCHNET_SIZE_IP_REASSDATA),
                          WCHNET_MEM_ALIGN_SIZE(WCHNET_SIZE_PBUF) + WCHNET_MEM_ALIGN_SIZE(0),
                          WCHNET_MEM_ALIGN_SIZE(WCHNET_SIZE_PBUF) + WCHNET_MEM_ALIGN_SIZE(WCHNET_SIZE_POOL_BUF)
                         };
 __attribute__((__aligned__(4)))u8 Memp_Memory[WCHNET_MEMP_SIZE];
 __attribute__((__aligned__(4)))u8 Mem_Heap_Memory[WCHNET_RAM_HEAP_SIZE];
 __attribute__((__aligned__(4)))u8 Mem_ArpTable[WCHNET_RAM_ARP_TABLE_SIZE];


#define RECE_BUF_LEN                          WCHNET_TCP_MSS*2                                   /*socket���ջ������ĳ���,��СΪTCP MSS*/

uint8_t MACAddr[6];                                                                                   /*Mac��ַ*/
uint8_t IPAddr[4] = {192,168,1,10};                                                                   /*IP��ַ*/
uint8_t GWIPAddr[4] = {192,168,1,1};                                                                  /*����*/
uint8_t IPMask[4] = {255,255,255,0};                                                                  /*��������*/
uint8_t DESIP[4] = {192,168,1,100};                                                                   /*Ŀ��IP��ַ*/

uint8_t SocketId;                                                                                     /*socket id��*/
uint8_t SocketRecvBuf[WCHNET_MAX_SOCKET_NUM][RECE_BUF_LEN];                                           /*socket������*/
uint8_t MyBuf[RECE_BUF_LEN];
uint16_t desport=1000;                                                                                /*Ŀ�Ķ˿ں�*/
uint16_t srcport=1000;                                                                                /*Դ�˿ں�*/

/*********************************************************************
 * @fn      Ethernet_LED_Configuration
 *
 * @brief   set eth data and link led pin
 *
 * @return  none
 */
void Ethernet_LED_Configuration(void)
{
    GPIO_InitTypeDef  GPIO={0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
    GPIO.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12;
    GPIO.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE,&GPIO);
    Ethernet_LED_LINKSET(1);
    Ethernet_LED_DATASET(1);
}


/*********************************************************************
 * @fn      Ethernet_LED_LINKSET
 *
 * @brief   set eth link led,setbit 0 or 1,the link led turn on or turn off
 *
 * @return  none
 */
void Ethernet_LED_LINKSET(u8 setbit)
{
     if(setbit){
         GPIO_SetBits(GPIOE, GPIO_Pin_11);
     }
     else {
         GPIO_ResetBits(GPIOE, GPIO_Pin_11);
    }
}


/*********************************************************************
 * @fn      Ethernet_LED_DATASET
 *
 * @brief   set eth data led,setbit 0 or 1,the data led turn on or turn off
 *
 * @return  none
 */
void Ethernet_LED_DATASET(u8 setbit)
{
     if(setbit){
         GPIO_SetBits(GPIOE, GPIO_Pin_12);
     }
     else {
         GPIO_ResetBits(GPIOE, GPIO_Pin_12);
    }
}

/*********************************************************************
 * @fn      mStopIfError
 *
 * @brief   check if error.
 *
 * @return  none
 */
void mStopIfError(u8 iError)
{
    if (iError == WCHNET_ERR_SUCCESS) return;                                   /* �����ɹ� */
    printf("Error: %02X\r\n", (u16)iError);                                    /* ��ʾ���� */
}


/*********************************************************************
 * @fn      WCHNET_LibInit
 *
 * @brief   Initializes NET.
 *
 * @return  command status
 */
u8 WCHNET_LibInit(const u8 *ip,const u8 *gwip,const u8 *mask,const u8 *macaddr)
{
    u8 i;
    struct _WCH_CFG  cfg;

    cfg.RxBufSize = RX_BUF_SIZE;
    cfg.TCPMss   = WCHNET_TCP_MSS;
    cfg.HeapSize = WCH_MEM_HEAP_SIZE;
    cfg.ARPTableNum = WCHNET_NUM_ARP_TABLE;
    cfg.MiscConfig0 = WCHNET_MISC_CONFIG0;
    WCHNET_ConfigLIB(&cfg);
    i = WCHNET_Init(ip,gwip,mask,macaddr);
    return (i);
}

/*********************************************************************
 * @fn      SET_MCO
 *
 * @brief   Set ETH Clock.
 *
 * @return  none
 */
void SET_MCO(void)
{

    RCC_PLL3Cmd(DISABLE);
    RCC_PREDIV2Config(RCC_PREDIV2_Div2);
    RCC_PLL3Config(RCC_PLL3Mul_15);
    RCC_MCOConfig(RCC_MCO_PLL3CLK);
    RCC_PLL3Cmd(ENABLE);
    system_delay_ms(100);
    while(RESET == RCC_GetFlagStatus(RCC_FLAG_PLL3RDY))
    {
        system_delay_ms(500);
    }
    RCC_AHBPeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
}

/*********************************************************************
 * @fn      TIM2_Init
 *
 * @brief   Initializes TIM2.
 *
 * @return  none
 */
void TIM2_Init( void )
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure={0};

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_TimeBaseStructure.TIM_Period = 200-1;
    TIM_TimeBaseStructure.TIM_Prescaler =7200-1;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    TIM_ITConfig(TIM2, TIM_IT_Update ,ENABLE);

    TIM_Cmd(TIM2, ENABLE);
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update );
    NVIC_SetPriority(TIM2_IRQn, 0x80);
    NVIC_EnableIRQ(TIM2_IRQn);
}


/*********************************************************************
 * @fn      WCHNET_CreatTcpSocket
 *
 * @brief   Creat Tcp Socket
 *
 * @return  none
 */
void WCHNET_CreatTcpSocket(void)
{
   u8 i;
   SOCK_INF TmpSocketInf;                                                       /* ������ʱsocket���� */

   memset((void *)&TmpSocketInf,0,sizeof(SOCK_INF));                            /* ���ڲ��Ὣ�˱������ƣ�������ý���ʱ������ȫ������ */
   memcpy((void *)TmpSocketInf.IPAddr,DESIP,4);                                 /* ����Ŀ��IP��ַ */
   TmpSocketInf.DesPort  = desport;                                             /* ����Ŀ�Ķ˿� */
   TmpSocketInf.SourPort = srcport++;                                           /* ����Դ�˿� */
   TmpSocketInf.ProtoType = PROTO_TYPE_TCP;                                     /* ����socekt���� */
   TmpSocketInf.RecvStartPoint = (u32)SocketRecvBuf[SocketId];                  /* ���ý��ջ������Ľ��ջ����� */
   TmpSocketInf.RecvBufLen = RECE_BUF_LEN ;                                     /* ���ý��ջ������Ľ��ճ��� */
   i = WCHNET_SocketCreat(&SocketId,&TmpSocketInf);                             /* ����socket�������ص�socket����������SocketId�� */
   printf("WCHNET_SocketCreat %d\r\n",SocketId);
   mStopIfError(i);                                                             /* ������ */
   i = WCHNET_SocketConnect(SocketId);                                          /* TCP���� */
   mStopIfError(i);                                                             /* ������ */
}

/*********************************************************************
 * @fn      WCHNET_HandleSockInt
 *
 * @brief   Socket Interrupt Handle
 *
 * @return  none
 */
void WCHNET_HandleSockInt(u8 sockeid,u8 initstat)
{
    u32 len;

    if(initstat & SINT_STAT_RECV)                                               /* socket�����ж�*/
    {
       len = WCHNET_SocketRecvLen(sockeid,NULL);                                /* ��ȡsocket���������ݳ���  */
       printf("WCHNET_SocketRecvLen %d \r\n",len);
       WCHNET_SocketRecv(sockeid,MyBuf,&len);                                   /* ��ȡsocket���������� */
       WCHNET_SocketSend(sockeid,MyBuf,&len);                                   /* ��ʾ�ش����� */
       if (strcmp(MyBuf, "led_on") == 0)
       {
           gpio_set_level(LED_INDICATOR, 1);
       }
       else if (strcmp(MyBuf, "led_off") == 0)
       {
           gpio_set_level(LED_INDICATOR, 0);
       }
       tft180_show_string(10, 10, MyBuf );
    }
    if(initstat & SINT_STAT_CONNECT)                                            /* socket���ӳɹ��ж�*/
    {
        printf("TCP Connect Success\r\n");
    }
    if(initstat & SINT_STAT_DISCONNECT)                                         /* socket���ӶϿ��ж�*/
    {
        printf("TCP Disconnect\r\n");
    }
    if(initstat & SINT_STAT_TIM_OUT)                                            /* socket���ӳ�ʱ�ж�*/
    {
       printf("TCP Timout\r\n");                                                /* ��ʱ200ms������*/
       system_delay_ms(200);
       WCHNET_CreatTcpSocket();
    }
}


/*********************************************************************
 * @fn      WCHNET_HandleGlobalInt
 *
 * @brief   Global Interrupt Handle
 *
 * @return  none
 */
void WCHNET_HandleGlobalInt(void)
{
    u8 initstat;
    u16 i;
    u8 socketinit;

    initstat = WCHNET_GetGlobalInt();                                           /* ��ȡȫ���жϱ�־*/
    if(initstat & GINT_STAT_UNREACH)                                            /* ���ɴ��ж� */
    {
       printf("GINT_STAT_UNREACH\r\n");
    }
   if(initstat & GINT_STAT_IP_CONFLI)                                           /* IP��ͻ�ж� */
   {
       printf("GINT_STAT_IP_CONFLI\r\n");
   }
   if(initstat & GINT_STAT_PHY_CHANGE)                                          /* PHY״̬�仯�ж� */
   {
       i = WCHNET_GetPHYStatus();                                               /* ��ȡPHY����״̬*/
       if(i&PHY_Linked_Status)
       printf("PHY Link Success\r\n");
   }
   if(initstat & GINT_STAT_SOCKET)
   {
       for(i = 0; i < WCHNET_MAX_SOCKET_NUM; i ++)
       {
           socketinit = WCHNET_GetSocketInt(i);
           if(socketinit)WCHNET_HandleSockInt(i,socketinit);
       }
   }
}

void Eth()
{
    uint8_t i;
    SET_MCO();
    TIM2_Init();
    WCH_GetMac(MACAddr);                                                     /*��ȡоƬMac��ַ*/
    i=WCHNET_LibInit(IPAddr,GWIPAddr,IPMask,MACAddr);                        /*��̫�����ʼ��*/
    //mStopIfError(i);
    while(!(WCHNET_GetPHYStatus()&PHY_LINK_SUCCESS))                         /*�ȴ�PHY���ӳɹ�*/
     {
        system_delay_ms(100);
     }
    WCHNET_CreatTcpSocket();                                                 /*����Tcp socket*/

}