#include "stc51reg.h"
#include <intrins.h>
#include "ADC.h"


//ADC功能
void initialADC();                               //初始化ADC
void ADC_Power_On();						 	 //打开ADC电源控制，启动AD转换功能之前要确保ADC电源已打开
void Set_ASF();								 //P1.0-P1.4口作为模拟功能AD使用
void Set_ADC_Channel(unsigned char channelADC);						 //模拟AD转换通道选择

//接口
unsigned char getADResult(unsigned char channel);							 //获取AD转换结果

//miscellaneous
void delay(unsigned int t);						 //延迟一段时间

void initialADC()
{
	//AUXR=0x40;
	P1M1|=0x1F;
	P1M0|=0x00;
	Set_ASF();
	ADC_Power_On();
}

void ADC_Power_On()
{
	ADC_CONTR=ADC_CONTR|0X80;					//ADC_Power=1,打开ADC电源控制
	delay(2);
}

void Set_ASF()
{
	P1ASF=P1ASF|0X1F;							//P1.0-P1.4口作为模拟功能AD使用
}

void Set_ADC_Channel(unsigned char channelADC)
{
	switch(channelADC)
	{
		case 0:
			ADC_CONTR=ADC_Power_On_Speed_Channel1_0;
			delay(5);
			break;
		case 1:
			ADC_CONTR=ADC_Power_On_Speed_Channel1_1;
			delay(5);
			break;
		case 2:
			ADC_CONTR=ADC_Power_On_Speed_Channel1_2;
			delay(5);
			break;
		case 3:
			ADC_CONTR=ADC_Power_On_Speed_Channel1_3;
			delay(5);
			break;
		case 4:
			ADC_CONTR=ADC_Power_On_Speed_Channel1_4;
			delay(5);
			break;
	}
}

unsigned char getADResult(unsigned char channel)
{  
	unsigned char ADC_Channel_Result;				 //AD转换结果寄存	

	Set_ADC_Channel(channel);	

	ADC_RES=0X00;									//清零AD转换结果寄存器	
	ADC_CONTR=ADC_CONTR|0X08;  				//启动AD转换
	_nop_();						    				//在对ADC_CONTR控制寄存器进行写操作后，要执行4个CPU时钟的延迟，才能保证被设置进ADC_CONTR控制寄存器
	_nop_();
	_nop_();
	_nop_();
	while((ADC_CONTR&0X10)==0);				//AD转换尚未完成，等待
	ADC_CONTR=ADC_CONTR&0XE7;  				//清0 ADC_FLAG,ADC_START位，停止AD转换	
	ADC_Channel_Result=ADC_RES;				//将8位AD转换结果进行保存

	return ADC_Channel_Result;
}

void delay(unsigned int t)						//延迟函数
{
     unsigned int j=0;
     unsigned int g=0;
	  unsigned int k=0;
     for(j=0;j<t;j++)
     {
      for(g=0;g<20;g++)
      {
		for(k=0;k<20;k++)
      	{
				_nop_();
      	}
      }
     }   
}
