/*
 * my_function.c
 *
 *  Created on: 2022年6月2日
 *      Author: lenovo
 */
#include "zf_common_headfile.h"
#include "Config.h"

//舵机
float angle_set_duty(float angle)
{
    float angle_time = (angle/45+1)*0.5;
    return angle_time/20.0*10000;
}

