/*
 * port.c
 *
 *  Created on: 2022年6月4日
 *      Author: 随风
 */
#include "port.h"

static uint16_t p_ms = 0;
void Delay_Ms(uint32_t n)
{
    uint32_t i;

    SysTick->SR &= ~(1 << 0);
    i = (uint32_t)n * p_ms;

    SysTick->CMP = i;
    SysTick->CTLR |= (1 << 4) | (1 << 5) | (1 << 0);

    while((SysTick->SR & (1 << 0)) != (1 << 0))
        ;
    SysTick->CTLR &= ~(1 << 0);
}

/*
 * @brief:  关闭DW1000中断引脚
 * */
int NVIC_DW_DisableDECAIRQ(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;

    /* Configure EXTI line */
    EXTI_InitStructure.EXTI_Line = DECAIRQ_EXTI;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  //MPW3 IRQ polarity is high by default
    EXTI_InitStructure.EXTI_LineCmd = DECAIRQ_EXTI_NOIRQ;
    EXTI_Init(&EXTI_InitStructure);

    return 0;
}

/*
 * @brief:  DW1000中断引脚配置
 * */
int NVIC_DW_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    // Enable GPIO used as DECA IRQ for interrupt
    GPIO_InitStructure.GPIO_Pin = DECAIRQ;
    GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPD;  //IRQ pin should be Pull Down to prevent unnecessary EXT IRQ while DW1000 goes to sleep mode
    GPIO_Init(DECAIRQ_GPIO, &GPIO_InitStructure);

    /* Connect EXTI Line to GPIO Pin */
    GPIO_EXTILineConfig(DECAIRQ_EXTI_PORT, DECAIRQ_EXTI_PIN);

    /* Configure EXTI line */
    EXTI_InitStructure.EXTI_Line = DECAIRQ_EXTI;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  //MPW3 IRQ polarity is high by default
    EXTI_InitStructure.EXTI_LineCmd = DECAIRQ_EXTI_USEIRQ;
    EXTI_Init(&EXTI_InitStructure);

    /* Set NVIC Grouping to 16 groups of interrupt without sub-grouping */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

    /* Enable and set EXTI Interrupt to the lowest priority */
    NVIC_InitStructure.NVIC_IRQChannel = DECAIRQ_EXTI_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 15;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = DECAIRQ_EXTI_USEIRQ;

    NVIC_Init(&NVIC_InitStructure);

    /* Enable the RTC Interrupt */
    //NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
    //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 10;
    //NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    //NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    //NVIC_Init(&NVIC_InitStructure);

    return 0;
}

/*
 * @brief:  获取对应的外部中断通道的事件使能状态
 * */
ITStatus EXTI_GetITEnStatus(uint32_t EXTI_Line)
{
  ITStatus bit_status = RESET;
  uint32_t enable_status = 0;

  enable_status =  EXTI->EVENR & EXTI_Line;
  if (enable_status != (uint32_t)RESET)
  {
      bit_status = SET;
  }
  else
  {
      bit_status = RESET;
  }
  return bit_status;
}

/*
 * @brief:  SPI波特率修改
 * @note :  在通讯时不可以修改波特率
 * */
void SPI_ChangeRate(SPI_TypeDef* spi_port, uint16_t scaling_factor)
{
    uint16_t tmpreg = 0;
    tmpreg = spi_port->CTLR1;
    // 将CTLR1寄存器的[5:3]置零
    tmpreg &= 0xFFC7;
    // 配置CTLR1寄存器的[5:3]
    tmpreg |= scaling_factor;
    // 写入寄存器
    spi_port->CTLR1 = tmpreg;
}

/*
 * @brief:  配置SPI速率，使之小于3MHz，以能正确完成DW1000的初始化工作
 * @add  :  CH32V307系统时钟最高144MHz 144MHz / 64 = 2.25MHz
 */
void SPI_DW_SetRateLow (SPI_TypeDef* spi_port)
{
    SPI_ChangeRate(spi_port, SPI_BaudRatePrescaler_64);
}

/*
 * @brief:  配置SPI速率，使之尽可能接近20MHz(锁定CLKPLL时，DW1000所能接受的最大SPI速率. 详细请查看DW1000手册)
 */
void SPI_DW_SetRateHigh(SPI_TypeDef* spi_port)
{
    SPI_ChangeRate(spi_port, SPI_BaudRatePrescaler_8);
}

/*
 * @brief:  SPI初始化
 */
void SPI_DW_Configuration(SPI_TypeDef* spi_port, uint16_t scaling_factor)
{
    SPI_InitTypeDef  SPI_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_I2S_DeInit(spi_port);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  // 双线双向全双工
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;

    // 选择SPI模式0，此模式下不需要额外配置DW1000的GPIO5/6
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;

    SPI_InitStructure.SPI_BaudRatePrescaler = scaling_factor;                          // 定义波特率预分频的值
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                               // 主机模式，使用软件控制NSS引脚
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;                      // 指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
    SPI_InitStructure.SPI_CRCPolynomial = 7;

    SPI_Init(spi_port, &SPI_InitStructure);

    // 相关引脚配置
    GPIO_InitStructure.GPIO_Pin = SPIx_CS;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SPIx_CS_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = SPIx_SCK;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SPIx_CS_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = SPIx_MOSI;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SPIx_CS_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = SPIx_MISO;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SPIx_CS_GPIO, &GPIO_InitStructure);

    // 使能SPI
    SPI_Cmd(spi_port, ENABLE);

    // 将CS引脚拉高
    GPIO_SetBits(SPIx_CS_GPIO, SPIx_CS);
}

/*
 * @brief:  复位DW1000
 */
void Reset_DW1000(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = DW1000_RSTn;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(DW1000_RSTn_GPIO, &GPIO_InitStructure);

    GPIO_ResetBits(DW1000_RSTn_GPIO, DW1000_RSTn);

    GPIO_InitStructure.GPIO_Pin = DW1000_RSTn;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(DW1000_RSTn_GPIO, &GPIO_InitStructure);

    Delay_Ms(2);
}

void SetUp_DW1000RSTnIRQ(FunctionalState state)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    if(state)
    {
        // Enable GPIO used as DECA IRQ for interrupt
        GPIO_InitStructure.GPIO_Pin = DECARSTIRQ;
        //GPIO_InitStructure.GPIO_Mode =    GPIO_Mode_IPD;  //IRQ pin should be Pull Down to prevent unnecessary EXT IRQ while DW1000 goes to sleep mode
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(DECARSTIRQ_GPIO, &GPIO_InitStructure);

        /* Connect EXTI Line to GPIO Pin */
        GPIO_EXTILineConfig(DECARSTIRQ_EXTI_PORT, DECARSTIRQ_EXTI_PIN);

        /* Configure EXTI line */
        EXTI_InitStructure.EXTI_Line = DECARSTIRQ_EXTI;
        EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  //MP IRQ polarity is high by default
        EXTI_InitStructure.EXTI_LineCmd = ENABLE;
        EXTI_Init(&EXTI_InitStructure);

        /* Set NVIC Grouping to 16 groups of interrupt without sub-grouping */
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

        /* Enable and set EXTI Interrupt to the lowest priority */
        NVIC_InitStructure.NVIC_IRQChannel = DECARSTIRQ_EXTI_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 15;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

        NVIC_Init(&NVIC_InitStructure);
    }
    else
    {
        //put the pin back to tri-state ... as input
        GPIO_InitStructure.GPIO_Pin = DW1000_RSTn;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(DW1000_RSTn_GPIO, &GPIO_InitStructure);

        /* Configure EXTI line */
        EXTI_InitStructure.EXTI_Line = DECARSTIRQ_EXTI;
        EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  //MP IRQ polarity is high by default
        EXTI_InitStructure.EXTI_LineCmd = DISABLE;
        EXTI_Init(&EXTI_InitStructure);
    }
}
