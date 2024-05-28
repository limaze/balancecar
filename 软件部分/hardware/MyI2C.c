#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void MyI2C_W_SCL(uint8_t Bitvalue)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_10,(BitAction)Bitvalue);
	Delay_us(10);
}

void MyI2C_W_SDA(uint8_t Bitvalue)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_11,(BitAction)Bitvalue);
	Delay_us(10);
}

uint8_t MyI2C_R_SDA(void)
{
	uint8_t Bitvalue;
	Bitvalue=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
	Delay_us(10);
	return Bitvalue;
}

void MyI2C_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_10|GPIO_Pin_11);
}

void MyI2C_start(void)
{
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(0);
}

void MyI2C_stop(void)
{
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(1);
}

void MyI2C_sentbyte(uint8_t byte)
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
		MyI2C_W_SDA(byte&(0x80>>i));
		MyI2C_W_SCL(1);
		MyI2C_W_SCL(0);
	}
}

uint8_t MyI2C_receivebyte(void)
{
	uint8_t i;
	uint8_t byte=0x00;
	for(i=0;i<8;i++)
	{
		MyI2C_W_SDA(1);
		MyI2C_W_SCL(1);
		if(MyI2C_R_SDA()==1){byte|=(0x80>>i);}
		MyI2C_W_SCL(0);
	}
	return byte;
}

void MyI2C_sendACK(uint8_t ackbit)
{
	MyI2C_W_SDA(ackbit);
	MyI2C_W_SCL(1);
	MyI2C_W_SCL(0);
}

uint8_t MyI2C_receiveACK(void)
{
	uint8_t ackbit;
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);
	ackbit=MyI2C_R_SDA();
	MyI2C_W_SCL(0);
	return ackbit;
}
