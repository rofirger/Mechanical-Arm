/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2018,逐飞科技
* All rights reserved.
*
* 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
* 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
*
* @file             zf_common_typedef
* @company          成都逐飞科技有限公司
* @author           逐飞科技(QQ790875685)
* @version          查看doc内version文件 版本说明
* @Software         MounRiver Studio V1.51
* @Target core      CH32V307VCT6
* @Taobao           https://seekfree.taobao.com/
* @date             2021-11-25
********************************************************************************************************************/

#ifndef _zf_common_typedef_h_
#define _zf_common_typedef_h_

#include "stdio.h"
#include "stdint.h"
#include "stdarg.h"
#include "string.h"

//=================================================== 类型定义 ===================================================

#define COMPATIBLE_WITH_OLDER_VERSIONS                                       	// 兼容旧版开源库接口
#define USE_ZF_TYPEDEF      1                                                   // 是否启用类型定义申明
#if USE_ZF_TYPEDEF
// 数据类型声明
// 尽量使用 stdint.h 定义的类型名称 避免冲突 这里可以裁剪
#ifndef uint8
typedef unsigned char       uint8;                                              // 无符号  8 bits
#endif
#ifndef uint16
typedef unsigned short int  uint16;                                             // 无符号 16 bits
#endif
#ifndef uint32
typedef unsigned int        uint32;                                             // 无符号 32 bits
#endif
#ifndef uint64
typedef unsigned long long  uint64;                                             // 无符号 64 bits
#endif

#ifndef int8
typedef signed char         int8;                                               // 有符号  8 bits
#endif
#ifndef int16
typedef signed short int    int16;                                              // 有符号 16 bits
#endif
#ifndef int32
typedef signed int          int32;                                              // 有符号 32 bits
#endif
#ifndef int64
typedef signed long long    int64;                                              // 有符号 64 bits
#endif

typedef volatile uint8      vuint8;                                             // 易变性修饰 无符号  8 bits
typedef volatile uint16     vuint16;                                            // 易变性修饰 无符号 16 bits
typedef volatile uint32     vuint32;                                            // 易变性修饰 无符号 32 bits
typedef volatile uint64     vuint64;                                            // 易变性修饰 无符号 64 bits

typedef volatile int8       vint8;                                              // 易变性修饰 有符号  8 bits
typedef volatile int16      vint16;                                             // 易变性修饰 有符号 16 bits
typedef volatile int32      vint32;                                             // 易变性修饰 有符号 32 bits
typedef volatile int64      vint64;                                             // 易变性修饰 有符号 64 bits
#endif



//=================================================== 类型定义 ===================================================

#endif
