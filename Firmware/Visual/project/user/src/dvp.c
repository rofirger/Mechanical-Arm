/*
 * dvp.c
 *
 *  Created on: 2022年6月3日
 *      Author: 随风
 */
#include "ov.h"
#include "stdio.h"
#include "ch32v30x.h"
#include "ch32v30x_rcc.h"
#include "zf_common_headfile.h"
#include "dvp.h"
extern uint8_t dvp_img_finish_flag;


UINT32 JPEG_DVPDMAaddr0 = 0x20005000;
UINT32 JPEG_DVPDMAaddr1 = 0x20005000 + OV2640_JPEG_WIDTH;

UINT32 RGB565_DVPDMAaddr0 = 0x2000A000;
UINT32 RGB565_DVPDMAaddr1 = 0x2000A000 + RGB565_COL_NUM * 2; // each byte(D9-D2) will take 2 bytes of RAM

volatile UINT32 href_cnt = 0;

__aligned(4) uint16 img_dvp[ROW_TFT_HEIGHT][ROW_TFT_WIDTH / 2];

void DVP_OV_Init()
{
    // 打开DVP模块的时钟信号
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DVP, ENABLE);
    // 清除DVP寄存器CR0
    DVP->CR0 &= ~RB_DVP_MSK_DAT_MOD;
    // 配置DVP寄存器
    DVP->CR0 |= RB_DVP_D10_MOD | RB_DVP_V_POLAR;
    DVP->CR1 &= ~((RB_DVP_ALL_CLR)| RB_DVP_RCV_CLR);
    DVP->ROW_NUM = RGB565_ROW_NUM;
    DVP->COL_NUM = RGB565_COL_NUM;

    DVP->HOFFCNT = (RGB565_COL_NUM - ROW_TFT_WIDTH) / 2;
    DVP->VST = (RGB565_ROW_NUM - ROW_TFT_HEIGHT) / 2;
    DVP->CAPCNT = ROW_TFT_WIDTH;
    DVP->VLINE = ROW_TFT_HEIGHT;
    // 开启裁剪
    DVP->CR1 |= RB_DVP_CROP;

    DVP->DMA_BUF0 = (uint32)RGB565_DVPDMAaddr0;
    DVP->DMA_BUF1 = (uint32)RGB565_DVPDMAaddr1;


    // DVP帧捕获率控制
    DVP->CR1 &= ~RB_DVP_FCRC;
    // 设置帧捕获率为100%
    DVP->CR1 |= DVP_RATE_100P;

    // 帧结束中断使能
    DVP->IER |= RB_DVP_IE_FRM_DONE;
    // 行结束中断使能
    DVP->IER |= RB_DVP_IE_ROW_DONE;

    NVIC_InitTypeDef NVIC_InitStructure = {0};
    NVIC_InitStructure.NVIC_IRQChannel = DVP_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    DVP->CR1 |= RB_DVP_DMA_EN; // enable DMA
    DVP->CR0 |= RB_DVP_ENABLE; // enable DVP

}
void dvp_handler()
{
    dvp_img_finish_flag = 1;

}
