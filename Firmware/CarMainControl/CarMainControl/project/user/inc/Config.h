/*
 * Config.h
 *
 *  Created on: 2022年5月17日
 *      Author: 随风
 */

#ifndef CONFIG_H_
#define CONFIG_H_

// 驱动板控制引脚定义
#define MOTOR_PWM1              A0
#define MOTOR_PWM2              A2
#define MOTOR_PWM3              D12
#define MOTOR_PWM4              D14
#define MOTOR_PWM5              A1
#define MOTOR_PWM6              A3
#define MOTOR_PWM7              D13
#define MOTOR_PWM8              D15
#define MOTOR_EN                A15

//电机
#define PWM_T3_1            TIM2_PWM_CH1_A0
#define PWM_T3_2            TIM2_PWM_CH3_A2
#define PWM_T4_3            TIM4_PWM_CH1_D12
#define PWM_T4_4            TIM4_PWM_CH3_D14
#define PWM_T5_5            TIM2_PWM_CH2_A1
#define PWM_T5_6            TIM2_PWM_CH4_A3
#define PWM_T6_7            TIM4_PWM_CH2_D13
#define PWM_T6_8            TIM4_PWM_CH4_D15

// 蜂鸣器
#define BEEP                    E15

// ICM20602
#define ICM_SCK                 B3
#define ICM_MOSI                B5
#define ICM_MISO                B4
#define ICM_CS                  C10

// IMU901-10
#define IMU_TX                  C4
#define IMU_RX                  C5

// MY-UWB
#define MYESP_RX                C3
#define MYESP_TX                C2
#define MYESP_SCK               B13
#define MYESP_MOSI              B15
#define MYESP_MISO              B14
#define MYESP_CS                B12

// 5KEY 内部已包含上拉电阻
#define KEY_LEFT                D6
#define KEY_MID                 D13
#define KEY_UP                  E1
#define KEY_RIGHT               E3
#define KEY_DOWN                E2

// 指示灯
#define INDICATOR               E7

// USB
#define USB_DN1                 A11
#define USB_DP1                 A12
#define USB_DN2                 B6
#define USB_DP2                 B7

// 超声波测距模块
#define ULTRASONIC1_TRIG        B0
#define ULTRASONIC1_ECHO        B1
#define ULTRASONIC2_TRIG        D6
#define ULTRASONIC2_ECHO        D13
#define ULTRASONIC3_TRIG        E0
#define ULTRASONIC3_ECHO        E1
#define ULTRASONIC4_TRIG        A7
#define ULTRASONIC4_ECHO        E6

// 舵机
#define STEER1_PWM              A8
#define STEER2_PWM              E11
#define STEER3_PWM              E13
#define STEER4_PWM              E14

// GPS
#define GPS_TX                  B10
#define GPS_RX                  B11
#define GPS_PPS                 E15

// TFT
#define TFT_SCK                 B13
#define TFT_MOSI                B15
#define TFT_RST                 D10
#define TFT_DC                  D7
#define TFT_CS                  D4
#define TFT_BL                  D0

// 编码器 note: B/Dir
#define ENCODER1_A              E11
#define ENCODER1_B              E9
#define ENCODER2_A              C7
#define ENCODER2_B              C6
#define ENCODER3_A              D11
#define ENCODER3_B              D9
#define ENCODER4_A              D3
#define ENCODER4_B              D1

// ESP01/01S
#define ESP01_RX                C0
#define ESP01_TX                C1

#endif /* CONFIG_H_ */
