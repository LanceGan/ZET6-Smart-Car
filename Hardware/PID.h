#ifndef _PID_H
#define _PID_H

int16_t aybs(int a);
void Xianfu(void);
float pid1(int16_t speed,float tar);
float pid2(int16_t speed,float tar);
void Set_speed(int16_t mode);
void Su_fortrack(void);
float pid3(float dist,float tar);//λ��ʽpid������ָ��С���߶��پ��롣
float turn_pid(float yaw,float tar);
void Su_forturn(void);

#endif