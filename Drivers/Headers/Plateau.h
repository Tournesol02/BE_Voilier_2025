#include "stm32f10x.h"

void initPlato(TIM_TypeDef * Timer, int Channel);
void Update_Motor_PWM(int Consigne, TIM_TypeDef * Timer, int Channel);