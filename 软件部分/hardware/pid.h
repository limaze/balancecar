#ifndef ___PID_H
#define ___PID_H

#include "stm32f10x.h"                  // Device header

uint8_t over_flag(float jiaodu);
void Xianfu(int max);
int zhilihuan(float lilun,float shiji);
int suduhuan(int vlilun,int vshiji);
int jsuduhuan(int alilun,int ashiji);
int dsuduhuan(int dlilun,int dshiji);
int zhuanxianghuan(int tlilun,int tshiji);

#endif
