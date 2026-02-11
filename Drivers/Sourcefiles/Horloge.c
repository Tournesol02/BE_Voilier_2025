#include <stm32f10x.h>
#include "Horloge.h"

static void (*TIM2_Appel)(void) = 0;
static void (*TIM3_Appel)(void) = 0;
static void (*TIM4_Appel)(void) = 0;


void Timer_Init(TIM_TypeDef *Timer, unsigned short Autoreload, unsigned short Prescaler) {
	if (Timer == TIM1) {
    // On ne l'utilise JAMAIS!!
	  RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	}
  else if (Timer == TIM2) {
	  TIM2->CR1 |= TIM_CR1_CEN;
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	}
  else if (Timer == TIM3) {
    TIM3->CR1 |= TIM_CR1_CEN;
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	}
  else if (Timer == TIM4) {
    TIM3->CR1 |= TIM_CR1_CEN;
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	}
	Timer->ARR |= Autoreload;
	Timer->PSC |= Prescaler;
  Timer->EGR |= TIM_EGR_UG;
}



void MyTimer_ActiveIT(TIM_TypeDef * Timer, char Prio, void(*Interrupt_fonc)(void)) { //On veut créer une fonction qui envoie un signal au cas où il y a debordement, avec une prioritaire, 0 plus importante 15 moins importante
	if (Timer == TIM2) {
		TIM2_Appel = Interrupt_fonc;
		
		NVIC_EnableIRQ(TIM2_IRQn);
		NVIC_SetPriority(TIM2_IRQn, Prio);
		TIM2->DIER |= TIM_DIER_UIE; //Le registre DIER(Interrupt Enable Register) est mis au bit Update Interrupt, qui se commute lors d'un overflow
		TIM2->CR1 |= TIM_CR1_CEN; //Clock Enable
	}
  else if (Timer == TIM3) {
    TIM3_Appel = Interrupt_fonc;

    NVIC_EnableIRQ(TIM3_IRQn);
    NVIC_SetPriority(TIM2_IRQn, Prio);
    TIM3->DIER |= TIM_DIER_UIE;
    TIM3->CR1 |= TIM_CR1_CEN;
  }
  else if (Timer == TIM4) {
    TIM4_Appel = Interrupt_fonc;

    NVIC_EnableIRQ(TIM4_IRQn);
    NVIC_SetPriority(TIM4_IRQn, Prio);
    TIM4->DIER |= TIM_DIER_UIE;
    TIM4->CR1 |= TIM_CR1_CEN;
  }
  else if (Timer == TIM1) {
    // On n'utilise pas TIM1
  }
  else {
    // L'horloge n'existe pas
  }
}

//La fonction TIM2_IRQHandler existe déjà dans le processeur, on l'a juste redifint, tel qu'à chaque overflow on met un bit 1 dans GPIOA_ODR
void TIM2_IRQHandler(void) { //On redefinit le IRQHandler qui est déjà ecrit dans le code source
  if (TIM2->SR & TIM_SR_UIF) { //On met le bit de overflow à un dès qu'on a overflow
    TIM2->SR &= ~TIM_SR_UIF; //Remise à zero
		if (TIM2_Appel){TIM2_Appel();}
  }
}

//La fonction TIM3_IRQHandler existe déjà dans le processeur, on l'a juste redifint, tel qu'à chaque overflow on met un bit 1 dans GPIOA_ODR
void TIM3_IRQHandler(void) { //On redefinit le IRQHandler qui est déjà ecrit dans le code source
  if (TIM3->SR & TIM_SR_UIF) { //On met le bit de overflow à un dès qu'on a overflow
    TIM3->SR &= ~TIM_SR_UIF; //Remise à zero
	  if (TIM3_Appel){TIM3_Appel();}
  }
}

//La fonction TIM4_IRQHandler existe déjà dans le processeur, on l'a juste redifint, tel qu'à chaque overflow on met un bit 1 dans GPIOA_ODR
void TIM4_IRQHandler(void) { //On redefinit le IRQHandler qui est déjà ecrit dans le code source
  if (TIM4->SR & TIM_SR_UIF) { //On met le bit de overflow à un dès qu'on a overflow
    TIM4->SR &= ~TIM_SR_UIF; //Remise à zero
	  if (TIM4_Appel){TIM4_Appel();}
  }
}



