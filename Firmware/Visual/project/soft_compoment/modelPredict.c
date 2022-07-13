//=====================================================================
//文件名称：modelPredict.c
//功能概要：模型驱动构件源文件
//制作单位：苏州大学嵌入式系统与物联网研究所(sumcu.suda.edu.cn)
//版    本：  2020-12-06  V2.0
//适用芯片：STM32
//=====================================================================

//包含的头文件
#include  "modelPredict.h"
#include "model_init.h"
//=====================================================================
//函数名称:GETLENGTH
//函数返回:数组长度

//参数说明:array:输入数组
//功能概要:计算数组元素个数
//=====================================================================
#define GETLENGTH(array) (sizeof(array)/sizeof(*(array)))

//=====================================================================
//函数名称:GETCOUNT
//函数返回:float数组元素个数
//参数说明:array:输入数组
//功能概要:计算float类型的数组个数
//=====================================================================
#define GETCOUNT(array)  (sizeof(array)/sizeof(float))

//=====================================================================
//函数名称:FOREACH
//函数返回:无
//参数说明:   i:临时计数变量
//        count:总循环次数
//功能概要:进行for循环
//=====================================================================
#define FOREACH(i,count) for (int i = 0; i < count; ++i)

//=====================================================================
//函数名称:Data_Padding
//函数返回:无
//参数说明:input:输入层元素数组指针，afterPadding:填充后元素数组指针,p:填充所需元素
//功能概要:填充输入层
//=====================================================================
#define Data_Padding(input,afterPadding,p)									\
{																			\
	FOREACH(w,GETLENGTH(afterPadding))									\
		FOREACH(h,GETLENGTH(*afterPadding))								\
		{																	\
			if(w>=p&&w<(GETLENGTH(*input)+p)&&h>=p&&h<(GETLENGTH(*input)+p))\
			{																\
				afterPadding[w][h]=input[w-p][h-p];							\
			}																\
			else															\
			{																\
				afterPadding[w][h]=0;										\
			}																\
		}																	\
}

//=====================================================================
//函数名称:CONVOLUTE_VALID
//函数返回:无
//参数说明:input:输入层元素数组首地址指针
//		  output:输出层元素数组首地址指针
//        weight:输入层与输出层之间权重数组指针
//        s:步长
//功能概要:进行权重的赋值传播
//=====================================================================
#define CONVOLUTE_VALID(input,output,weight,s)						\
{																	\
	for(int o0=0;o0<GETLENGTH(output);++o0)						\
		for(int o1=0;o1<GETLENGTH(*output);++o1)					\
			FOREACH(w0,GETLENGTH(weight))							\
				FOREACH(w1,GETLENGTH(*(weight)))					\
				(output)[o0][o1] += (input)[o0*s+w0][o1*s+w1] * (weight)[w0][w1];\
}

//=====================================================================
//函数名称:Conv2D
//函数返回:无
//参数说明:input:输入层元素数组首地址指针
//		  output:输出层元素数组首地址指针
//        kernel:输入层与输出层之间权值数组指针
//          bias:输入层与输出层之间偏置数组指针
//        strides:步长
//功能概要:进行卷积操作，填充输入，随后坐卷积操作
//=====================================================================
#define CONV2D(input,output,kernel,bias,strides)						\
{																			\
	int f=GetPadding_value(GETLENGTH(**kernel));							\
	float padding[GETLENGTH(input)][(GETLENGTH(*input)+2*f)][(GETLENGTH(*input)+2*f)];\
	FOREACH(i,GETLENGTH(input))											\
		Data_Padding(input[i],padding[i],f);							\
	FOREACH(x,GETLENGTH(kernel))											\
		FOREACH (y,GETLENGTH(*kernel))									\
			CONVOLUTE_VALID(padding[x],output[y],kernel[x][y],strides);\
	FOREACH(j, GETLENGTH(output))												\
		FOREACH(i, GETCOUNT(output[j]))										\
		((float *)output[j])[i] = ((float *)output[j])[i] + bias[j];			\
}

//=====================================================================
//函数名称:DEPTHWISE_CONV2D
//函数返回:无
//参数说明:input:输入层元素数组首地址指针
//		  output:输出层元素数组首地址指针
//        kernel:输入层与输出层之间权值数组指针
//          bias:输入层与输出层之间偏置数组指针
//        strides:步长
//功能概要:进行卷积操作，填充输入，随后坐卷积操作
//=====================================================================
#define DEPTHWISE_CONV2D(input,output,kernel,bias,strides)				\
{																				\
	int f=GetPadding_value(GETLENGTH(**kernel));							\
	float padding[GETLENGTH(input)][(GETLENGTH(*input)+2*f)][(GETLENGTH(*input)+2*f)];\
	FOREACH(i,GETLENGTH(input))										\
		Data_Padding(input[i],padding[i],f);								\
	FOREACH(x,GETLENGTH(kernel))												\
		FOREACH(y,GETLENGTH(*kernel))											\
			CONVOLUTE_VALID(padding[x],output[x],kernel[x][y],strides);	\
	FOREACH(j, GETLENGTH(output))												\
		FOREACH(i, GETCOUNT(output[j]))										\
		((float *)output[j])[i] = ((float *)output[j])[i] + bias[j];			\
}

//=====================================================================
//函数名称:BATCH_NORMALIZATION
//函数返回:无
//参数说明:input:输入层元素数组指针，output:输出元素数组指针
//数据：eps：增加到方差中的小浮动，以避免被零整除
//     momentum：移动到平均值和移动方差的动量
//     bnParam  0-beta  1-gamma 2-move_mean 3 -move_var
//功能概要:批量归一化处理
//=====================================================================
#define BATCH_NORMALIZATION(input,bnParam) 							\
{                    														\
	float eps=0.001;                										\
 	float beta[GETLENGTH(*bnParam)];										\
 	float gamma[GETLENGTH(*bnParam)];										\
 	float move_mean[GETLENGTH(*bnParam)];									\
 	float move_var[GETLENGTH(*bnParam)];									\
 	float x_normed[GETLENGTH(input)][GETLENGTH(*input)][GETLENGTH(**input)];\
 	FOREACH(w,GETLENGTH(*bnParam))										\
 	{																		\
 		(beta)[w]=(bnParam)[1][w];												\
 		(gamma)[w]=(bnParam)[0][w];												\
 		(move_mean)[w]=(bnParam)[2][w];											\
 		(move_var)[w]=(bnParam)[3][w];											\
 	}																		\
 	FOREACH(i,GETLENGTH(input))											\
 		FOREACH(j,GETLENGTH(*input))										\
 			FOREACH(k,GETLENGTH(**input))									\
 			{																\
 				(x_normed)[i][j][k]=((input)[i][j][k]-(move_mean)[i])/(Sqrt((move_var)[i]+eps));\
 				(input)[i][j][k]=gamma[i]*(x_normed)[i][j][k]+(beta)[i];			\
 			}																\
 }

//=====================================================================
//函数名称:ACTIVATION
//函数返回:无
//参数说明:input:输入层元素数组指针，output:输出元素数组指针
//数据：action：激活函数
//功能概要:激活函数	Activation
//=====================================================================
#define ACTIVATION(input) 							\
{																			\
	 FOREACH(j, GETLENGTH(input))									\
		FOREACH(i, GETCOUNT(input[j]))							\
			((float *)input[j])[i] = Relu6(((float *)input[j])[i]);	\
}
//=====================================================================
//函数名称:GlobalAveragePooling
//函数返回:无
//参数说明:input:输入层元素数组首地址指针
//		  output:输出层元素数组首地址指针
//功能概要:全局平均池化 对最后一层卷积的特征图，每个通道求整个特征图的均值
//GlobalAveragePooling
//=====================================================================
#define GLOBALAVERAGEPOOLING(input,output)							\
{																	\
	float aveage[GETLENGTH(input)];								\
	FOREACH(i,GETLENGTH(input))									\
	{																\
		float temp=0;												\
		FOREACH(j,GETLENGTH(*input))								\
		{															\
			FOREACH(k,GETLENGTH(**input))							\
			{														\
				temp+=(input)[i][j][k];								\
			}														\
		}															\
		(aveage)[i] =temp/((GETLENGTH(*input))*(GETLENGTH(**input)));\
	}																\
	FOREACH(i,GETLENGTH(output))									\
		FOREACH(j,GETLENGTH(*output))								\
			FOREACH(k,GETLENGTH(**output))						\
			(output)[i][j][k]=(aveage)[i];							\
}


//=====================================================================
//函数名称:GetPadding_value
//函数返回:无
//参数说明:f:卷积核维度
//功能概要:计算填充所需元素个数
//=====================================================================
int GetPadding_value(int f)
{
	int p;																	
	if(((f-1)%2)>0)										
		p=(f-1)/2+1;										
	else																	
		p=(f-1)/2;										
	return p;
}

//=====================================================================
//函数名称:Sqrt
//函数返回:输入值的开平方根
//参数说明:number:输入值
//功能概要:求开平方根函数
//=====================================================================
float Sqrt(float number)
{
	float new_guess;
	float last_guess;
	if(number < 0)
	{
		return -1;
	}
	if(number == 0)
	{
		return 0;
	}
	new_guess = 1;
	do
	{
		last_guess = new_guess;
		new_guess = (last_guess+number/last_guess)/2;

	}while(new_guess != last_guess);

	return new_guess;
}

//=====================================================================
//函数名称:relu6
//函数返回:激活值
//参数说明:x:待激活值
//功能概要:将输出值限制在(0,6)之间
//=====================================================================
float Relu6(float x)
{   
	if(x<=0)
		return 0;
	else if(x>6)
	    return 6;
	return x;		
}

//=====================================================================
//函数名称:Exp
//函数返回:自然指数值
//参数说明:x:输入值
//功能概要:求以自然数e为底，输入值为指数的值
//=====================================================================
float Exp(float x)
{
	int i,k,m,t;
	int xm = (int )x;
	float sum;
	float e;
	float ef;
	float z;
	float sub = x-xm;
	m=1;
	e=1.0;
	ef = 1.0;
	t = 10;
	z=1;
	sum = 1;
	if(xm<0)
	{
		xm=(-xm);
		for(k=0;k<xm;k++)
		{
			ef*=2.718281;
		}
		e/=ef;
	}
	else
	{
		for(k=0;k<xm;k++)
		{
			e*=2.718281;
		}
	}
	for(i=1;i<t;i++)
	{
		m*=i;
		z*=sub;
		sum+=z/m;
	}
	return sum*e;
}
//=====================================================================
//函数名称:relugrad
//函数返回:
//参数说明:y:输入值
//功能概要:判断输入值是否正负
//=====================================================================
float relugrad(float y)
{
	return y > 0;
}


//=====================================================================
//函数名称:Model_SoftmaxOut
//函数返回:回归后数组指针
//参数说明:input:输入层元素数组指针 
//		   count:需要回归的元素个数
//功能概要:将数组进行softmax回归
//=====================================================================
float * Model_SoftmaxOut(float *input,int count)
{
	float exparr[count];
	float expsum=0;
	int i;
	float temp;

	for(i=0;i<count;i++)
	{
		temp=input[i];
		exparr[i]=Exp(temp);
		expsum+=exparr[i];
	}
	
	
	for(i=0;i<count;i++)
	{
		input[i]=exparr[i]/expsum;	
	}

	return input;
}

//=====================================================================
//函数名称:Model_AverageOut
//函数返回:回归后数组指针
//参数说明:input:输入层元素数组指针
//		   count:需要回归的元素个数
//功能概要:将数组进行均值回归
//=====================================================================
float * Model_AverageOut(float *input,int count)
{
	int i=0;
	float sum=0;

	for(i=0;i<count;i++)
	{
		sum+=input[i];
	}
	
	
	for(i=0;i<count;i++)
	{
		input[i]=input[i]/sum;	

	}

	return input;
}

//=====================================================================
//函数名称:write_flash_array
//函数返回:无
//参数说明:buf:写入数组
//         size:数组的总字节数
//功能概要:写入Flash指定位置的数组
//=====================================================================
void write_flash_array(float *buf, uint32_t size)
{
	//(1)转为带符号整型便于计算
    int length = size;
    
    //(2)初始化数组指针偏移量为0
    uint16_t add=0;
    
    //(3.1)指定60扇区作为起始写入扇区
    for(uint16_t sect = 60; length>0;)
    {
    //(3.2)擦除指定扇区
        flash_erase(sect);    
        
    //(3.3)将数组写入Flash指定扇区
        if(length<2048)
        {
        	flash_write(sect, 0, length, (uint8_t *)(buf+add));
        	return ;
        }
        else
        {
        	flash_write(sect, 0, 2048, (uint8_t *)(buf+add));        	
        }
        length-=2048;
        add+=512;
        sect++;
    }
}

//=====================================================================
//函数名称:read_flash_array
//函数返回:无
//参数说明:buf:写入数组
//         size:数组的总字节数
//功能概要:读取Flash指定位置的数组
//=====================================================================
void read_flash_array(float *dest, uint32_t size)
{
	//(1)转为带符号整型便于计算
    int length = size;
    
    //(2)初始化数组指针偏移量为0
    uint16_t add = 0;
    
     //(3.1)指定60扇区作为起始写入扇区
    for(uint16_t sect = 60; length>0;)
    {
    
    	//(3.3)读取Flash指定扇区内容
    	 if(length<2048)
        {
        	flash_read_logic((uint8_t*)(dest+add), sect, 0, length); 
        	return ;
        }
        else
        {
        	flash_read_logic((uint8_t*)(dest+add), sect, 0, 2048);        	
        }
    	length-=2048;
        add+=512;
    	sect++;
    }
}

//=====================================================================
//函数名称:write_c2_flash
//函数返回:无
//参数说明:buf:写入数组
//         size:数组的总字节数
//功能概要:存放c2数据（Flash）
//=====================================================================
void write_c2_flash(float *buf, uint16_t size)
{
	//转为带符号整型便于计算
    int length = size ;
    
    //擦除指定扇区
    flash_erase(99);
    
    //将数组写入Flash指定扇区
    flash_write(99, 0, length, (uint8_t *)buf);
}

//=====================================================================
//函数名称:write_c2_flash
//函数返回:无
//参数说明:buf:写入数组
//         size:数组的总字节数
//功能概要:读取c2数据（Flash）
//=====================================================================
void read_c2_flash(float *dest, int size)
{
    //转为带符号整型便于计算
    int length = size ;
    
    //读取Flash指定扇区内容
    flash_read_logic((uint8_t *)dest, 99, 0, length); //从99扇区的第0位开始读取
}


//=====================================================================
//函数名称:ModelPredict_Part1
//函数返回:无
//参数说明:input:输入层元素数组
//功能概要:部分推理
//=====================================================================
void ModelPredict_Part1(float input[1][28][28])
{
	Model_Input model_input={0};		//输入-28×28×1
   	Model_Conv_Output m_c={0};			
   	Model_Conv1_Output c1={0};  		
   	Model_DepthwiseConv_Output m_d = {0};
   	Model_Conv2_Output c2_temp={0};
   
   	for(int w=0;w<28;w++)
	{
		for(int h=0;h<28;h++)
		{
			model_input[0][w][h]=input[0][w][h];
		}
	}
	
	//第一层卷积，步长为2  第一层输出--mc：14×14×6
	CONV2D(model_input,m_c,Model_Conv1_W,Model_Conv1_B,2);
	BATCH_NORMALIZATION(m_c,Model_BN1);
	ACTIVATION(m_c);
	
	//第二层卷积，步长为1--增维，第二层输出--c1：14×14×18
	CONV2D(m_c,c1,Model_Conv2_W,Model_Conv2_B,1);
	BATCH_NORMALIZATION(c1,Model_BN2);
	ACTIVATION(c1);
	
	//第一层深度卷积，步长为2，输出--m_d：7×7×18
	DEPTHWISE_CONV2D(c1,m_d,Model_DepthwiseConv1_W,Model_DepthwiseConv1_B,2);
	BATCH_NORMALIZATION(m_d,Model_BN3);
	ACTIVATION(m_d);

	//第三层卷积，步长为1--降维(未使用激活函数)，第三层输出--c2_temp：7×7×8
	CONV2D(m_d,c2_temp,Model_Conv3_W,Model_Conv3_B,1);
	BATCH_NORMALIZATION(c2_temp,Model_BN4);
	
	//将C2写入专门扇区，用于下次使用
    write_c2_flash((float*)c2_temp, sizeof(c2_temp));
}


//=====================================================================
//函数名称:ModelPredict_Part2
//函数返回:无
//参数说明:无
//功能概要:部分推理
//=====================================================================
void ModelPredict_Part2()
{
	//从存c2的扇区中读取数据
	Model_Conv2_Output c2={0};
	read_c2_flash((uint8_t*)c2,sizeof(c2));

	Model_Conv3_Output c3_t={0};
	
	//第四层卷积--增维，第四层输出--c3_t：7×7×24
	CONV2D(c2,c3_t,Model_Conv4_W,Model_Conv4_B,1);
	BATCH_NORMALIZATION(c3_t,Model_BN5);
	ACTIVATION(c3_t);
	
	//将输出结果存放到Flash中
	write_flash_array((float*)c3_t, sizeof(c3_t));
}

//=====================================================================
//函数名称:ModelPredict_Part3
//函数返回:无
//参数说明:无
//功能概要:部分推理
//=====================================================================
void ModelPredict_Part3()
{
	//从扇区中读取上一层卷积结果
	Model_Conv3_Output c3={0};
	read_flash_array((uint8_t*)c3, sizeof(c3));
	
	Model_DepthwiseConv1_Output d1_t ={0};
	
	//第二层深度卷积，步长为1，输出--d1_t：7×7×24
	DEPTHWISE_CONV2D(c3,d1_t,Model_DepthwiseConv2_W,Model_DepthwiseConv2_B,1);
	BATCH_NORMALIZATION(d1_t,Model_BN6);
	ACTIVATION(d1_t);
	
	
	Model_Conv4_Output c4_t={0};
	
	//第五层卷积--降维(未使用激活),输出--c4_t：7×7×8
	CONV2D(d1_t,c4_t,Model_Conv5_W,Model_Conv5_B,1);
	BATCH_NORMALIZATION(c4_t,Model_BN7);
	
	//将该层结果存放到Flash中
	write_flash_array((float*)c4_t, sizeof(c4_t));
} 

//=====================================================================
//函数名称:residual_add
//函数返回:无
//参数说明:无
//功能概要:进行残差操作
//=====================================================================
void residual_add()
{
	//获取上一层卷积结果
	Model_Conv4_Output c4={0};
	read_flash_array((uint8_t*)c4, sizeof(c4));
	
	//从指定扇区中读取C2
	Model_Conv2_Output c2={0};
	read_c2_flash((uint8_t*)c2, sizeof(c2)); 
	
	//输入输出进行特征叠加
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<7;j++)
		{
			for(int k=0;k<7;k++)
			{
				c4[i][j][k]=c4[i][j][k]+c2[i][j][k];
			}
		}
	}
	
	//将该层结果存放到Flash中
	write_flash_array((float*)c4, sizeof(c4));
}

//=====================================================================
//函数名称:ModelPredict_Part4
//函数返回:无
//参数说明:无
//功能概要:部分推理
//=====================================================================
void ModelPredict_Part4()
{
	//从Flash中读取上一层结果
	Model_Conv4_Output c4={0};
	read_flash_array((uint8_t*)c4, sizeof(c4));
	
	//第六层卷积--4×4×10
	Model_Conv5_Output c5_t={0};
	CONV2D(c4,c5_t,Model_Conv6_W,Model_Conv6_B,2)
	BATCH_NORMALIZATION(c5_t,Model_BN8);
	ACTIVATION(c5_t);
	
	//将该层结果存放到Flash中
	write_flash_array((float*)c5_t, sizeof(c5_t));
}

//=====================================================================
//函数名称:Model_PredictImage
//函数返回:回归后数组指针
//参数说明:input:输入层元素数组指针
//功能概要:将数组进行softmax回归
//=====================================================================
float *Model_PredictImage(float input[1][28][28])
{
	
	//定义模型传播用的特征图像数组
	Model_Conv5_Output c5={0};
	Model_Conv6_Output c6={0};
	Model_Conv7_Output c7={0};
	Model_GlobalAveragePooling mgp={0};
	Model_Conv8_Output c8={0};
	Model_Output result_output={0};
	float * output;
	
	//开始推理
	ModelPredict_Part1(input);
	
	ModelPredict_Part2();
	
	ModelPredict_Part3();
	
	residual_add();
	
	ModelPredict_Part4();
	
	//Flash中读取c5数据
	read_flash_array((uint8_t*)c5, sizeof(c5));
	
	//第7层卷积--输入10×4×4，卷积核14×3×3,步长为1
	CONV2D(c5,c6,Model_Conv7_W,Model_Conv7_B,1);
	BATCH_NORMALIZATION(c6,Model_BN9);
	ACTIVATION(c6);
	
	//第8层卷积--输入14×4×4，卷积核14×3×3,步长为1
	CONV2D(c6,c7,Model_Conv8_W,Model_Conv8_B,1);
	BATCH_NORMALIZATION(c7,Model_BN10);
	ACTIVATION(c7);
	
	//全局平均值池化
	GLOBALAVERAGEPOOLING(c7,mgp);
	
	//第9层卷积--输入16×1×1   卷积核SortNum ×1×1
	CONV2D(mgp,c8,Model_Conv9_W,Model_Conv9_B,1);
	wdog_feed();				//喂狗
	
	//将上一层3维数组转换为1维数组，数组大小为SortNum
	for(int i=0;i<SortNum;i++)
		result_output[i]=c8[i][0][0];
	
	//对输出数组进行softmax回归
	output=result_output;
	
	Model_SoftmaxOut(output,SortNum);	
	
	wdog_feed(); 				//喂狗
	
	//返回输出激活数组
	return output;
}
