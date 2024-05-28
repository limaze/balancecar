#include "MPU6050_I2C.h"
 
void MPU6050_IIC_IO_Init(void)
{
  My_GPIO_Init(MPU6050_IIC_GPIO,MPU6050_IIC_SCL_Pin|MPU6050_IIC_SDA_Pin,GPIO_TW_OUT,GPIO_P_NO,GPIO_50MHz);//������� ���� 50m
 
	MPU6050_IIC_SCL=1;
	MPU6050_IIC_SDA=1;
}

void MPU6050_IIC_SDA_IO_OUT(void)
{
	My_GPIO_Init(MPU6050_IIC_GPIO,MPU6050_IIC_SDA_Pin,GPIO_TW_OUT,GPIO_P_NO,GPIO_50MHz);//������� ���� 50m
}

void MPU6050_IIC_SDA_IO_IN(void)
{
	My_GPIO_Init(MPU6050_IIC_GPIO,MPU6050_IIC_SDA_Pin,GPIO_FK_IN,GPIO_P_UP,GPIO_50MHz);//�������� ���� 50m
}
//����MPU6050_IIC��ʼ�ź�
void MPU6050_IIC_Start(void)
{
	  MPU6050_IIC_SDA_IO_OUT();
		MPU6050_IIC_SDA=1;	  	  
		MPU6050_IIC_SCL=1;
		MPU6050_IIC_delay_4us();
		MPU6050_IIC_SDA=0; 
		MPU6050_IIC_delay_4us();
		MPU6050_IIC_SCL=0; 
}	  
//����MPU6050_IICֹͣ�ź�
void MPU6050_IIC_Stop(void)
{
	  MPU6050_IIC_SDA_IO_OUT();
		MPU6050_IIC_SCL=0;
		MPU6050_IIC_SDA=0;   
		MPU6050_IIC_delay_4us();
		MPU6050_IIC_SCL=1; 
		MPU6050_IIC_delay_4us(); 
		MPU6050_IIC_SDA=1;   
		MPU6050_IIC_delay_4us();  					   	
	}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 MPU6050_IIC_Read_Ack(void)
{
		u8 ucErrTime=0;
	  MPU6050_IIC_SDA_IO_IN();
		MPU6050_IIC_SDA=1;
	  MPU6050_IIC_delay_4us();	   
		MPU6050_IIC_SCL=1;
	  MPU6050_IIC_delay_4us();	 
		while(MPU6050_IIC_SDA_IN)
		{
			ucErrTime++;
			if(ucErrTime>250)
			{
				MPU6050_IIC_Stop();
				return 1;
			}
		}
		MPU6050_IIC_SCL=0; 	   
		return 0;  
} 
//����ACKӦ��
void MPU6050_IIC_Send_Ack(u8 ack)
{
		MPU6050_IIC_SDA_IO_OUT();
		MPU6050_IIC_SCL=0;
		MPU6050_IIC_SDA=ack;
		MPU6050_IIC_delay_4us();
		MPU6050_IIC_SCL=1;
		MPU6050_IIC_delay_4us();
		MPU6050_IIC_SCL=0;
}				 				     
//MPU6050_IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void MPU6050_IIC_Send_Byte(u8 txd)
{                        
    u8 t;
	  MPU6050_IIC_SDA_IO_OUT();	
    MPU6050_IIC_SCL=0; 
    for(t=0;t<8;t++)
    {              
			if((txd&0x80)>>7)
				MPU6050_IIC_SDA=1;
			else
				MPU6050_IIC_SDA=0;
			txd<<=1; 	  
			MPU6050_IIC_delay_4us();    
			MPU6050_IIC_SCL=1;
			MPU6050_IIC_delay_4us(); 
			MPU6050_IIC_SCL=0;	
			MPU6050_IIC_delay_4us();
    }
    MPU6050_IIC_Read_Ack();		
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 MPU6050_IIC_Read_Byte(u8 ack)
{
		unsigned char i,receive=0;
		MPU6050_IIC_SDA_IO_IN();
		for(i=0;i<8;i++ )
		{
			MPU6050_IIC_SCL=0; 
			MPU6050_IIC_delay_4us();
			MPU6050_IIC_SCL=1;
			receive<<=1;
			if(MPU6050_IIC_SDA_IN)receive++;   
			MPU6050_IIC_delay_4us(); 
		}					 
		MPU6050_IIC_SCL=0;    
		MPU6050_IIC_delay_4us();
		MPU6050_IIC_Send_Ack(ack);
		return receive;
}


