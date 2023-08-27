#include "stm32f10x.h"                  // Device header
#include "Delay.h"
void buzzer_init()
{
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//ʹ��GPIOA��ʱ��		
	  GPIO_InitStructure.GPIO_Mode= GPIO_Mode_Out_PP;//IO�ܽ�ģʽ����Ϊ�������룬�������ܻ�ȡ�������������������ź�(�ߵ͵�ƽ)
	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
	  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	  GPIO_Init(GPIOB,&GPIO_InitStructure);//PA6,PA7�ܽŵĳ�ʼ��  
}

void buzzer_on(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_8);
	Delay_ms(500);
	GPIO_SetBits(GPIOB,GPIO_Pin_8);
}