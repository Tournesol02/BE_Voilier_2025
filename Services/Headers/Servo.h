#ifndef SERVO_H_
#define SERVO_H_
#include <stm32f10x.h>
void Servo_Moteur(int angle, TIM_TypeDef * Timer, int Channel);
extern void initServo(TIM_TypeDef * Timer, int Channel);

#endif // SERVO_H_
