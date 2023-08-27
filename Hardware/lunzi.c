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

void lunzi_Init(void)//对相应的IO口进行初始化,PA0-3
{
	  GPIO_InitTypeDef GPIO_InitStructure;
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能GPIOA的时钟
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能GPIOA的时钟
	
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//输出模式为推挽输出，电平可高可低
	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;//PA0-3管脚IO口
	  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//管脚传输速度
	  GPIO_Init(GPIOB,&GPIO_InitStructure);
	
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//输出模式为推挽输出，电平可高可低
	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_11;//PA0-3管脚IO口
	  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//管脚传输速度
	  GPIO_Init(GPIOA,&GPIO_InitStructure);
}

void stop(void)//小车两个电机反转，因为越过终点线时，单纯停止电机工作，小车会因为惯性停不下来，所以短时间的反转，能抵消惯性，从而使小车迅速停下来
{
	  /*四个管脚设置不同的电平(1为高电平0为低电平)，作为TB6612的逻辑输入，用以控制电机转动状态。 */
	  /*打个比方，四个管脚IO分别设置成0 1 0 1，电机反转，那么反过来设置成1 0 1 0时，电机正转*/
		GPIO_ResetBits(GPIOB,GPIO_Pin_0);//PA0低电平   0
		GPIO_ResetBits(GPIOB,GPIO_Pin_1);//PA1高电平	     1
		GPIO_ResetBits(GPIOA,GPIO_Pin_10);//PA2低电平	   0
		GPIO_ResetBits(GPIOA,GPIO_Pin_11);//PA3高电平     1
}
void forward(void)//小车两个电机正转
{
	  GPIO_SetBits(GPIOB,GPIO_Pin_0);//PA0高电平	     1
		GPIO_ResetBits(GPIOB,GPIO_Pin_1);//PA1低电平   0
		GPIO_SetBits(GPIOA,GPIO_Pin_10);//PA2高电平	     1
		GPIO_ResetBits(GPIOA,GPIO_Pin_11);//PA3低电平   0
}

void back(void)//小车两个电机反转
{
	  GPIO_SetBits(GPIOB,GPIO_Pin_1);//PA0高电平	     1
		GPIO_ResetBits(GPIOB,GPIO_Pin_0);//PA1低电平   0
		GPIO_SetBits(GPIOA,GPIO_Pin_11);//PA2高电平	     1
		GPIO_ResetBits(GPIOA,GPIO_Pin_10);//PA3低电平   0
}

void leftback(void)//左轮反转
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);//PA0高电平	     0
	GPIO_SetBits(GPIOB,GPIO_Pin_1);//PA1低电平   1
}

void leftforward(void)//左轮正转
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_1);//PA0高电平	     0
	GPIO_SetBits(GPIOB,GPIO_Pin_0);//PA1低电平   1
}

void rightback(void)//右轮反转
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_10);//PA0高电平	     0
	GPIO_SetBits(GPIOA,GPIO_Pin_11);//PA1低电平   1
}

void rightforward(void)//右轮正转
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_11);//PA0高电平	     0
	GPIO_SetBits(GPIOA,GPIO_Pin_10);//PA1低电平   1
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
//	TIM_SetCompare3(TIM2,4000);//电机控制
//	TIM_SetCompare4(TIM2,4000);//电机控制
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
//	TIM_SetCompare3(TIM2,);//电机控制
//	TIM_SetCompare4(TIM2,4000);//电机控制
//	}
//	while((yaw/10.0f)>-100);
//	stop();
//	is_turnright=0;
//}






