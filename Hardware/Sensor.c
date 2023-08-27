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
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//ʹ��GPIOA��ʱ��		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);//ʹ��GPIOA��ʱ��	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//ʹ�ܸ��ù��ܵ�ʱ��
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;//IO�ܽ�ģʽ����Ϊ�������룬�������ܻ�ȡ�������������������ź�(�ߵ͵�ƽ)
	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_12;
	  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	  GPIO_Init(GPIOB,&GPIO_InitStructure);//PA6,PA7�ܽŵĳ�ʼ��  
	
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;//IO�ܽ�ģʽ����Ϊ�������룬�������ܻ�ȡ�������������������ź�(�ߵ͵�ƽ)
	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
	  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	  GPIO_Init(GPIOD,&GPIO_InitStructure);//PA6,PA7�ܽŵĳ�ʼ��  
}

void read_sensor(void)
{
		sensor[0]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5);//����Ĵ�����
		sensor[1]=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0);
		sensor[2]=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1);//�м俿��
		sensor[3]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13);//�м俿��
		sensor[4]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14);
		sensor[5]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12);//���ҵĴ�����
	
	
		if(sensor[0]==0&&sensor[1]==0&&sensor[2]==0&&sensor[3]==0&&sensor[4]==0&sensor[5]==0)
			{	/*�������м�*/	
				Set_speed(5);bias=0;target=4500;
			}
				
				else if(sensor[0]==1&&sensor[1]==1&&sensor[2]==1&&sensor[3]==1&&sensor[4]==1&&sensor[5]==1)
			{/*ʶ��ʮ��·�ڻ�T��·��*/
				is_turnround=1;Set_speed(5);bias=0;target=4500;
			}	
				
				else if((sensor[0]==0&&sensor[1]==0)&&(sensor[2]==1)&&(sensor[3]==0&&sensor[4]==0&&sensor[5]==0))
			{/*С��λ���е�ƫ��*/
				Set_speed(5);bias=-1;target=3700;
			}
				
				else if((sensor[0]==0&&sensor[1]==0&&sensor[2]==0)&&(sensor[3]==1)&&(sensor[4]==0&&sensor[5]==0))
			{/*С��λ���е�ƫ��*/
				Set_speed(4);bias=1;target=3700;
			}
			
//			else if (sensor[2]==1&&sensor[3]==1&&(sensor[0]==0||sensor[1]==0||sensor[4]==0||sensor[5]==0))
//			{}
				
			else if(((sensor[0]==0&&sensor[2]==0)&&sensor[1]==1&&(sensor[3]==0&&sensor[4]==0&&sensor[5]==0))||
					(sensor[0]==0&&(sensor[2]==1&&sensor[1]==1)&&(sensor[3]==0&&sensor[4]==0&&sensor[5]==0)))
			{/*С��λ��ƫ��*/
				Set_speed(4);bias=-2;target=3700;
			}
				
			else if(((sensor[0]==0&&sensor[1]==0&&sensor[2]==0)&&sensor[4]==1&&(sensor[3]==0&&sensor[5]==0))||
					((sensor[0]==0&&sensor[1]==0&&sensor[2]==0)&&(sensor[3]==1&&sensor[4]==1)&&sensor[5]==0))
			{/*С��λ��ƫ��*/
				Set_speed(4);bias=2;target=3700;
			}
			
			else if(((sensor[1]==0&&sensor[2]==0)&&sensor[0]==1&&(sensor[3]==0&&sensor[4]==0&&sensor[5]==0)))
					
			{/*С��λ�ú�ƫ��*/
				Set_speed(3);bias=-3;target=3700;
			}
				
			else if(((sensor[0]==0&&sensor[1]==0&&sensor[2]==0)&&sensor[5]==1&&(sensor[3]==0&&sensor[4]==0)))
					
			{/*С��λ�ú�ƫ��*/
				Set_speed(3);bias=3;target=3700;
			}
			
//			else if(((sensor[0]==0&&sensor[1]==0&&sensor[2]==0)&&sensor[4]==1&&(sensor[3]==0&&sensor[5]==0))||
//					((sensor[0]==0&&sensor[1]==0&&sensor[2]==0)&&(sensor[3]==1&&sensor[4]==1)&&sensor[5]==0))
//			{/*С��λ��ƫ��*/
//				Set_speed(4);bias=2;target=1300;
//			}
			
			else if(sensor[5]==1&&sensor[4]==1&&sensor[3]==1&&sensor[0]==0&&sensor[1]==0)//��ת
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

