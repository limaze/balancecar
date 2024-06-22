#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MPU6050.h"
#include "inv_mpu.h"
#include "EXTI.h"
#include "pid.h"
#include "ENCODER.h"
#include "Motor.h"
#include "Key.h"
#include "PWM.h"
#include "BLUETOOTH.h"

float Pitch,Roll,Yaw;								//俯仰角默认跟中值一样，翻滚角，偏航角
int16_t ax,ay,az,gx,gy,gz;							//加速度，陀螺仪角速度

u8 MPU_Get_Gyroscope(short *gx,short *gy,short *gz);
u8 MPU_Get_Accelerometer(short *ax,short *ay,short *az);

uint8_t power_flag=0;

//直立环参数:
float Kp=-300,Ki=0,Kd=-780; 

//速度环参数:
float VKp=-260,VKi=-1.3; 

//加速度环参数:
float AKp=-0.008,AKi=-0.002; 

//角速度环参数:
float JKp=15,JKi=0.02; 

//转向环参数
float TKp=30,TKd=6;

int16_t speed1,speed2;//编码器1和2的速度
float zhongzhi=0;//理论小车平衡时的角度

float zllilun,zlshiji;//直立环的理论值和实际值
int sdlilun,sdshiji;//速度环的理论值和实际值
int jsdlilun=0,jsdshiji;//加速度环的理论值和实际值
int dsdlilun=-10,dsdshiji;//角速度环的理论值和实际值
int zxlilun=0,zxshiji=0;//转向环的理论值和实际值

uint8_t keynum;
uint8_t blsj;

int main(void)
{
	OLED_Init();
	MPU6050_Init();
	MPU6050_DMP_Init();
	EXTI1_Init();
	Encoder1_Init();
	Encoder2_Init();
	Motor_Init();
	Ket_Init();
	Bluet_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	OLED_ShowString(1,1,"SPEED:");
	zxshiji=Yaw;
	while(1)
	{
		speed1=Get_Encoder1();
		speed2=Get_Encoder2();
		OLED_ShowSignedNum(1,7,speed1,4);
		OLED_ShowSignedNum(1,12,speed2,4);
		OLED_ShowSignedNum(2, 1, Pitch, 5);
		OLED_ShowSignedNum(3, 1, Roll, 5);
		OLED_ShowSignedNum(4, 1, Yaw, 5);
		OLED_ShowSignedNum(2, 8, gx, 5);
		OLED_ShowSignedNum(3, 8, gy, 5);
		OLED_ShowSignedNum(4, 8, gz, 5);
		if(Get_BluetBZ()==1)
		{
			blsj=Get_BluetSJ();
//			OLED_ShowSignedNum(4, 8, blsj, 5);
			switch(blsj)
			{
				case 0:sdlilun=0;
				case 1:sdlilun=-1;break;
				case 2:sdlilun=1;break;
				case 3:zxlilun+=20;break;
				case 4:zxlilun-=20;break;
				case 5:sdlilun--;break;
				case 6:sdlilun++;break;
				case 7:Motor_off();break;
			}
		}
		if(blsj!=3&&blsj!=4)
		{
			zxlilun=Yaw;
		}
//		Delay_ms(500);
	}
}

void EXTI15_10_IRQHandler(void)
{
	int pwm_out,pwm_zhuan=0,pwm1_out,pwm2_out;
	if(EXTI_GetITStatus(EXTI_Line13)==SET)
	{
		MPU6050_DMP_Get_Data(&Pitch,&Roll,&Yaw);				
		MPU_Get_Gyroscope(&gx,&gy,&gz);
		MPU_Get_Accelerometer(&ax,&ay,&az);
		if(over_flag(Roll)==1){Motor_off();}
		zlshiji=Roll;
		zllilun=zhongzhi;
		sdshiji=(Get_Encoder1()+Get_Encoder2())/2;
		jsdshiji=ay;
		zxshiji=Yaw;
		pwm_out=zhilihuan(zllilun,zlshiji)+suduhuan(sdlilun,sdshiji)+jsuduhuan(jsdlilun,jsdshiji)+dsuduhuan(dsdlilun,dsdshiji);
		pwm_zhuan=zhuanxianghuan(zxlilun,zxshiji);
		pwm1_out=pwm_out+pwm_zhuan;
		pwm2_out=pwm_out-pwm_zhuan;
		pwxianfu(7000,&pwm1_out);
		pwxianfu(7000,&pwm2_out);
//		if(power_flag==0)
//		{
			SETPWM_l(pwm1_out);
			SETPWM_r(pwm2_out);
//		}
		EXTI_ClearITPendingBit(EXTI_Line13);
	}
}
