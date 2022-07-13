//===================================================================== 
//文件名称：model_init.h 
//功能概要：模型初始化构件文件 
//版    本：V1.0 
//使用芯片：STM32 
//===================================================================== 
#ifndef MODEL_INIT_H 

#define MODEL_INIT_H 

#define SortNum 10 

extern   const float Model_Conv1_W[1][6][3][3];     //卷积层1卷积核的权重

extern   const float Model_Conv1_B[6];               //卷积层1卷积核的权重

extern   const float Model_Conv2_W[6][18][1][1];     //卷积层2卷积核的权重

extern   const float Model_Conv2_B[18];             //卷积层2卷积核的权重

extern   const float Model_Conv3_W[18][8][1][1];     //卷积层3卷积核的权重

extern   const float Model_Conv3_B[8];              //卷积层3卷积核的权重

extern   const float Model_Conv4_W[8][24][1][1];    //卷积层4卷积核的权重

extern   const float Model_Conv4_B[24];             //卷积层4卷积核的权重

extern  const float Model_Conv5_W[24][8][1][1];    //卷积层5卷积核的权重

extern  const float Model_Conv5_B[8];             //卷积层5卷积核的权重

extern   const float Model_Conv6_W[8][10][3][3];    //卷积层6卷积核的权重

extern   const float Model_Conv6_B[10];             //卷积层6卷积核的权重

extern   const float Model_Conv7_W[10][14][3][3];    //卷积层7卷积核的权重

extern   const float Model_Conv7_B[14];             //卷积层7卷积核的权重

extern   const float Model_Conv8_W[14][16][1][1];    //卷积层8卷积核的权重

extern   const float Model_Conv8_B[16];             //卷积层8卷积核的权重

extern   const float Model_Conv9_W[16][10][1][1];    //卷积层9卷积核的权重

extern   const float Model_Conv9_B[10];              //卷积层9卷积核的权重

extern   const float Model_DepthwiseConv1_W[18][1][3][3];    //深度卷积层1卷积核的权重

extern   const float Model_DepthwiseConv1_B[18];    //深度卷积层1卷积核的权重

extern   const float Model_DepthwiseConv2_W[24][1][3][3];    //深度卷积层2卷积核的权重

extern   const float Model_DepthwiseConv2_B[24];    //深度卷积层2卷积核的权重

 // 获取 每层BN归一化网络层的β γ moving_mean moving_variance大小   

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
