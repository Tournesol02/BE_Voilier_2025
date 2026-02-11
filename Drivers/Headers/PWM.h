#ifndef PWM_H_
#define PWM_H_
#include "stm32f10x.h"
//Variables
#define POWERMODE 2 // 1 vaut powermode 1, 0 vaut powermode 2 (Powermode pour le config de dutycycle)
// Config
extern void MyTimer_PWM(TIM_TypeDef * Timer , int Channel);
extern int Set_DutyCycle_PWM(TIM_TypeDef *Timer, int Channel, int DutyC);
int Set_DutyCycle_PWM_Plateau(TIM_TypeDef *Timer, int Channel, int DutyC);
#endif
