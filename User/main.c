#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Encoder.h"
#include "pwm.h"
#include "lunzi.h"
#include "Serial.h"
#include "PID.h"
#include "Sensor.h"
#include "buzzer.h"
#include "MPU6050.h"
#include "math.h"
#include "bluetooth.h"

#define GYRO_SENSITIVITY 131.0f 
#define ACC_SENSITIVITY 16384.0f 
#define COMPLEMENTARY_FILTER_ALPHA 0.98f

extern int stopconfig;
int16_t lSpeed,rSpeed;
float distance,tar_dis;
uint8_t RxData;
float PWM1,PWM2;
extern float pwm1,pwm2,Pwm;
extern int is_turnleft,is_turnright,is_turnround;
extern int noread;
extern float target;
extern int bias;
extern int OUTPUT1,OUTPUT2;
extern uint8_t Serial_RxPacket[4];
int16_t AX, AY, AZ, GX, GY, GZ;
int tagf=0,tagr=0;
float yaw=0.0f;
int main(void)
{
	OLED_Init();
	Encoder_Init();
	Encoder_Init2();
	lunzi_Init();
//	OLED_ShowString(1, 1, "Speed:");
	buzzer_init();
	TIM3_Init_Init(99,7199);
	TIM2_PWM_Init(7199,0);
	Serial_Init();
//	forward();
	Sensor_init();
	MPU6050_Init();
	bluetooth_init();
//	target=2000;
//	bias=0;
//	Set_speed(5);
//	Delay_s(1);
//	is_turnleft=1;
	int blue=0;
	
	while (1)
	{
//			OLED_ShowSignedNum(1, 1, yaw/10.0f, 5);	
//			Serial_Printf("%d,%d\n",lSpeed,rSpeed);
//			Serial_SendNumber((yaw/10.0f),3);
//			Serial_SendString("  ");
//			Serial_Printf("%f\n",(yaw/10.0f));
//		tar_dis=100;
//		float pwm=pid3(distance,tar_dis);
//		TIM_SetCompare3(TIM2,7200);//电机控制
//		TIM_SetCompare4(TIM2,7200);//电机控制
//		forward();
//		Serial_Printf("%d,%d\n",lSpeed,rSpeed);
		
		blue=bluetooth_key;
		
		if(blue)
		{
			buzzer_on();
//			Serial_SendByte(0xAB);
//			Serial_SendString("ok");
//			Serial_SendByte(0xCD);
			OLED_ShowString(1, 1, "ok");
		}
		else 
		{
//			Serial_SendString("no");
			OLED_ShowString(1, 1, "no");
		}
		
		OLED_ShowHexNum(2,1,Serial_RxPacket[0],2);
		OLED_ShowHexNum(2,5,Serial_RxPacket[1],2);
		OLED_ShowHexNum(3,1,Serial_RxPacket[2],2);
		OLED_ShowHexNum(4,5,Serial_RxPacket[3],2);
		
		if(Serial_RxPacket[0]&&blue)
		{
		
		TIM_SetCompare3(TIM2,7200);//电机控制
		TIM_SetCompare4(TIM2,7200);//电机控制
		Delay_s(1);
		}
		else stop();
		
//		if(!stopconfig)
//				{
//					if(is_turnleft)
//					{
//						if(tagf==0)
//						{
//							Delay_ms(1);
//							tagf=1;
//						}
//			//				OLED_ShowString(2, 1, "left");
//						leftback();
//						noread=1;
//					}
//					else if(is_turnright)
//					{
//						if(tagr==0)
//						{
//							Delay_ms(1);
//							tagr=1;
//						}
//			//				OLED_ShowString(2, 1, "right");
//						rightback();
//						noread=1;
//					}
//					else if(is_turnround)
//					{
//						leftback();
//						rightforward();
//						noread=1;
//					}
//					else 
//					{
//			//				OLED_ShowString(2, 1, "track");
//						forward();
//					}
//					
//				}
//				else if(stopconfig)
//				{
//					stop();
//					stopconfig=0;
//				}
	}
}


void TIM4_IRQHandler(void)   //TIM3中断服务函数
{
	static int16_t count=0;
	
	if(TIM4->SR&0X0001)//定时器每10ms定时中断一次
	{ 
		
		count++;
		MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);
		if(is_turnleft||is_turnright||is_turnround)
		{
		yaw += GZ / GYRO_SENSITIVITY;
		yaw-=0.30f;
		}
		else yaw=0;
		
			if(!noread)read_sensor();

			if(is_turnleft)
			{
				Su_forturn();
				if((yaw/10.0f)>70)
				{
					is_turnleft=0;
					noread=0;
					tagf=0;
					forward();
					
				}
			}
			else if(is_turnright)
			{
				Su_forturn();
				if((yaw/10.0f)<-70)
				{
					is_turnright=0;
					noread=0;
					tagr=0;
					forward();
				}
			}
			else if(is_turnround)
			{
				Su_forturn();
				if((yaw/10.0f)>170)
				{
					is_turnround=0;
					noread=0;
					forward();
				}
			}
			else 
			{
			Su_fortrack();
			
			}
		  TIM4->SR&=~(1<<0);//清除定时器三的计时标志，执行完TIM3中断服务函数里的操作后定时器会重新计时
			if(count==100)
			{
				count=0;
				lSpeed=Encoder_Get();
				rSpeed=Encoder_Get2();
				distance+=((lSpeed+rSpeed)*2*100/(2*2*11*35*2))/100.0;
			}
	}
}
