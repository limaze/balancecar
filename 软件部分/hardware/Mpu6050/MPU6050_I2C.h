#ifndef __MPU6050_I2C_H
#define __MPU6050_I2C_H
#include "sys.h"
#include "delay.h"

//如果移植程序时只要改一下地方就行了
#define MPU6050_IIC_GPIO                   GPIOB
#define MPU6050_IIC_SCL_Pin                GPIO_Pin_10	         //PB10
#define MPU6050_IIC_SDA_Pin                GPIO_Pin_11	         //PB11

#define	MPU6050_IIC_SCL                    PBout(10)
#define	MPU6050_IIC_SDA                    PBout(11)  
#define	MPU6050_IIC_SDA_IN                 PBin(11)              //读数据端口
#define MPU6050_IIC_delay_4us()            delay_us(4)


//MPU6050_IIC所有操作函数
void MPU6050_IIC_IO_Init(void);               //初始化MPU6050_IIC的IO口	
void MPU6050_IIC_SDA_IO_OUT(void);    
void MPU6050_IIC_SDA_IO_IN(void);
void MPU6050_IIC_Start(void);				          //发送MPU6050_IIC开始信号
void MPU6050_IIC_Stop(void);	  			        //发送MPU6050_IIC停止信号
void MPU6050_IIC_Send_Byte(u8 txd);			      //MPU6050_IIC发送一个字节
u8   MPU6050_IIC_Read_Byte(u8 ack);           //MPU6050_IIC读取一个字节
u8   MPU6050_IIC_Read_Ack(void); 				      //MPU6050_IIC等待ACK信号
void MPU6050_IIC_Send_Ack(u8 ack);					  //MPU6050_IIC发送ACK信号

#endif
