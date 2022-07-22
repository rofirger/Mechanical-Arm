/*
 * my_pit.c
 *
 *  Created on: 2022年7月1日
 *      Author: 随风
 */

#include "headfile.h"
#include "my_pit.h"
/*
 * 更改定时器频率
 */
void PitSetPeriodUs(TIM_TypeDef* _tim, uint32_t _us)
{
    uint32_t _period = _us * (SystemCoreClock / 1000000);
    uint16_t freq_div = (_period >> 15);
    uint16_t period_temp = (_period / (freq_div + 1));

    _tim->ATRLR = period_temp - 1 ;
    _tim->PSC = freq_div;
}
