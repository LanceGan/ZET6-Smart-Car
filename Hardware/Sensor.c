#include "stm32f10x.h"                  // Device header
#include "pid.h"
#include "pwm.h"
#include "lunzi.h"
int sensor[6]={0,0,0,0,0,0};
int bias;
float target;
int stopconfig=0;
int is_turnleft=0,is_turnright=0,is_turnround=0,sznum=0;
void Sensor_init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能GPIOA的时钟		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);//使能GPIOA的时钟	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//使能复用功能的时钟
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;//IO管脚模式配置为浮空输入，这样就能获取传感器传回来的数字信号(高低电平)
	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_12;
	  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	  GPIO_Init(GPIOB,&GPIO_InitStructure);//PA6,PA7管脚的初始化  
	
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;//IO管脚模式配置为浮空输入，这样就能获取传感器传回来的数字信号(高低电平)
	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
	  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	  GPIO_Init(GPIOD,&GPIO_InitStructure);//PA6,PA7管脚的初始化  
}

void read_sensor(void)
{
		sensor[0]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5);//最左的传感器
		sensor[1]=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0);
		sensor[2]=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1);//中间靠左
		sensor[3]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13);//中间靠右
		sensor[4]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14);
		sensor[5]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12);//最右的传感器
	
	
		if(sensor[0]==0&&sensor[1]==0&&sensor[2]==0&&sensor[3]==0&&sensor[4]==0&sensor[5]==0)
			{	/*红线在中间*/	
				Set_speed(5);bias=0;target=4500;
			}
				
				else if(sensor[0]==1&&sensor[1]==1&&sensor[2]==1&&sensor[3]==1&&sensor[4]==1&&sensor[5]==1)
			{/*识别到十字路口或T字路口*/
				is_turnround=1;Set_speed(5);bias=0;target=4500;
			}	
				
				else if((sensor[0]==0&&sensor[1]==0)&&(sensor[2]==1)&&(sensor[3]==0&&sensor[4]==0&&sensor[5]==0))
			{/*小车位置有点偏右*/
				Set_speed(5);bias=-1;target=3700;
			}
				
				else if((sensor[0]==0&&sensor[1]==0&&sensor[2]==0)&&(sensor[3]==1)&&(sensor[4]==0&&sensor[5]==0))
			{/*小车位置有点偏左*/
				Set_speed(4);bias=1;target=3700;
			}
			
//			else if (sensor[2]==1&&sensor[3]==1&&(sensor[0]==0||sensor[1]==0||sensor[4]==0||sensor[5]==0))
//			{}
				
			else if(((sensor[0]==0&&sensor[2]==0)&&sensor[1]==1&&(sensor[3]==0&&sensor[4]==0&&sensor[5]==0))||
					(sensor[0]==0&&(sensor[2]==1&&sensor[1]==1)&&(sensor[3]==0&&sensor[4]==0&&sensor[5]==0)))
			{/*小车位置偏右*/
				Set_speed(4);bias=-2;target=3700;
			}
				
			else if(((sensor[0]==0&&sensor[1]==0&&sensor[2]==0)&&sensor[4]==1&&(sensor[3]==0&&sensor[5]==0))||
					((sensor[0]==0&&sensor[1]==0&&sensor[2]==0)&&(sensor[3]==1&&sensor[4]==1)&&sensor[5]==0))
			{/*小车位置偏左*/
				Set_speed(4);bias=2;target=3700;
			}
			
			else if(((sensor[1]==0&&sensor[2]==0)&&sensor[0]==1&&(sensor[3]==0&&sensor[4]==0&&sensor[5]==0)))
					
			{/*小车位置很偏右*/
				Set_speed(3);bias=-3;target=3700;
			}
				
			else if(((sensor[0]==0&&sensor[1]==0&&sensor[2]==0)&&sensor[5]==1&&(sensor[3]==0&&sensor[4]==0)))
					
			{/*小车位置很偏左*/
				Set_speed(3);bias=3;target=3700;
			}
			
//			else if(((sensor[0]==0&&sensor[1]==0&&sensor[2]==0)&&sensor[4]==1&&(sensor[3]==0&&sensor[5]==0))||
//					((sensor[0]==0&&sensor[1]==0&&sensor[2]==0)&&(sensor[3]==1&&sensor[4]==1)&&sensor[5]==0))
//			{/*小车位置偏左*/
//				Set_speed(4);bias=2;target=1300;
//			}
			
			else if(sensor[5]==1&&sensor[4]==1&&sensor[3]==1&&sensor[0]==0&&sensor[1]==0)//右转
			{
				Set_speed(4);bias=0;target=4500;is_turnright=1;
			}
			
			else if(sensor[0]==1&&sensor[1]==1&&sensor[2]==1&&sensor[5]==0&&sensor[4]==0)
			{
				Set_speed(4);bias=0;target=4500;is_turnleft=1;
			}
			
			else if(sensor[2]==1&&sensor[3]==1&&sensor[0]==0&&sensor[5]==0)
			{
				stopconfig++;
			}
			
}

