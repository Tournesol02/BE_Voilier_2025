#include <stm32f10x.h>
#define PSC_VAL 624
#define ARR_VAL 0xE0FF

//DUTY CYCLE
#define DUTYC 70 //Chiffre entre 0 et 100, où 100 est 100% duty cycle
//#define POWERMODE 1 // 1 vaut powermode 1, 0 vaut powermode 2 (Powermode pour le config de dutycycle)
//Powermode 1 reste sur la bonne polarité: cad. si DUTY_CYCLE vaut 60 alors le signal reste HIGH pour 60% du periode, inverse pour pwmd2
//Timer
void Timer_Init(TIM_TypeDef *Timer, unsigned short Autoreload, unsigned short Prescaler);
void MyTimer_ActiveIT(TIM_TypeDef * Timer, char Prio, void(*Interrupt_fonc)(void));
void TIM2_IRQHandler(void);

//PWM
void MyTimer_PWM(TIM_TypeDef * Timer , int Channel);
int Set_DutyCycle_PWM(TIM_TypeDef *Timer, int Channel, int DutyC);