#include "lunzi.h"
#include "stm32f10x.h"
#include "pwm.h"
#include "sensor.h"
#include "Delay.h"
#include "pid.h"
extern int sensor[6];
extern int is_turnleft,is_turnright,is_turnround;
int noread=0;
extern float yaw;

void lunzi_Init(void)//����Ӧ��IO�ڽ��г�ʼ��,PA0-3
{
	  GPIO_InitTypeDef GPIO_InitStructure;
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//ʹ��GPIOA��ʱ��
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��GPIOA��ʱ��
	
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//���ģʽΪ�����������ƽ�ɸ߿ɵ�
	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;//PA0-3�ܽ�IO��
	  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//�ܽŴ����ٶ�
	  GPIO_Init(GPIOB,&GPIO_InitStructure);
	
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//���ģʽΪ�����������ƽ�ɸ߿ɵ�
	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_11;//PA0-3�ܽ�IO��
	  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//�ܽŴ����ٶ�
	  GPIO_Init(GPIOA,&GPIO_InitStructure);
}

void stop(void)//С�����������ת����ΪԽ���յ���ʱ������ֹͣ���������С������Ϊ����ͣ�����������Զ�ʱ��ķ�ת���ܵ������ԣ��Ӷ�ʹС��Ѹ��ͣ����
{
	  /*�ĸ��ܽ����ò�ͬ�ĵ�ƽ(1Ϊ�ߵ�ƽ0Ϊ�͵�ƽ)����ΪTB6612���߼����룬���Կ��Ƶ��ת��״̬�� */
	  /*����ȷ����ĸ��ܽ�IO�ֱ����ó�0 1 0 1�������ת����ô���������ó�1 0 1 0ʱ�������ת*/
		GPIO_ResetBits(GPIOB,GPIO_Pin_0);//PA0�͵�ƽ   0
		GPIO_ResetBits(GPIOB,GPIO_Pin_1);//PA1�ߵ�ƽ	     1
		GPIO_ResetBits(GPIOA,GPIO_Pin_10);//PA2�͵�ƽ	   0
		GPIO_ResetBits(GPIOA,GPIO_Pin_11);//PA3�ߵ�ƽ     1
}
void forward(void)//С�����������ת
{
	  GPIO_SetBits(GPIOB,GPIO_Pin_0);//PA0�ߵ�ƽ	     1
		GPIO_ResetBits(GPIOB,GPIO_Pin_1);//PA1�͵�ƽ   0
		GPIO_SetBits(GPIOA,GPIO_Pin_10);//PA2�ߵ�ƽ	     1
		GPIO_ResetBits(GPIOA,GPIO_Pin_11);//PA3�͵�ƽ   0
}

void back(void)//С�����������ת
{
	  GPIO_SetBits(GPIOB,GPIO_Pin_1);//PA0�ߵ�ƽ	     1
		GPIO_ResetBits(GPIOB,GPIO_Pin_0);//PA1�͵�ƽ   0
		GPIO_SetBits(GPIOA,GPIO_Pin_11);//PA2�ߵ�ƽ	     1
		GPIO_ResetBits(GPIOA,GPIO_Pin_10);//PA3�͵�ƽ   0
}

void leftback(void)//���ַ�ת
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);//PA0�ߵ�ƽ	     0
	GPIO_SetBits(GPIOB,GPIO_Pin_1);//PA1�͵�ƽ   1
}

void leftforward(void)//������ת
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_1);//PA0�ߵ�ƽ	     0
	GPIO_SetBits(GPIOB,GPIO_Pin_0);//PA1�͵�ƽ   1
}

void rightback(void)//���ַ�ת
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_10);//PA0�ߵ�ƽ	     0
	GPIO_SetBits(GPIOA,GPIO_Pin_11);//PA1�͵�ƽ   1
}

void rightforward(void)//������ת
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_11);//PA0�ߵ�ƽ	     0
	GPIO_SetBits(GPIOA,GPIO_Pin_10);//PA1�͵�ƽ   1
}

//void turnleft(void)
//{
//	Delay_ms(500);
//	while(sensor[2]==0)
//	{
//		leftback();
//	}
//	is_turnleft=0;
//	forward();
//}

//void turnright(void)
//{
//	Delay_ms(500);
//	while(sensor[3]==0)
//	{
//		rightback();
//	}
//	is_turnright=0;
//	forward();
//}

//void turnround(void)
//{
//	leftback();
//	noread=1;
//	Delay_ms(500);
//	noread=0;
//	while(sensor[2]==0)leftback();
//	forward();
//	is_turnround=0;
//}

//void left(void)
//{
//	do
//	{
//	leftback();
//	rightforward();
//	TIM_SetCompare3(TIM2,4000);//�������
//	TIM_SetCompare4(TIM2,4000);//�������
//	}
//	while((yaw/10.0f)<100);
//	stop();
//	is_turnleft=0;
//}

//void right(void)
//{
//	do
//	{
//	leftforward();
//	rightback();
//	TIM_SetCompare3(TIM2,);//�������
//	TIM_SetCompare4(TIM2,4000);//�������
//	}
//	while((yaw/10.0f)>-100);
//	stop();
//	is_turnright=0;
//}






