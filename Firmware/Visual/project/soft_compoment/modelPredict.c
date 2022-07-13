//=====================================================================
//�ļ����ƣ�modelPredict.c
//���ܸ�Ҫ��ģ����������Դ�ļ�
//������λ�����ݴ�ѧǶ��ʽϵͳ���������о���(sumcu.suda.edu.cn)
//��    ����  2020-12-06  V2.0
//����оƬ��STM32
//=====================================================================

//������ͷ�ļ�
#include  "modelPredict.h"
#include "model_init.h"
//=====================================================================
//��������:GETLENGTH
//��������:���鳤��

//����˵��:array:��������
//���ܸ�Ҫ:��������Ԫ�ظ���
//=====================================================================
#define GETLENGTH(array) (sizeof(array)/sizeof(*(array)))

//=====================================================================
//��������:GETCOUNT
//��������:float����Ԫ�ظ���
//����˵��:array:��������
//���ܸ�Ҫ:����float���͵��������
//=====================================================================
#define GETCOUNT(array)  (sizeof(array)/sizeof(float))

//=====================================================================
//��������:FOREACH
//��������:��
//����˵��:   i:��ʱ��������
//        count:��ѭ������
//���ܸ�Ҫ:����forѭ��
//=====================================================================
#define FOREACH(i,count) for (int i = 0; i < count; ++i)

//=====================================================================
//��������:Data_Padding
//��������:��
//����˵��:input:�����Ԫ������ָ�룬afterPadding:����Ԫ������ָ��,p:�������Ԫ��
//���ܸ�Ҫ:��������
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
//��������:CONVOLUTE_VALID
//��������:��
//����˵��:input:�����Ԫ�������׵�ַָ��
//		  output:�����Ԫ�������׵�ַָ��
//        weight:������������֮��Ȩ������ָ��
//        s:����
//���ܸ�Ҫ:����Ȩ�صĸ�ֵ����
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
//��������:Conv2D
//��������:��
//����˵��:input:�����Ԫ�������׵�ַָ��
//		  output:�����Ԫ�������׵�ַָ��
//        kernel:������������֮��Ȩֵ����ָ��
//          bias:������������֮��ƫ������ָ��
//        strides:����
//���ܸ�Ҫ:���о��������������룬������������
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
//��������:DEPTHWISE_CONV2D
//��������:��
//����˵��:input:�����Ԫ�������׵�ַָ��
//		  output:�����Ԫ�������׵�ַָ��
//        kernel:������������֮��Ȩֵ����ָ��
//          bias:������������֮��ƫ������ָ��
//        strides:����
//���ܸ�Ҫ:���о��������������룬������������
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
//��������:BATCH_NORMALIZATION
//��������:��
//����˵��:input:�����Ԫ������ָ�룬output:���Ԫ������ָ��
//���ݣ�eps�����ӵ������е�С�������Ա��ⱻ������
//     momentum���ƶ���ƽ��ֵ���ƶ�����Ķ���
//     bnParam  0-beta  1-gamma 2-move_mean 3 -move_var
//���ܸ�Ҫ:������һ������
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
//��������:ACTIVATION
//��������:��
//����˵��:input:�����Ԫ������ָ�룬output:���Ԫ������ָ��
//���ݣ�action�������
//���ܸ�Ҫ:�����	Activation
//=====================================================================
#define ACTIVATION(input) 							\
{																			\
	 FOREACH(j, GETLENGTH(input))									\
		FOREACH(i, GETCOUNT(input[j]))							\
			((float *)input[j])[i] = Relu6(((float *)input[j])[i]);	\
}
//=====================================================================
//��������:GlobalAveragePooling
//��������:��
//����˵��:input:�����Ԫ�������׵�ַָ��
//		  output:�����Ԫ�������׵�ַָ��
//���ܸ�Ҫ:ȫ��ƽ���ػ� �����һ����������ͼ��ÿ��ͨ������������ͼ�ľ�ֵ
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
//��������:GetPadding_value
//��������:��
//����˵��:f:�����ά��
//���ܸ�Ҫ:�����������Ԫ�ظ���
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
//��������:Sqrt
//��������:����ֵ�Ŀ�ƽ����
//����˵��:number:����ֵ
//���ܸ�Ҫ:��ƽ��������
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
//��������:relu6
//��������:����ֵ
//����˵��:x:������ֵ
//���ܸ�Ҫ:�����ֵ������(0,6)֮��
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
//��������:Exp
//��������:��Ȼָ��ֵ
//����˵��:x:����ֵ
//���ܸ�Ҫ:������Ȼ��eΪ�ף�����ֵΪָ����ֵ
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
//��������:relugrad
//��������:
//����˵��:y:����ֵ
//���ܸ�Ҫ:�ж�����ֵ�Ƿ�����
//=====================================================================
float relugrad(float y)
{
	return y > 0;
}


//=====================================================================
//��������:Model_SoftmaxOut
//��������:�ع������ָ��
//����˵��:input:�����Ԫ������ָ�� 
//		   count:��Ҫ�ع��Ԫ�ظ���
//���ܸ�Ҫ:���������softmax�ع�
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
//��������:Model_AverageOut
//��������:�ع������ָ��
//����˵��:input:�����Ԫ������ָ��
//		   count:��Ҫ�ع��Ԫ�ظ���
//���ܸ�Ҫ:��������о�ֵ�ع�
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
//��������:write_flash_array
//��������:��
//����˵��:buf:д������
//         size:��������ֽ���
//���ܸ�Ҫ:д��Flashָ��λ�õ�����
//=====================================================================
void write_flash_array(float *buf, uint32_t size)
{
	//(1)תΪ���������ͱ��ڼ���
    int length = size;
    
    //(2)��ʼ������ָ��ƫ����Ϊ0
    uint16_t add=0;
    
    //(3.1)ָ��60������Ϊ��ʼд������
    for(uint16_t sect = 60; length>0;)
    {
    //(3.2)����ָ������
        flash_erase(sect);    
        
    //(3.3)������д��Flashָ������
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
//��������:read_flash_array
//��������:��
//����˵��:buf:д������
//         size:��������ֽ���
//���ܸ�Ҫ:��ȡFlashָ��λ�õ�����
//=====================================================================
void read_flash_array(float *dest, uint32_t size)
{
	//(1)תΪ���������ͱ��ڼ���
    int length = size;
    
    //(2)��ʼ������ָ��ƫ����Ϊ0
    uint16_t add = 0;
    
     //(3.1)ָ��60������Ϊ��ʼд������
    for(uint16_t sect = 60; length>0;)
    {
    
    	//(3.3)��ȡFlashָ����������
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
//��������:write_c2_flash
//��������:��
//����˵��:buf:д������
//         size:��������ֽ���
//���ܸ�Ҫ:���c2���ݣ�Flash��
//=====================================================================
void write_c2_flash(float *buf, uint16_t size)
{
	//תΪ���������ͱ��ڼ���
    int length = size ;
    
    //����ָ������
    flash_erase(99);
    
    //������д��Flashָ������
    flash_write(99, 0, length, (uint8_t *)buf);
}

//=====================================================================
//��������:write_c2_flash
//��������:��
//����˵��:buf:д������
//         size:��������ֽ���
//���ܸ�Ҫ:��ȡc2���ݣ�Flash��
//=====================================================================
void read_c2_flash(float *dest, int size)
{
    //תΪ���������ͱ��ڼ���
    int length = size ;
    
    //��ȡFlashָ����������
    flash_read_logic((uint8_t *)dest, 99, 0, length); //��99�����ĵ�0λ��ʼ��ȡ
}


//=====================================================================
//��������:ModelPredict_Part1
//��������:��
//����˵��:input:�����Ԫ������
//���ܸ�Ҫ:��������
//=====================================================================
void ModelPredict_Part1(float input[1][28][28])
{
	Model_Input model_input={0};		//����-28��28��1
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
	
	//��һ����������Ϊ2  ��һ�����--mc��14��14��6
	CONV2D(model_input,m_c,Model_Conv1_W,Model_Conv1_B,2);
	BATCH_NORMALIZATION(m_c,Model_BN1);
	ACTIVATION(m_c);
	
	//�ڶ�����������Ϊ1--��ά���ڶ������--c1��14��14��18
	CONV2D(m_c,c1,Model_Conv2_W,Model_Conv2_B,1);
	BATCH_NORMALIZATION(c1,Model_BN2);
	ACTIVATION(c1);
	
	//��һ����Ⱦ��������Ϊ2�����--m_d��7��7��18
	DEPTHWISE_CONV2D(c1,m_d,Model_DepthwiseConv1_W,Model_DepthwiseConv1_B,2);
	BATCH_NORMALIZATION(m_d,Model_BN3);
	ACTIVATION(m_d);

	//��������������Ϊ1--��ά(δʹ�ü����)�����������--c2_temp��7��7��8
	CONV2D(m_d,c2_temp,Model_Conv3_W,Model_Conv3_B,1);
	BATCH_NORMALIZATION(c2_temp,Model_BN4);
	
	//��C2д��ר�������������´�ʹ��
    write_c2_flash((float*)c2_temp, sizeof(c2_temp));
}


//=====================================================================
//��������:ModelPredict_Part2
//��������:��
//����˵��:��
//���ܸ�Ҫ:��������
//=====================================================================
void ModelPredict_Part2()
{
	//�Ӵ�c2�������ж�ȡ����
	Model_Conv2_Output c2={0};
	read_c2_flash((uint8_t*)c2,sizeof(c2));

	Model_Conv3_Output c3_t={0};
	
	//���Ĳ���--��ά�����Ĳ����--c3_t��7��7��24
	CONV2D(c2,c3_t,Model_Conv4_W,Model_Conv4_B,1);
	BATCH_NORMALIZATION(c3_t,Model_BN5);
	ACTIVATION(c3_t);
	
	//����������ŵ�Flash��
	write_flash_array((float*)c3_t, sizeof(c3_t));
}

//=====================================================================
//��������:ModelPredict_Part3
//��������:��
//����˵��:��
//���ܸ�Ҫ:��������
//=====================================================================
void ModelPredict_Part3()
{
	//�������ж�ȡ��һ�������
	Model_Conv3_Output c3={0};
	read_flash_array((uint8_t*)c3, sizeof(c3));
	
	Model_DepthwiseConv1_Output d1_t ={0};
	
	//�ڶ�����Ⱦ��������Ϊ1�����--d1_t��7��7��24
	DEPTHWISE_CONV2D(c3,d1_t,Model_DepthwiseConv2_W,Model_DepthwiseConv2_B,1);
	BATCH_NORMALIZATION(d1_t,Model_BN6);
	ACTIVATION(d1_t);
	
	
	Model_Conv4_Output c4_t={0};
	
	//�������--��ά(δʹ�ü���),���--c4_t��7��7��8
	CONV2D(d1_t,c4_t,Model_Conv5_W,Model_Conv5_B,1);
	BATCH_NORMALIZATION(c4_t,Model_BN7);
	
	//���ò�����ŵ�Flash��
	write_flash_array((float*)c4_t, sizeof(c4_t));
} 

//=====================================================================
//��������:residual_add
//��������:��
//����˵��:��
//���ܸ�Ҫ:���вв����
//=====================================================================
void residual_add()
{
	//��ȡ��һ�������
	Model_Conv4_Output c4={0};
	read_flash_array((uint8_t*)c4, sizeof(c4));
	
	//��ָ�������ж�ȡC2
	Model_Conv2_Output c2={0};
	read_c2_flash((uint8_t*)c2, sizeof(c2)); 
	
	//�������������������
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
	
	//���ò�����ŵ�Flash��
	write_flash_array((float*)c4, sizeof(c4));
}

//=====================================================================
//��������:ModelPredict_Part4
//��������:��
//����˵��:��
//���ܸ�Ҫ:��������
//=====================================================================
void ModelPredict_Part4()
{
	//��Flash�ж�ȡ��һ����
	Model_Conv4_Output c4={0};
	read_flash_array((uint8_t*)c4, sizeof(c4));
	
	//��������--4��4��10
	Model_Conv5_Output c5_t={0};
	CONV2D(c4,c5_t,Model_Conv6_W,Model_Conv6_B,2)
	BATCH_NORMALIZATION(c5_t,Model_BN8);
	ACTIVATION(c5_t);
	
	//���ò�����ŵ�Flash��
	write_flash_array((float*)c5_t, sizeof(c5_t));
}

//=====================================================================
//��������:Model_PredictImage
//��������:�ع������ָ��
//����˵��:input:�����Ԫ������ָ��
//���ܸ�Ҫ:���������softmax�ع�
//=====================================================================
float *Model_PredictImage(float input[1][28][28])
{
	
	//����ģ�ʹ����õ�����ͼ������
	Model_Conv5_Output c5={0};
	Model_Conv6_Output c6={0};
	Model_Conv7_Output c7={0};
	Model_GlobalAveragePooling mgp={0};
	Model_Conv8_Output c8={0};
	Model_Output result_output={0};
	float * output;
	
	//��ʼ����
	ModelPredict_Part1(input);
	
	ModelPredict_Part2();
	
	ModelPredict_Part3();
	
	residual_add();
	
	ModelPredict_Part4();
	
	//Flash�ж�ȡc5����
	read_flash_array((uint8_t*)c5, sizeof(c5));
	
	//��7����--����10��4��4�������14��3��3,����Ϊ1
	CONV2D(c5,c6,Model_Conv7_W,Model_Conv7_B,1);
	BATCH_NORMALIZATION(c6,Model_BN9);
	ACTIVATION(c6);
	
	//��8����--����14��4��4�������14��3��3,����Ϊ1
	CONV2D(c6,c7,Model_Conv8_W,Model_Conv8_B,1);
	BATCH_NORMALIZATION(c7,Model_BN10);
	ACTIVATION(c7);
	
	//ȫ��ƽ��ֵ�ػ�
	GLOBALAVERAGEPOOLING(c7,mgp);
	
	//��9����--����16��1��1   �����SortNum ��1��1
	CONV2D(mgp,c8,Model_Conv9_W,Model_Conv9_B,1);
	wdog_feed();				//ι��
	
	//����һ��3ά����ת��Ϊ1ά���飬�����СΪSortNum
	for(int i=0;i<SortNum;i++)
		result_output[i]=c8[i][0][0];
	
	//������������softmax�ع�
	output=result_output;
	
	Model_SoftmaxOut(output,SortNum);	
	
	wdog_feed(); 				//ι��
	
	//���������������
	return output;
}
