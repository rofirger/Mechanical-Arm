/*
 * my_function.c
 *
 *  Created on: 2022��6��2��
 *      Author: lenovo
 */
#include "zf_common_headfile.h"
#include "Config.h"

//���
float angle_set_duty(float angle)
{
    float angle_time = (angle/45+1)*0.5;
    return angle_time/20.0*10000;
}

