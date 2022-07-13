/*
 * img_process.h
 *
 *  Created on: 2022年7月1日
 *      Author: 随风
 */

#ifndef IMG_PROCESS_H_
#define IMG_PROCESS_H_
#include "stddef.h"
#include "headfile.h"
#include "ov.h"

#ifndef bool
#define bool unsigned char
#endif

#ifndef false
#define false   0
#endif

#ifndef true
#define true    1
#endif

#define ABS(_num)      ((_num) >= 0 ? (_num) : (-(_num)))

extern const uint16_t img_height;
extern const uint16_t img_width;
extern uint8_t binary_dvp_img[ROW_TFT_HEIGHT][ROW_TFT_WIDTH / 2];



typedef struct Pos
{
    int16_t _x;
    int16_t _y;
}Pos;
typedef Pos RedPointPos;

typedef struct RedLinePos
{
    RedPointPos _red_point_pos;
    uint8_t _length;
    uint8_t _width;
}RedLinePos;



uint8_t SeekRed(RedLinePos* _pos, uint16_t* _img, uint16_t _width, uint16_t _height, uint8_t* _binary_dvp_img);
int16_t SeekRedLine(uint8_t* _red_binary_dvp_img, uint16_t _width, uint16_t _height);

#endif /* IMG_PROCESS_H_ */
