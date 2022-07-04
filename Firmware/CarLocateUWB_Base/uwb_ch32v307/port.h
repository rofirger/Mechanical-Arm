/*
 * port.h
 *
 *  Created on: 2022年6月4日
 *      Author: 随风
 */

#ifndef _PORT_H_
#define _PORT_H_
#include "ch32v30x_conf.h"

// DW1000 SPI数据交流端口
#define SPIx_PRESCALER              SPI_BaudRatePrescaler_8
#define SPIx                        SPI1
#define SPIx_GPIO                   GPIOA
#define SPIx_CS                     GPIO_Pin_4
#define SPIx_CS_GPIO                GPIOA
#define SPIx_SCK                    GPIO_Pin_5
#define SPIx_MISO                   GPIO_Pin_6
#define SPIx_MOSI                   GPIO_Pin_7

// 复位
#define DW1000_RSTn                 GPIO_Pin_8
#define DW1000_RSTn_GPIO            GPIOD

// 复位引脚中断定义
#define DECARSTIRQ                  GPIO_Pin_8
#define DECARSTIRQ_GPIO             GPIOD
#define DECARSTIRQ_EXTI             EXTI_Line8
#define DECARSTIRQ_EXTI_PORT        GPIO_PortSourceGPIOD
#define DECARSTIRQ_EXTI_PIN         GPIO_PinSource8
#define DECARSTIRQ_EXTI_IRQn        EXTI9_5_IRQn

// DW1000中断引脚定义
#define DECAIRQ                     GPIO_Pin_2
#define DECAIRQ_GPIO                GPIOA
#define DECAIRQ_EXTI                EXTI_Line2
#define DECAIRQ_EXTI_PORT           GPIO_PortSourceGPIOA
#define DECAIRQ_EXTI_PIN            GPIO_PinSource2
#define DECAIRQ_EXTI_IRQn           EXTI2_IRQn
#define DECAIRQ_EXTI_USEIRQ         ENABLE
#define DECAIRQ_EXTI_NOIRQ          DISABLE

#define port_SPIx_busy_sending()        (SPI_I2S_GetFlagStatus((SPIx),(SPI_I2S_FLAG_TXE))==(RESET))
#define port_SPIx_no_data()             (SPI_I2S_GetFlagStatus((SPIx),(SPI_I2S_FLAG_RXNE))==(RESET))
#define port_SPIx_send_data(x)          SPI_I2S_SendData((SPIx),(x))
#define port_SPIx_receive_data()        SPI_I2S_ReceiveData(SPIx)
#define port_SPIx_disable()             SPI_Cmd(SPIx,DISABLE)
#define port_SPIx_enable()              SPI_Cmd(SPIx,ENABLE)
#define port_SPIx_set_chip_select()     GPIO_SetBits(SPIx_CS_GPIO,SPIx_CS)
#define port_SPIx_clear_chip_select()   GPIO_ResetBits(SPIx_CS_GPIO,SPIx_CS)

#define port_GetEXT_IRQStatus()             EXTI_GetITEnStatus(DECAIRQ_EXTI_IRQn)
#define port_DisableEXT_IRQ()               NVIC_DisableIRQ(DECAIRQ_EXTI_IRQn)
#define port_EnableEXT_IRQ()                NVIC_EnableIRQ(DECAIRQ_EXTI_IRQn)
#define port_CheckEXT_IRQ()                 GPIO_ReadInputDataBit(DECAIRQ_GPIO, DECAIRQ)
#endif
