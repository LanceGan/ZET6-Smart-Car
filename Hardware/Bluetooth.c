#include "stm32f10x.h"                  // Device header

void bluetooth_init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);//ʹ��GPIOA��ʱ��	
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;//IO�ܽ�ģʽ����Ϊ�������룬�������ܻ�ȡ�������������������ź�(�ߵ͵�ƽ)
	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_14;
	  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	  GPIO_Init(GPIOE,&GPIO_InitStructure);//PA6,PA7�ܽŵĳ�ʼ��  
}