#include "pid.h"

extern float Kp,Ki,Kd;   //直立环参数
float err;               //此次误差
float last_err;          //上次误差
float err_sum=0;         //误差累加
float err_difference;    //误差的差值

extern float VKp,VKi;    //速度环参数
float filt_velocity;     //滤波后的速度
float last_filt_velocity;//上一次的滤波后的速度
float velocity_sum=0;    //速度的累加
int verr;                //此次误差
int vlast_err;           //上次误差

extern float TKp,TKd;    //转向环的参数
int terr;                //此次的误差
int tlast_err;           //上一次的误差
int terr_difference;     //误差的差值

uint8_t over_flag(float jiaodu)
{
	uint8_t off_flag;
	if(jiaodu>35||jiaodu<-35)
	{
		off_flag=1;
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);GPIO_ResetBits(GPIOA,GPIO_Pin_5);
		GPIO_ResetBits(GPIOB,GPIO_Pin_14);GPIO_ResetBits(GPIOB,GPIO_Pin_15);
	}
	else off_flag=0;
	return off_flag;
}

void Xianfu(int max)
{
	if(velocity_sum>max){velocity_sum=max;}
	if(velocity_sum<-max){velocity_sum=-max;}
}

//直立环
int zhilihuan(float lilun,float shiji)
{
	err=lilun-shiji;
	err_sum+=err;
	err_difference=err-last_err;
	last_err=err;
	return Kp*err+Ki*err_sum+Kd*err_difference;
}

//速度环
int suduhuan(int vlilun,int vshiji)
{
	float a=0.3;
	verr=vlilun-vshiji;
	filt_velocity=a*verr+(1-a)*last_filt_velocity;
	velocity_sum+=filt_velocity;
	last_filt_velocity=filt_velocity;
	return VKp*filt_velocity+VKi*velocity_sum;
}	

//转向环
int zhuanxianghuan(int tlilun,int tshiji)
{
	terr=tshiji-tlilun;
	if(terr>180){terr=terr+360;}
	if(terr<-180){terr=terr-360;}
	terr_difference=terr-tlast_err;
	tlast_err=terr;
	return TKp*terr+TKd*terr_difference;
}
