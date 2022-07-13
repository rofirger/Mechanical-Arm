//===================================================================== 
//�ļ����ƣ�model_init.h 
//���ܸ�Ҫ��ģ�ͳ�ʼ�������ļ� 
//��    ����V1.0 
//ʹ��оƬ��STM32 
//===================================================================== 
#ifndef MODEL_INIT_H 

#define MODEL_INIT_H 

#define SortNum 10 

extern   const float Model_Conv1_W[1][6][3][3];     //�����1����˵�Ȩ��

extern   const float Model_Conv1_B[6];               //�����1����˵�Ȩ��

extern   const float Model_Conv2_W[6][18][1][1];     //�����2����˵�Ȩ��

extern   const float Model_Conv2_B[18];             //�����2����˵�Ȩ��

extern   const float Model_Conv3_W[18][8][1][1];     //�����3����˵�Ȩ��

extern   const float Model_Conv3_B[8];              //�����3����˵�Ȩ��

extern   const float Model_Conv4_W[8][24][1][1];    //�����4����˵�Ȩ��

extern   const float Model_Conv4_B[24];             //�����4����˵�Ȩ��

extern  const float Model_Conv5_W[24][8][1][1];    //�����5����˵�Ȩ��

extern  const float Model_Conv5_B[8];             //�����5����˵�Ȩ��

extern   const float Model_Conv6_W[8][10][3][3];    //�����6����˵�Ȩ��

extern   const float Model_Conv6_B[10];             //�����6����˵�Ȩ��

extern   const float Model_Conv7_W[10][14][3][3];    //�����7����˵�Ȩ��

extern   const float Model_Conv7_B[14];             //�����7����˵�Ȩ��

extern   const float Model_Conv8_W[14][16][1][1];    //�����8����˵�Ȩ��

extern   const float Model_Conv8_B[16];             //�����8����˵�Ȩ��

extern   const float Model_Conv9_W[16][10][1][1];    //�����9����˵�Ȩ��

extern   const float Model_Conv9_B[10];              //�����9����˵�Ȩ��

extern   const float Model_DepthwiseConv1_W[18][1][3][3];    //��Ⱦ����1����˵�Ȩ��

extern   const float Model_DepthwiseConv1_B[18];    //��Ⱦ����1����˵�Ȩ��

extern   const float Model_DepthwiseConv2_W[24][1][3][3];    //��Ⱦ����2����˵�Ȩ��

extern   const float Model_DepthwiseConv2_B[24];    //��Ⱦ����2����˵�Ȩ��

 // ��ȡ ÿ��BN��һ�������Ħ� �� moving_mean moving_variance��С   

extern   const float Model_BN1[4][6];

extern   const float Model_BN2[4][18];

extern  const float Model_BN3[4][18];

extern  const float Model_BN4[4][8];

extern  const float Model_BN5[4][24];

extern  const float Model_BN6[4][24];

extern  const float Model_BN7[4][8];

extern const float Model_BN8[4][10];

extern const float Model_BN9[4][14];

extern const float Model_BN10[4][16];

#endif /* MODEL_INIT_H */ 
