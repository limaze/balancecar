#include "stm32f10x.h"                  // Device header

void BUZZER_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_5);
}

void BUZZER_on(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_5);
}

void BUZZER_off(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_5);
}
