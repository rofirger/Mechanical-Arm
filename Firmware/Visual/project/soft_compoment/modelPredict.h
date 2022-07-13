//=====================================================================
//文件名称：model_Predict_Gary.h
//功能概要：模型驱动构件源文件
//制作单位：苏州大学嵌入式系统与物联网研究所(sumcu.suda.edu.cn)
//版    本：  2020-11-07  V1.0
//适用芯片：STM32
//=====================================================================

#include "headfile.h"
#include "modelPreprocess.h"
#include "stdlib.h"
#define SortNum 10

//定义输入模型的图像矩阵大小
typedef uint8_t image_28[28][28];

// 定义模型传播所使用的特征图像结构体
typedef float Model_Input[1][28][28];   			//输入层

//普通卷积，步长为2
typedef float Model_Conv_Output[6][14][14];   	   //第1层卷积输出	

//第一层可分离卷积
typedef float Model_Conv1_Output[18][14][14];     //第2层卷积输出	

typedef float Model_DepthwiseConv_Output[18][7][7]; //第1层深度卷积输出

typedef float Model_Conv2_Output[8][7][7];  		//第3层卷积输出

//第二层可分离卷积
typedef float Model_Conv3_Output[24][7][7];  		//第4层卷积输出

typedef float Model_DepthwiseConv1_Output[24][7][7];//第2层深度卷积输出

typedef float Model_Conv4_Output[8][7][7];  		//第5层卷积输出	


typedef float Model_Conv5_Output[10][4][4];  		//第6层卷积输出

typedef float Model_Conv6_Output[14][4][4];  		//第7层卷积输出	

typedef float Model_Conv7_Output[16][4][4];  		//第8层卷积输出

//全局平均池化 global_average_pooling
typedef float Model_GlobalAveragePooling[16][1][1]; //全局平均值池化输出

typedef float Model_Conv8_Output[SortNum][1][1];  	//第9层卷积输出		

//最终输出
typedef float Model_Output[SortNum];  				//模型最终输出


//=====================================================================
//函数名称:Model_SoftmaxOut
//函数返回:回归后数组指针
//参数说明:input:输入层元素数组指针
//功能概要:将数组进行softmax回归
//=====================================================================
float *Model_SoftmaxOut(float *input,int count);


//=====================================================================
//函数名称:Model_AverageOut
//函数返回:回归后数组指针 
//参数说明:input:输入层元素数组指针
//功能概要:经过均值算法得出每个物体的识别概率
//=====================================================================
float * Model_AverageOut(float *input,int count);

//=====================================================================
//函数名称:Model_PredictImage
//函数返回:回归后数组指针
//参数说明:input:输入层元素数组指针
//功能概要:将数组进行softmax回归
//=====================================================================
float *Model_PredictImage(float input[1][28][28]);
