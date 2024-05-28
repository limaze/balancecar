#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MPU6050.h"
#include "inv_mpu.h"
#include "EXTI.h"
#include "AD.h"
#include "BUZZER.h"
#include "pid.h"
#include "ENCODER.h"
#include "Motor.h"

float Pitch,Roll,Yaw;								//俯仰角默认跟中值一样，翻滚角，偏航角
int16_t ax,ay,az,gx,gy,gz;							//加速度，陀螺仪角速度

u8 MPU_Get_Gyroscope(short *gx,short *gy,short *gz);
u8 MPU_Get_Accelerometer(short *ax,short *ay,short *az);

uint8_t power_flag=0;

//直立环参数:
float Kp=-420,Ki=0,Kd=-2000; 

//速度环参数:
float VKp=+190,VKi=0.95; 

//转向环参数
float TKp=0,TKd=0;

uint32_t a;
uint16_t ad;
float dv;
int16_t speed1,speed2;//编码器1和2的速度
float zhongzhi=0;//理论小车平衡时的角度

float zllilun,zlshiji;//直立环的理论值和实际值
int sdlilun,sdshiji;//速度环的理论值和实际值
int zxlilun,zxshiji;//转向环的理论值和实际值

int main(void)
{
	OLED_Init();
	MPU6050_Init();
	MPU6050_DMP_Init();
	EXTI1_Init();
	AD_Init();
	BUZZER_Init();
	Encoder1_Init();
	Encoder2_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	OLED_ShowString(1,1,"AD:");
	OLED_ShowString(1,9,"V: .");
	while(1)
	{
		speed1=Get_Encoder1();
		speed2=Get_Encoder2();
		ad=AD_Read();
		dv=(float)ad/4095*3.3;
		OLED_ShowNum(1,4,ad,4);
		OLED_ShowNum(1,11,dv,1);
		OLED_ShowNum(1,13,(uint16_t)(dv*100)%100,2);
		OLED_ShowSignedNum(2, 1, Pitch, 5);
		OLED_ShowSignedNum(3, 1, Roll, 5);
		OLED_ShowSignedNum(4, 1, Yaw, 5);
		OLED_ShowSignedNum(2, 8, gx, 5);
		OLED_ShowSignedNum(3, 8, gy, 5);
		OLED_ShowSignedNum(4, 8, gz, 5);
//		Delay_ms(500);
	}
}

void EXTI15_10_IRQHandler(void)
{
	int pwm_out,pwm_zhuan,pwm1_out,pwm2_out;
	if(EXTI_GetITStatus(EXTI_Line13)==SET)
	{
		MPU6050_DMP_Get_Data(&Pitch,&Roll,&Yaw);				
		MPU_Get_Gyroscope(&gx,&gy,&gz);
		if(over_flag(Roll)==1){Motor_off();}
		zlshiji=Pitch;
		zllilun=zhongzhi;
		sdshiji=(Get_Encoder1()+Get_Encoder2())/2;
		sdlilun=0;
		pwm_out=zhilihuan(zllilun,zlshiji)+suduhuan(sdlilun,sdshiji);
		pwm_zhuan=zhuanxianghuan(zxlilun,zxshiji);
		pwm1_out=pwm_out+pwm_zhuan;
		pwm2_out=pwm_out-pwm_zhuan;
		pwxianfu(7000,&pwm1_out);
		pwxianfu(7000,&pwm2_out);
		if(power_flag==0)
		{
			SETPWM_l(pwm1_out);
			SETPWM_r(pwm2_out);
		}
		EXTI_ClearITPendingBit(EXTI_Line13);
	}
}

void ADC1_2_IRQHandler(void)
{
	if(ADC_GetFlagStatus(ADC1,ADC_FLAG_AWD)==SET)
	{
		BUZZER_on();
		power_flag=1;
		ADC_ClearFlag(ADC1,ADC_FLAG_AWD);
	}
}
