#include "stm32f10x.h"                  // Device header

void AD_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_28Cycles5);
	
	ADC_InitTypeDef ADC_InitStucture;
	ADC_InitStucture.ADC_ContinuousConvMode=ENABLE;
	ADC_InitStucture.ADC_DataAlign=ADC_DataAlign_Right;
	ADC_InitStucture.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;
	ADC_InitStucture.ADC_Mode=ADC_Mode_Independent;
	ADC_InitStucture.ADC_NbrOfChannel=1;
	ADC_InitStucture.ADC_ScanConvMode=DISABLE;
	ADC_Init(ADC1,&ADC_InitStucture);
	
	ADC_AnalogWatchdogCmd(ADC1,ADC_AnalogWatchdog_SingleRegOrInjecEnable);
	ADC_AnalogWatchdogThresholdsConfig(ADC1,0XFFF,0X76C);
	ADC_AnalogWatchdogSingleChannelConfig(ADC1,ADC_Channel_0);
	
	NVIC_InitTypeDef NVIC_InitStucture;
	NVIC_InitStucture.NVIC_IRQChannel=ADC1_2_IRQn;
	NVIC_InitStucture.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStucture.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_InitStucture.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStucture);
	
	ADC_Cmd(ADC1,ENABLE);
	
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1)==SET);
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1)==SET);
	
	ADC_ITConfig(ADC1,ADC_IT_AWD,ENABLE);
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}

uint16_t AD_Read(void)
{
	return ADC_GetConversionValue(ADC1);
}
