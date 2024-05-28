#ifndef __MOTOR_H
#define __MOTOR_H

void Motor_Init(void);
void pwxianfu(int max,int*pw);
void SETPWM_l(int pw);
void SETPWM_r(int pw);
void Motor_off(void);

#endif
