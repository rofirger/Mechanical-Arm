/*
 * img_process.c
 *
 *  Created on: 2022��7��1��
 *      Author: ���
 */

#include "img_process.h"
#include "math.h"
#include "ov.h"

RedLinePos red_line_pos[10];
// �Ƿ��Ѿ����
uint8_t seeked_pixel_flag[(ROW_TFT_HEIGHT * ROW_TFT_WIDTH / 2) >> 3] = {0};
/*
 * @brief:Ѱ��ͼ���к�ɫ������λ��
 */
uint8_t SeekRed(RedLinePos* _pos, uint16_t* _img, uint16_t _width, uint16_t _height, uint8_t* _red_binary_dvp_img)
{
    uint8_t _num_red_pos = 0;

    uint32_t _r, _g, _b;
    for (uint16_t _i = 0; _i < _height; ++_i)
    {
        for (uint16_t _j = 0; _j < _width; ++_j)
        {
            uint16_t _pixel;
            _pixel = _img[_i * _width + _j];
            _pixel = ((_pixel & 0xff) << 8) | (_pixel >> 8);
            _r = _pixel >> 11;
            _g = (_pixel >> 5) & 0x3f;
            _b = _pixel & 0x1f;
            // �жϺ�ɫ��
            if (_r > (_g + 3) && _r > (_b + 3))
            {
                _red_binary_dvp_img[_i * _width + _j] = 0;
                //_img[_i * _width + _j] = 0x0;
                // ��������
//                if ((seeked_pixel_flag[( _i * _width + _j) >> 3] & ((uint8_t)1 << (( _i * _width + _j) % 8))) == 0)
//                {
//                    seeked_pixel_flag[( _i * _width + _j) >> 3] |= ((uint8_t)1 << (( _i * _width + _j) % 8));
//                    RedPointPos _start_point_pos;
//                    _start_point_pos._x = _j;
//                    _start_point_pos._y = _i;
//                    // ��������һ�����£�һ������
//                    for (uint16_t _h = _i + 1; _h < _width; ++_h)
//                    {
//                        // �����μ�����
//                        uint8_t _lt_flag = seeked_pixel_flag[( _i * _width + _width) >> 3] & ((uint8_t)1 << (( _i * _width + _width) % 8));
//                    }
//                }
            }
            else {
                _red_binary_dvp_img[_i * _width + _j] = 255;
            }
        }
    }

    return _num_red_pos;
}

/*
 *  @brief:Ѱ�Һ�ɫ������
 *  @return:��Ч��-1����߽���ڲ������ĺ�ɫ�飺-2���ұ߽���ڲ������ĺ�ɫ�飺-3
 */
int16_t SeekRedLine(uint8_t* _red_binary_dvp_img, uint16_t _width, uint16_t _height)
{
    int16_t _width_start_point = -1;
    int16_t _width_end_point = -1;
    int16_t _height_start_point = -1;
    int16_t _height_end_point = -1;
    uint8_t _red_block_height = 0;
    bool _is_white_line = false;
    bool _is_square_red_block = true;
//    uint8_t _i = 8;
//    for (; _i < _height - 8; ++_i)
//    {
//        uint8_t _num_white = 0;
//        for (uint8_t _j = 0; _j < _width - 1; ++_j)
//        {
//            if (_red_binary_dvp_img[_i * _width + _j] == 0 && _red_binary_dvp_img[_i * _width + _j + 1] == 0)
//            {
//                if (_width_start_point == -1)
//                    _width_start_point = _j;
//                if (_height_start_point == -1)
//                    _height_start_point = _i;
//            }
//            else {
//                _num_white++;
//            }
//            if (_width_start_point != -1)
//            {
//                if (_width_end_point == -1 && _red_binary_dvp_img[_i * _width + _j] == 255 && _red_binary_dvp_img[_i * _width + _j + 1] == 255)
//                {
//                    _width_end_point = _j;
//                    break;
//                }
//            }
//            if (_j == _width - 2 && _width_start_point != -1 && _width_end_point == -1)
//            {
//                _width_start_point = -1;
//                _height_start_point = -1;
//            }
//        }
//        if (_num_white > _width - 3)
//            _is_white_line = true;
//        else
//            _is_white_line = false;
//        if (_is_white_line && _height_end_point == -1
//             && _width_start_point != -1
//             && _height_start_point != -1
//             && _width_end_point != -1)
//        {
//            _is_white_line = false;
//            _height_end_point = _i;
//            if (false == _is_square_red_block)
//            {
//                if (_i > 2 * _width / 3)
//                    return -1;
//                if (ABS(_width_end_point - _width_start_point - _height_end_point - _height_start_point) < (_width_end_point - _width_start_point) * 2)
//                {
//                    _is_square_red_block = true;
//                    _red_block_height = _height_end_point - _height_start_point;
//                    _num_white = 0;
//                    _width_start_point = -1;
//                    _width_end_point = -1;
//                    _height_start_point = -1;
//                    _height_end_point = -1;
//                    break;
//                }
//                else {
//                    return -1;
//                }
//            }
//        }
//    }
    // ƫ��
    if (_is_square_red_block)
    {
        uint8_t _start_row = _height / 2;
        if (_start_row > _height - 3)
            return -1;
        uint8_t _ret_num_red_block = 0;
        bool _is_start = false;
        uint8_t _line_start = 0;
        for (uint8_t _j = 0; _j < _width - 1; ++_j)
        {
            if (false == _is_start && _red_binary_dvp_img[_start_row * _width + _j] == 0 && _red_binary_dvp_img[_start_row * _width + _j + 1] == 0)
            {
                _is_start = true;
                _line_start = _j;
            }
            if (true == _is_start && _red_binary_dvp_img[_start_row * _width + _j] == 255 && _red_binary_dvp_img[_start_row * _width + _j + 1] == 255)
            {
                _is_start = false;
                if (_j - _line_start > 2)
                    _ret_num_red_block++;
            }
        }
        return _ret_num_red_block;
    }
    return -1;
}





