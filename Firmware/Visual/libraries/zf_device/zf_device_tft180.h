/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,逐飞科技
* All rights reserved.
*
* 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
* 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
*
* @file             zf_device_tft180
* @company          成都逐飞科技有限公司
* @author           逐飞科技(QQ790875685)
* @version          查看doc内version文件 版本说明
* @Software         MounRiver Studio V1.51
* @Target core      CH32V307VCT6
* @Taobao           https://seekfree.taobao.com/
* @date             2021-11-25
* @note             接线定义：
*                   ------------------------------------
*                   模块管脚                                        单片机管脚
*                   SCL                 查看 zf_device_tft180.h 中 TFT180_SCL_PIN 宏定义
*                   SDA                 查看 zf_device_tft180.h 中 TFT180_SDA_PIN 宏定义
*                   RES                 查看 zf_device_tft180.h 中 TFT180_RES_PIN 宏定义
*                   DC                  查看 zf_device_tft180.h 中 TFT180_DC_PIN 宏定义
*                   CS                  查看 zf_device_tft180.h 中 TFT180_CS_PIN 宏定义
*                   BL                  查看 zf_device_tft180.h 中 TFT180_BL_PIN 宏定义
*                   电源引脚
*                   VCC                 3.3V电源
*                   GND                 电源地
*                   最大分辨率160*128
*                   ------------------------------------
********************************************************************************************************************/

#ifndef _zf_device_tft180_h_
#define _zf_device_tft180_h_


#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_common_font.h"
#include "zf_common_function.h"

#include "zf_driver_delay.h"
#include "zf_driver_spi.h"
//#include "zf_driver_soft_spi.h"

#define TFT180_USE_SOFT_SPI             0                                       // 默认使用硬件 SPI 方式驱动 建议使用硬件 SPI 方式驱动
#if TFT180_USE_SOFT_SPI                                                         // 这两段 颜色正常的才是正确的 颜色灰的就是没有用的
//====================================================软件 SPI 驱动====================================================
#define TFT180_SOFT_SPI_DELAY           1                                       // 软件 SPI 的时钟延时周期 数值越小 SPI 通信速率越快
#define TFT180_SCL_PIN                  D4                                      // 软件 SPI SCK 引脚
#define TFT180_SDA_PIN                  D6                                      // 软件 SPI MOSI 引脚
//====================================================软件 SPI 驱动====================================================
#else
//====================================================硬件 SPI 驱动====================================================
#define TFT180_SPI_SPEED                system_clock/4                          // 硬件 SPI 速率
#define TFT180_SPI                      SPI_2                                   // 硬件 SPI 号
#define TFT180_SCL_PIN                  SPI2_SCK_B13                            // 硬件 SPI SCK 引脚
#define TFT180_SDA_PIN                  SPI2_MOSI_B15                           // 硬件 SPI MOSI 引脚
//====================================================硬件 SPI 驱动====================================================
#endif

#define TFT180_RES_PIN                  D10                                      // 液晶复位引脚定义
#define TFT180_DC_PIN                   D7                                      // 液晶命令位引脚定义
#define TFT180_CS_PIN                   D4                                      // CS 片选引脚
#define TFT180_BL_PIN                   D0                                      // 液晶背光引脚定义

#define TFT180_DC(x)                    (x? (gpio_high(TFT180_DC_PIN)): (gpio_low(TFT180_DC_PIN)))
#define TFT180_RES(x)                   (x? (gpio_high(TFT180_RES_PIN)): (gpio_low(TFT180_RES_PIN)))
#define TFT180_CS(x)                    (x? (gpio_high(TFT180_CS_PIN)): (gpio_low(TFT180_CS_PIN)))
#define TFT180_BL(x)                    (x? (gpio_high(TFT180_BL_PIN)): (gpio_low(TFT180_BL_PIN)))

typedef enum
{
    TFT180_PORTAIT                      = 0,                                    // 竖屏模式
    TFT180_PORTAIT_180                  = 1,                                    // 竖屏模式  旋转180
    TFT180_CROSSWISE                    = 2,                                    // 横屏模式
    TFT180_CROSSWISE_180                = 3,                                    // 横屏模式  旋转180
}tft180_dir_enum;

#define TFT180_DEFAULT_DISPLAY_DIR      TFT180_CROSSWISE_180                          // 默认的显示方向
#define TFT180_DEFAULT_PENCOLOR         RGB565_RED                                     // 默认的画笔颜色
#define TFT180_DEFAULT_BGCOLOR          RGB565_WHITE                                   // 默认的背景颜色

extern uint16 tft180_pencolor;
extern uint16 tft180_bgcolor;

extern tft180_dir_enum tft180_display_dir;
extern uint8 tft180_x_max;
extern uint8 tft180_y_max;

void    tft180_clear                    (const uint16 color);
void    tft180_set_dir                  (tft180_dir_enum dir);
void    tft180_set_color                (const uint16 pen, const  uint16 bgcolor);
void    tft180_draw_point               (uint16 x, uint16 y, const uint16 color);
void    tft180_draw_line                (uint16 x_start, uint16 y_start, uint16 x_end, uint16 y_end, const uint16 color);

void    tft180_show_char                (uint16 x, uint16 y, const char dat);
void    tft180_show_string              (uint16 x, uint16 y, const char dat[]);
void    tft180_show_int                 (uint16 x,uint16 y, const int32 dat, uint8 num);
void    tft180_show_uint                (uint16 x,uint16 y, const uint32 dat, uint8 num);
void    tft180_show_float               (uint16 x,uint16 y, const float dat, uint8 num, uint8 pointnum);

void    tft180_show_binary_image        (uint16 x, uint16 y, const uint8 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height);
void    tft180_show_gray_image          (uint16 x, uint16 y, const uint8 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height, uint8 threshold);
void    tft180_show_rgb565_image        (uint16 x, uint16 y, const uint16 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height, uint8 color_mode);

void    tft180_show_wave                (uint16 x, uint16 y, const uint16 *wave, uint16 width, uint16 value_max, uint16 dis_width, uint16 dis_value_max);
void    tft180_show_chinese             (uint16 x, uint16 y, uint8 size, const uint8 *chinese_buffer, uint8 number, const uint16 color);

#define tft180_displayimage7725(p,width,height)                                 tft180_show_binary_image(0,0,p,width,height,width,height)

#define tft180_displayimage032(p,width,height)                                  tft180_show_gray_image(0,0,p,width,height,width,height,0)
#define tft180_displayimage032_zoom(p,width,height,dis_width,dis_height)        tft180_show_gray_image(0,0,p,width,height,dis_width,dis_height,0)
#define tft180_displayimage032_zoom1(p,width,height,x,y,dis_width,dis_height)   tft180_show_gray_image(x,y,p,width,height,dis_width,dis_height,0)

#define tft180_displayimage8660(p,width,height)                                 tft180_show_rgb565_image(0,0,p,width,height,width,height,1)
#define tft180_displayimage8660_zoom(p,width,height,dis_width,dis_height)       tft180_show_rgb565_image(0,0,p,width,height,dis_width,dis_height,1)
#define tft180_displayimage8660_zoom1(p,width,height,x,y,dis_width,dis_height)  tft180_show_rgb565_image(x,y,p,width,height,dis_width,dis_height,1)

void    tft180_init                     (void);

#endif

