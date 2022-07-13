//=====================================================================
//�ļ����ƣ�model_Predict_Gary.h
//���ܸ�Ҫ��ģ����������Դ�ļ�
//������λ�����ݴ�ѧǶ��ʽϵͳ���������о���(sumcu.suda.edu.cn)
//��    ����  2020-11-07  V1.0
//����оƬ��STM32
//=====================================================================

#include "headfile.h"
#include "modelPreprocess.h"
#include "stdlib.h"
#define SortNum 10

//��������ģ�͵�ͼ������С
typedef uint8_t image_28[28][28];

// ����ģ�ʹ�����ʹ�õ�����ͼ��ṹ��
typedef float Model_Input[1][28][28];   			//�����

//��ͨ���������Ϊ2
typedef float Model_Conv_Output[6][14][14];   	   //��1�������	

//��һ��ɷ�����
typedef float Model_Conv1_Output[18][14][14];     //��2�������	

typedef float Model_DepthwiseConv_Output[18][7][7]; //��1����Ⱦ�����

typedef float Model_Conv2_Output[8][7][7];  		//��3�������

//�ڶ���ɷ�����
typedef float Model_Conv3_Output[24][7][7];  		//��4�������

typedef float Model_DepthwiseConv1_Output[24][7][7];//��2����Ⱦ�����

typedef float Model_Conv4_Output[8][7][7];  		//��5�������	


typedef float Model_Conv5_Output[10][4][4];  		//��6�������

typedef float Model_Conv6_Output[14][4][4];  		//��7�������	

typedef float Model_Conv7_Output[16][4][4];  		//��8�������

//ȫ��ƽ���ػ� global_average_pooling
typedef float Model_GlobalAveragePooling[16][1][1]; //ȫ��ƽ��ֵ�ػ����

typedef float Model_Conv8_Output[SortNum][1][1];  	//��9�������		

//�������
typedef float Model_Output[SortNum];  				//ģ���������


//=====================================================================
//��������:Model_SoftmaxOut
//��������:�ع������ָ��
//����˵��:input:�����Ԫ������ָ��
//���ܸ�Ҫ:���������softmax�ع�
//=====================================================================
float *Model_SoftmaxOut(float *input,int count);


//=====================================================================
//��������:Model_AverageOut
//��������:�ع������ָ�� 
//����˵��:input:�����Ԫ������ָ��
//���ܸ�Ҫ:������ֵ�㷨�ó�ÿ�������ʶ�����
//=====================================================================
float * Model_AverageOut(float *input,int count);

//=====================================================================
//��������:Model_PredictImage
//��������:�ع������ָ��
//����˵��:input:�����Ԫ������ָ��
//���ܸ�Ҫ:���������softmax�ع�
//=====================================================================
float *Model_PredictImage(float input[1][28][28]);
