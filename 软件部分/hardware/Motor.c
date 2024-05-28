#include "stm32f10x.h"                  // Device header
#include "PWM.h"

void Motor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	PWM_Init();
}

void left_z()
{
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
}

void left_f()
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	GPIO_SetBits(GPIOA,GPIO_Pin_5);
}

void right_z()
{
	GPIO_SetBits(GPIOB,GPIO_Pin_14);
	GPIO_ResetBits(GPIOB,GPIO_Pin_15);
}

void right_f()
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_14);
	GPIO_SetBits(GPIOB,GPIO_Pin_15);
}

void pwxianfu(int max,int*pw)
{
	if(*pw>max)*pw=max;
	if(*pw<-max)*pw=-max;
}

void SETPWM_l(int pw)
{
	if(pw>0)
	{
		left_z();
		PWM_Setcompare1(7200-pw);
	}
	else{
		left_f();
		PWM_Setcompare1(7200-(-pw));
	}
}

void SETPWM_r(int pw)
{
	if(pw>0)
	{
		right_z();
		PWM_Setcompare4(pw);
	}
	else{
		right_f();
		PWM_Setcompare4(-pw);
	}
}

void Motor_off(void)
{
	SETPWM_l(0);
	SETPWM_r(0);
}
