/*
 *      @File: MyCan.c
 *
 *      @Team: 删库跑路队
 *      @Author: 随风
 */

#include "zf_common_headfile.h"
#include "MyCan.h"

/*
 * CAN1的GPIO引脚:CAN1_RX(PA11), CAN1_TX(PA12)
 * */


/* CAN Mode Definition */
#define TX_MODE   0
#define RX_MODE   1

/* Frame Format Definition */
#define Standard_Frame   0
#define Extended_Frame   1

/* CAN Communication Mode Selection */
//#define CAN_MODE   TX_MODE
#define CAN_MODE   RX_MODE

/* Frame Formate Selection */
#define Frame_Format   Standard_Frame
//#define Frame_Format   Extended_Frame

/*********************************************************************
 * @fn      CAN_Mode_Init
 *
 * @brief   Initializes CAN communication test mode.
 *          Bps =Fpclk1/((tpb1+1+tbs2+1+1)*brp)
 *
 * @param   tsjw - CAN synchronisation jump width.
 *          tbs2 - CAN time quantum in bit segment 1.
 *          tbs1 - CAN time quantum in bit segment 2.
 *          brp - Specifies the length of a time quantum.
 *          mode - Test mode.
 *            CAN_Mode_Normal.
 *            CAN_Mode_LoopBack.
 *            CAN_Mode_Silent.
 *            CAN_Mode_Silent_LoopBack.
 *
 * @return  none
 */
void CAN_Mode_Init(uint8_t tsjw, uint8_t tbs2, uint8_t tbs1, uint16_t brp, uint8_t mode )
{
    GPIO_InitTypeDef GPIO_InitSturcture={0};
    CAN_InitTypeDef CAN_InitSturcture={0};
    CAN_FilterInitTypeDef CAN_FilterInitSturcture={0};

    // GPIO端口时钟使能
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE );
    // 复用外设时钟使能
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_CAN1, ENABLE );

    /*
     *         RM手册P92
     * CANx_TX的GPIO配置为：推免复用输出
     * CANx_RX的GPIO配置为：浮空输入或上拉输入
     */
    GPIO_InitSturcture.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitSturcture.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitSturcture.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( GPIOA, &GPIO_InitSturcture);

    GPIO_InitSturcture.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitSturcture.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init( GPIOA, &GPIO_InitSturcture);

    CAN_InitSturcture.CAN_TTCM = DISABLE;
    CAN_InitSturcture.CAN_ABOM = DISABLE;
    CAN_InitSturcture.CAN_AWUM = DISABLE;
    CAN_InitSturcture.CAN_NART = ENABLE;
    CAN_InitSturcture.CAN_RFLM = DISABLE;
    CAN_InitSturcture.CAN_TXFP = DISABLE;
    CAN_InitSturcture.CAN_Mode = mode;
    CAN_InitSturcture.CAN_SJW = tsjw;
    CAN_InitSturcture.CAN_BS1 = tbs1;
    CAN_InitSturcture.CAN_BS2 = tbs2;
    CAN_InitSturcture.CAN_Prescaler = brp;
    CAN_Init( CAN1, &CAN_InitSturcture );

    CAN_FilterInitSturcture.CAN_FilterNumber = 0;

#if (Frame_Format == Standard_Frame)
/* identifier/mask mode, One 32-bit filter, StdId: 0x317 */
//    CAN_FilterInitSturcture.CAN_FilterMode = CAN_FilterMode_IdMask;
//    CAN_FilterInitSturcture.CAN_FilterScale = CAN_FilterScale_32bit;
//    CAN_FilterInitSturcture.CAN_FilterIdHigh = 0x62E0;
//    CAN_FilterInitSturcture.CAN_FilterIdLow = 0;
//    CAN_FilterInitSturcture.CAN_FilterMaskIdHigh = 0xFFE0;
//    CAN_FilterInitSturcture.CAN_FilterMaskIdLow = 0x0006;

/* identifier/mask mode, Two 16-bit filters, StdId: 0x317，0x316 */
//  CAN_FilterInitSturcture.CAN_FilterMode = CAN_FilterMode_IdMask;
//  CAN_FilterInitSturcture.CAN_FilterScale = CAN_FilterScale_16bit;
//  CAN_FilterInitSturcture.CAN_FilterIdHigh = 0x62E0;
//  CAN_FilterInitSturcture.CAN_FilterIdLow = 0xFFF8;
//  CAN_FilterInitSturcture.CAN_FilterMaskIdHigh = 0x62C0;
//  CAN_FilterInitSturcture.CAN_FilterMaskIdLow = 0xFFF8;

/* identifier list mode, One 32-bit filter, StdId: 0x317，0x316 */
//  CAN_FilterInitSturcture.CAN_FilterMode = CAN_FilterMode_IdList;
//  CAN_FilterInitSturcture.CAN_FilterScale = CAN_FilterScale_32bit;
//  CAN_FilterInitSturcture.CAN_FilterIdHigh = 0x62E0;
//  CAN_FilterInitSturcture.CAN_FilterIdLow = 0;
//  CAN_FilterInitSturcture.CAN_FilterMaskIdHigh = 0x62C0;
//  CAN_FilterInitSturcture.CAN_FilterMaskIdLow = 0;

/* identifier list mode, Two 16-bit filters, StdId: 0x317,0x316,0x315,0x314 */
  CAN_FilterInitSturcture.CAN_FilterMode = CAN_FilterMode_IdList;
  CAN_FilterInitSturcture.CAN_FilterScale = CAN_FilterScale_16bit;
  CAN_FilterInitSturcture.CAN_FilterIdHigh = JOINT_GENERAL_ID;
  CAN_FilterInitSturcture.CAN_FilterIdLow = FILTER_ID_AXIS_C;
  CAN_FilterInitSturcture.CAN_FilterMaskIdHigh = FILTER_ID_AXIS_B;
  CAN_FilterInitSturcture.CAN_FilterMaskIdLow = FILTER_ID_AXIS_A;

#elif (Frame_Format == Extended_Frame)
/* identifier/mask mode, One 32-bit filter, ExtId: 0x12124567 */
    CAN_FilterInitSturcture.CAN_FilterMode = CAN_FilterMode_IdMask;
    CAN_FilterInitSturcture.CAN_FilterScale = CAN_FilterScale_32bit;
    CAN_FilterInitSturcture.CAN_FilterIdHigh = 0x9092;
    CAN_FilterInitSturcture.CAN_FilterIdLow = 0x2B3C;
    CAN_FilterInitSturcture.CAN_FilterMaskIdHigh = 0xFFFF;
    CAN_FilterInitSturcture.CAN_FilterMaskIdLow = 0xFFFE;

#endif

    CAN_FilterInitSturcture.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
    CAN_FilterInitSturcture.CAN_FilterActivation = ENABLE;
    CAN_FilterInit( &CAN_FilterInitSturcture );

    CAN_ClearITPendingBit( CAN1, CAN_IT_FMP0 );
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    CAN_ITConfig( CAN1, CAN_IT_FMP0, ENABLE );
}

/*********************************************************************
 * @fn      CAN_Send_Msg
 *
 * @brief   CAN Transmit function.
 *
 * @param   msg - Transmit data buffer.
 *          len - Data length.
 *
 * @return  0 - Send successful.
 *          1 - Send failed.
 */
uint8_t CAN_Send_Msg(uint8_t *msg, uint8_t len, uint32_t _id)
{
    uint8_t mbox;
    uint16_t i = 0;

    CanTxMsg CanTxStructure;

#if (Frame_Format == Standard_Frame)
    CanTxStructure.StdId = _id;
    CanTxStructure.IDE = CAN_Id_Standard;

#elif (Frame_Format == Extended_Frame)
    CanTxStructure.ExtId = 0x12124567;
    CanTxStructure.IDE = CAN_Id_Extended;

#endif

    CanTxStructure.RTR = CAN_RTR_Data;
    CanTxStructure.DLC = len;

    for( i=0; i < len; i++ )
    {
        CanTxStructure.Data[i] = msg[i];
    }

    mbox = CAN_Transmit( CAN1, &CanTxStructure);
    i = 0;

    while( ( CAN_TransmitStatus( CAN1, mbox ) != CAN_TxStatus_Ok ) && (i < 0xFFF) )
    {
        i++;
    }

    if( i == 0xFFF )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*********************************************************************
 * @fn      CAN_Receive_Msg
 *
 * @brief   CAN Receive function.
 *
 * @param   buf - Receive data buffer.
 *          len - Data length.
 *
 * @return  CanRxStructure.DLC - Receive data length.
 */
uint8_t CAN_Receive_Msg(uint8_t *buf)
{
    uint8_t i;

    CanRxMsg CanRxStructure;

    if( CAN_MessagePending( CAN1, CAN_FIFO0 ) == 0)
    {
        return 0;
    }

    CAN_Receive( CAN1, CAN_FIFO0, &CanRxStructure );

    for( i=0; i< CanRxStructure.DLC; i++ )
    {
        buf[i] = CanRxStructure.Data[i];
    }

    return CanRxStructure.DLC;
}

