#include "stm32f10x.h"                  // Device header
void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2);
}
void LED1_on(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
}
void LED1_off(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
}
void LED1_turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_1)==1)
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	}
	else
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_1);
	}
}
void LED2_turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_2)==1)
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
	}
	else
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_2);
	}
}
void LED2_on(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);
}
void LED2_off(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_2);
}
