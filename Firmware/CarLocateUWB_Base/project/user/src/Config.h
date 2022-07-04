/*
 * Config.h
 *
 *  Created on: 2022年5月29日
 *      Author: 随风
 */

#ifndef CONFIG_H_
#define CONFIG_H_

// UWB相关引脚定义
#define UWB_SPI_CS_PORT              GPIOA
#define UWB_SPI_SCK_PORT             GPIOA
#define UWB_SPI_MISO_PORT            GPIOA
#define UWB_SPI_MOSI_PORT            GPIOA
#define UWB_SPI_WAKEUP_PORT          GPIOA
#define UWB_SPI_IRQ_PORT             GPIOA
#define UWB_SPI_EXTON_PORT           GPIOD
#define UWB_SPI_RST_PORT             GPIOD

#define UWB_SPI_IRQ_PIN              GPIO_Pin_2
#define UWB_SPI_WAKEUP_PIN           GPIO_Pin_3
#define UWB_SPI_CS_PIN               GPIO_Pin_4
#define UWB_SPI_SCK_PIN              GPIO_Pin_5
#define UWB_SPI_MISO_PIN             GPIO_Pin_6
#define UWB_SPI_MOSI_PIN             GPIO_Pin_7
#define UWB_SPI_EXTON_PIN            GPIO_Pin_9
#define UWB_SPI_RST_PIN              GPIO_Pin_8

// 接口
#define INTERFACE_RX_PORT            GPIOB
#define INTERFACE_TX_PORT            GPIOB
#define INTERFACE_SPI_SCK_PORT       GPIOB
#define INTERFACE_SPI_MISO_PORT      GPIOB
#define INTERFACE_SPI_MOSI_PORT      GPIOB
#define INTERFACE_SPI_CS_PORT        GPIOD

#define INTERFACE_RX_PIN            GPIO_Pin_10
#define INTERFACE_TX_PIN            GPIO_Pin_11
#define INTERFACE_SPI_SCK_PIN       GPIO_Pin_3
#define INTERFACE_SPI_MISO_PIN      GPIO_Pin_4
#define INTERFACE_SPI_MOSI_PIN      GPIO_Pin_5
#define INTERFACE_SPI_CS_PIN        GPIO_Pin_7

#endif /* CONFIG_H_ */
