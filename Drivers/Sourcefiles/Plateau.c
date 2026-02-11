#include "stm32f10x.h"
#include "PWM.h"
#include "DriverGPIO.h"
#include "Horloge.h"

void initPlato(TIM_TypeDef * Timer, int Channel) { // Config du moteur servo	
	MyGPIO_Init(GPIOB, 5, AltOut_Ppull); //config pin de direction 0 ou 1
  if (Timer == TIM3) {
		Timer_Init(TIM3, 159, 17); // Pour obtenir fréq de 20kHZ
    if (Channel == 3) {
      MyGPIO_Init(GPIOB, 0, AltOut_Ppull); // Outut push pull alternate, config pin de consigne entre -100 et 100
      MyTimer_PWM(TIM3, 3); //TIM3 CH3
    }
    else {
      //printf("Ce pilote n'existe pas");
    }
  }
  else {
    //printf("Ce pilote n'existe pas");
  }
}


void Update_Motor_PWM(int Consigne, TIM_TypeDef * Timer, int Channel) {
  int duty_cycle;
		if (Consigne>=0) {
		  MyGPIO_Set(GPIOB, 5);
			duty_cycle = Consigne;
		}
		if (Consigne<0){
			MyGPIO_Reset(GPIOB,5);
			duty_cycle = -Consigne;
		}
		Set_DutyCycle_PWM_Plateau(Timer, Channel, duty_cycle);
}
