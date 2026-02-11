#include "stm32f10x.h"
#include "Horloge.h"
#include "DriverGPIO.h"
#include "Girouette.h"
#include "PWM.h"

#include <stdlib.h> // Pour abs()

#define POSITIONS (360*4) //0x5A0

void configEncoder(TIM_TypeDef * Timer) {
  // Timer
  Timer_Init(Timer, 0, 0);
    
  // Settings
  Timer -> CCMR1 |= TIM_CCMR1_CC1S; // TI1FP1 mapped on TI1
  Timer -> CCMR1 |= TIM_CCMR1_CC2S; // TI1FP2 mapped on TI2
  Timer -> CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC1NP); // TI1FP1 output non-inverted
  Timer -> CCMR1 &= ~(TIM_CCMR1_IC1F); // Input capture 1 filter, no filter
  Timer -> CCER &= ~(TIM_CCER_CC2P | TIM_CCER_CC2NP); // TI1FP2 output non-inverted 
  Timer -> CCMR2 &= ~(TIM_CCMR1_IC2F); // Input capture 2 filter, no filter
  Timer -> SMCR &= ~TIM_SMCR_SMS;	// Reset SMS-bits
  Timer -> SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;// SMS = "011"
  Timer -> CR1 |= TIM_CR1_CEN; // Enable counter
  Timer -> ARR = 0x5A0; // Setting ARR as 1440

  // GPIO
  MyGPIO_Init(GPIOA,0,In_Floating ); // GPIOA pin 0 in mode floating TIM2_CH1
  MyGPIO_Init(GPIOA,1,In_Floating ); // GPIOA pin 1 in mode floating TIM2_CH2
  MyGPIO_Init(GPIOA,8,In_PullDown ); // GPIOA pin 8 in mode floating Index
}


int angleVent(TIM_TypeDef * Timer) { // Returner l'angle du vent
  int angle =(((Timer -> CNT*360)/POSITIONS ));
	if (angle > 180){
		angle = 360 - angle; // Pour que l'angle soit entre 0 et 180
	}
	return(angle);
}


int vent2voile(int angle) { // Conversion angle vent à angle voile
	if(angle < 45){
		return 0;// Les voiles restent immobiles
	}
	else{
		return(2*(angle-45)/3); // Augmentation linéaire
	}
}


void LocaliserZero(void) { // Localisation de z
int Z_trouve = 0;
	while (Z_trouve != 1){
		if(MyGPIO_Read(GPIOA,8)){ // Index
			TIM2 -> CNT = 0x0; // Remet angle à zero
			Z_trouve = 1;
		}	
	}	
}	

