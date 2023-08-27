#include "stm32f10x.h"                  // Device header

void bluetooth_init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);//使能GPIOA的时钟	
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;//IO管脚模式配置为浮空输入，这样就能获取传感器传回来的数字信号(高低电平)
	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_14;
	  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	  GPIO_Init(GPIOE,&GPIO_InitStructure);//PA6,PA7管脚的初始化  
}