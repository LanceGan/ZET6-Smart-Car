#include "stm32f10x.h"                  // Device header
#include "pwm.h"
#include "lunzi.h"
#include "Sensor.h"
//float Err=0,last_err=0,next_err=0,pwm=0,add=0,p=0.001,i=0.005,d=0.5;//效果非常好的一套参数
extern int is_turnleft,is_turnright,is_turnround;
float Err1=0,last_err1=0,next_err1=0,pwm1=0,add1=0,p1=0.5,i1=0.1,d1=0.2;//左轮基础速度pid参数
float Err2=0,last_err2=0,next_err2=0,pwm2=0,add2=0,p2=0.5,i2=0.1,d2=0.2;//右轮基础速度pid参数
float Bias=0,Pwm=0,last_bias=0,Intergral_bias=0,kp=2000,ki=30,kd=20;//指定距离行驶pid
float Bias2=0,Pwm2=0,last_bias2=0,Intergral_bias2=0,kp2=20,ki2=3,kd2=2;

int OUTPUT1,OUTPUT2;
extern float target;
extern int16_t lSpeed,rSpeed;
extern int bias;
extern float yaw;

float Speed[5]={3000,4000,5000,6000,7000};
int16_t aybs(int a)
{
	int temp;
	if(a<0)temp=-a;
	else temp=a;
	return temp;
}

void Xianfu(void)
{
	if(pwm1>7200)pwm1=7200;
	if(pwm1<0)pwm1=0;
	if(pwm2>7200)pwm2=7200;
	if(pwm2<0)pwm2=0;
}

float pid1(int16_t speed,float tar)//左轮基础速度PID,增量式PID
{
	speed=aybs(speed);
	Err1=tar-speed;
	add1=p1*(Err1-last_err1)+i1*(Err1)+d1*(Err1+next_err1-2*last_err1);
	pwm1+=add1;
	Xianfu();
	next_err1=last_err1;
	last_err1=Err1;
	return pwm1;
}


float pid2(int16_t speed,float tar)//右轮基础速度PID,增量式PID
{
	speed=aybs(speed);
	Err2=tar-speed;
	add2=p2*(Err2-last_err2)+i2*(Err2)+d2*(Err2+next_err2-2*last_err2);
	pwm2+=add2;
	Xianfu();
	next_err2=last_err2;
	last_err2=Err2;
	return pwm2;
}

float pid3(float dist,float tar)//位置式pid，用来指定小车走多少距离。
{
	Bias=tar-dist;
	Intergral_bias+=Bias; //偏差累计
	
	if(Intergral_bias>200)Intergral_bias2=200;//积分限幅
	if(Intergral_bias<-200)Intergral_bias2=-200;	
	
	Pwm=kp*Bias+ki*Intergral_bias+kd*(Bias-last_bias);
	if(Pwm>7200)Pwm=7200;
	if(Pwm<0)Pwm=0;
	return Pwm;
}

float turn_pid(float yaw,float tar)//转向pid，实质上也是位置pid
{
	Bias2=tar-yaw;
	Intergral_bias2+=Bias2; //偏差累计
	if(Intergral_bias2>200)Intergral_bias2=200;//积分限幅
	if(Intergral_bias2<-200)Intergral_bias2=-200;	
	Pwm2=kp2*Bias2+ki2*Intergral_bias2+kd2*(Bias2-last_bias2);
	if(Pwm2>7200)Pwm2=7200;
	if(Pwm2<0)Pwm2=0;
	return Pwm2;
}

void Set_speed(int16_t mode)//设置初始速度
{	
		if(mode==1)pwm1=pwm2=3000;
		if(mode==2)pwm1=pwm2=4000;
		if(mode==3)pwm1=pwm2=5000;
		if(mode==4)pwm1=pwm2=6000;
		if(mode==5)pwm1=pwm2=7000;
}

void Su_fortrack(void)
{
//	if(is_turnleft)
//	{
//	OUTPUT1=turn_pid(yaw/10.0f,100);
//	OUTPUT2=turn_pid(yaw/10.0f,100);
//	leftback();
//	rightforward();
//	if((yaw/10.0f)>100)
//	{
//		is_turnleft=0;
//		forward();
//	}
//	}
//	else if(is_turnright)
//	{
//	OUTPUT1=turn_pid(yaw/10.0f,-100);
//	OUTPUT2=turn_pid(yaw/10.0f,-100);
//	leftforward();
//	rightback();
//	if((yaw/10.0f)<-100)
//	{
//		is_turnright=0;
//		forward();
//	}
//	}	
//	else 
//	{
	OUTPUT1=pid1(lSpeed,target)+bias*500;
	OUTPUT2=pid2(rSpeed,target)-bias*500;
//	}
	
	if(OUTPUT1>7200)OUTPUT1=7200;
	if(OUTPUT1<0)OUTPUT1=0;
	if(OUTPUT2>7200)OUTPUT2=7200;
	if(OUTPUT2<0)OUTPUT2=0;
	TIM_SetCompare3(TIM2,OUTPUT1);//电机控制
	TIM_SetCompare4(TIM2,OUTPUT2);//电机控制
}

void Su_forturn(void)
{
	OUTPUT1=OUTPUT2=turn_pid((yaw/10.0f),target);	
	TIM_SetCompare3(TIM2,OUTPUT1);//电机控制
	TIM_SetCompare4(TIM2,OUTPUT2);//电机控制
}







