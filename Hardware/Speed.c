#include "stm32f10x.h"                  // Device header
#include "pwm.h"
#include "pid.h"
#include "lunzi.h"
#include "Encoder.h"
//int16_t Speed[5]={3000,4000,5000,6000,7000};
//extern float pwm1,pwm2;
//void Set_speed(int16_t mode)
//{
//	switch(mode)
//	{
//		case 1:pwm1=pwm2=Speed[0];
//		case 2:pwm1=pwm2=Speed[1];
//		case 3:pwm1=pwm2=Speed[2];
//		case 4:pwm1=pwm2=Speed[3];
//		case 5:pwm1=pwm2=Speed[4];
//	}	
//}