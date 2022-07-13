/*
 * Config.h
 *       Brief: 机械臂主板的引脚定义
 *  Created on: 2022年5月15日
 *      Author: 随风
 */

#ifndef CONFIG_H_
#define CONFIG_H_

// TFT 屏相关引脚定义
#define TFT_SCL                  B13                                      // SPI CLK
#define TFT_SDA                  B15                                      // SPI MOSI
#define TFT_RES                  D10                                      // 液晶复位引脚定义
#define TFT_DC                   D8                                       // 液晶命令位引脚定义
#define TFT_CS                   B12                                      // CS 片选引脚
#define TFT_BL                   D12                                      // 液晶背光引脚定义

// CAN 相关引脚定义
#define CAN1_TX                  A12
#define CAN1_RX                  A11
#define CAN2_TX                  B13
#define CAN2_RX                  B12

// 外置128K flash 相关引脚定义
#define FLASH_SPI_PRESCALER              SPI_BaudRatePrescaler_8
#define FLASH_SPI                        SPI1
#define FLASH_SPI_GPIO                   GPIOA
#define FLASH_SPI_CS                     GPIO_Pin_4
#define FLASH_SPI_CS_GPIO                GPIOA
#define FLASH_SPI_SCK                    GPIO_Pin_5
#define FLASH_SPI_MISO                   GPIO_Pin_6
#define FLASH_SPI_MOSI                   GPIO_Pin_7

// BLINK 指示灯引脚定义
#define LED_INDICATOR            A10

// 按键相关引脚定义
#define BUTTON1                  A2
#define BUTTON2                  A3

// 5KEY 相关引脚定义
#define KEY_UP                   E1
#define KEY_DOWN                 E2
#define KEY_MID                  D13
#define KEY_LEFT                 D6
#define KEY_RIGHT                E3

// 蜂鸣器引脚定义
#define BEEP                     E15

// USB 相关引脚定义
#define DN1                      A11
#define DP1                      A12
#define DN2                      B6
#define DP2                      B7

// ETH 相关引脚定义
#define TXN                      C9
#define TXP                      C8
#define RXN                      C7
#define RXP                      C6
#define EGREEN_LED               E11
#define EYELLOW_LED              E12

// CH9141-BLE 相关引脚定义
#define BLE_SLEEP                C13
#define BLE_RST
#define BLE_RX                   C2
#define BLE_TX                   C3
#define BLE_AT                   A7

// MyESP32 相关引脚定义
#define MYESP_RX                 B10
#define MYESP_TX                 B11
#define MYESP_SCLK               B3
#define MYESP_MOSI               B5
#define MYESP_MISO               B4
#define MYESP_CS                 D7

// button2中断
#define BUTTON2_GPIO_PIN     GPIO_Pin_3
#define BUTTON2_GPIO_PORT    GPIOA
#define BUTTON2_PORT_SOURCE  GPIO_PortSourceGPIOA
#define BUTTON2_PIN_SOURCE   GPIO_PinSource3
#define BUTTON2_LINE         EXTI_Line3
#define BUTTON2_IRQ          EXTI3_IRQn

// 5key中断
#define KEYUP_GPIO_PIN     GPIO_Pin_1
#define KEYUP_GPIO_PORT    GPIOE
#define KEYUP_PORT_SOURCE  GPIO_PortSourceGPIOE
#define KEYUP_PIN_SOURCE   GPIO_PinSource1
#define KEYUP_LINE         EXTI_Line1
#define KEYUP_IRQ          EXTI1_IRQn

#define KEYDOWN_GPIO_PIN     GPIO_Pin_2
#define KEYDOWN_GPIO_PORT    GPIOE
#define KEYDOWN_PORT_SOURCE  GPIO_PortSourceGPIOE
#define KEYDOWN_PIN_SOURCE   GPIO_PinSource2
#define KEYDOWN_LINE         EXTI_Line2
#define KEYDOWN_IRQ          EXTI2_IRQn

#define KEYLEFT_GPIO_PIN     GPIO_Pin_6
#define KEYLEFT_GPIO_PORT    GPIOD
#define KEYLEFT_PORT_SOURCE  GPIO_PortSourceGPIOD
#define KEYLEFT_PIN_SOURCE   GPIO_PinSource6
#define KEYLEFT_LINE         EXTI_Line6
#define KEYLEFT_IRQ          EXTI9_5_IRQn

#endif /* CONFIG_H_ */
