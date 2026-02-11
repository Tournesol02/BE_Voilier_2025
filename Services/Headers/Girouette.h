#ifndef _GIROUETTE_H
#define _GIROUETTE_H
#include "stm32f10x.h"
extern void configEncoder(TIM_TypeDef * Timer);
extern int angleVent (TIM_TypeDef * Timer);
extern int vent2voile(int angle);
extern void LocaliserZero(void);
#endif
