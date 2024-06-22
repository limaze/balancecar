#include "pid.h"

extern float Kp,Ki,Kd;   //ֱ��������
float err;               //�˴����
float last_err;          //�ϴ����
float err_sum=0;         //����ۼ�
float err_difference;    //���Ĳ�ֵ

extern float VKp,VKi;    //�ٶȻ�����
float filt_velocity;     //�˲�����ٶ�
float last_filt_velocity;//��һ�ε��˲�����ٶ�
float velocity_sum=0;    //�ٶȵ��ۼ�
int verr;                //�˴����
int vlast_err;           //�ϴ����

extern float AKp,AKi;    //���ٶȻ�����
float filt_aelocity;     //�˲�����ٶ�
float last_filt_aelocity;//��һ�ε��˲�����ٶ�
float aelocity_sum=0;    //�ٶȵ��ۼ�
int aerr;                //�˴����
int alast_err;           //�ϴ����

extern float JKp,JKi;    //���ٶȻ�����
float filt_jelocity;     //�˲�����ٶ�
float last_filt_jelocity;//��һ�ε��˲�����ٶ�
float jelocity_sum=0;    //�ٶȵ��ۼ�
int jerr;                //�˴����
int jlast_err;           //�ϴ����

extern float TKp,TKd;    //ת�򻷵Ĳ���
int terr;                //�˴ε����
int tlast_err;           //��һ�ε����
int terr_difference;     //���Ĳ�ֵ

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

//ֱ����
int zhilihuan(float lilun,float shiji)
{
	err=lilun-shiji;
	err_sum+=err;
	err_difference=err-last_err;
	last_err=err;
	return Kp*err+Ki*err_sum+Kd*err_difference;
}

//�ٶȻ�
int suduhuan(int vlilun,int vshiji)
{
	float a=0.3;
	verr=vlilun-vshiji;
	filt_velocity=a*verr+(1-a)*last_filt_velocity;
	velocity_sum+=filt_velocity;
	last_filt_velocity=filt_velocity;
	return VKp*filt_velocity+VKi*velocity_sum;
}

//���ٶȻ�
int jsuduhuan(int alilun,int ashiji)
{
	float a=0.3;
	aerr=alilun-ashiji;
	filt_aelocity=a*aerr+(1-a)*last_filt_aelocity;
	aelocity_sum+=filt_aelocity;
	last_filt_aelocity=filt_aelocity;
	return AKp*filt_aelocity+AKi*aelocity_sum;
}	

//���ٶȻ�
int dsuduhuan(int dlilun,int dshiji)
{
	float a=0.3;
	jerr=dlilun-dshiji;
	filt_jelocity=a*jerr+(1-a)*last_filt_jelocity;
	jelocity_sum+=filt_jelocity;
	last_filt_jelocity=filt_jelocity;
	return JKp*filt_jelocity+JKi*jelocity_sum;
}	


//ת��
int zhuanxianghuan(int tlilun,int tshiji)
{
	terr=tshiji-tlilun;
	if(terr>180){terr=terr+360;}
	if(terr<-180){terr=terr-360;}
	terr_difference=terr-tlast_err;
	tlast_err=terr;
	return TKp*terr+TKd*terr_difference;
}
