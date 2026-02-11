#include <stdlib.h>
#include <stm32f10x.h>
#include "MYGPIO.h"


//FONCTIONS POUR LE DEL INTERNE
void initGPIO_Interne(void) {
	RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4) ;

	//Start
	//CRL pour les 8 premiers portes, CRH pour les 8 dernières portes
	if (LED_PIN_INTERNE < 8) {
		LED_GPIO_INTERNE->CRL &= ~(0xF << (LED_PIN_INTERNE*4)); 
		LED_GPIO_INTERNE->CRL |= GPIO_OUTPUT_PPULL_MODE<<(LED_PIN_INTERNE*4)	;	 // On met tous les Pins de broche A à ANalog Input sauf broche PA.5 qui correspond au LED GREEN: Output 2MHz et GP output push-pull
	}
	else {
		LED_GPIO_INTERNE->CRH &= ~(0xF <<((LED_PIN_INTERNE-8)*4));
		LED_GPIO_INTERNE->CRH |= GPIO_OUTPUT_PPULL_MODE<<((LED_PIN_INTERNE-8)*4);
	}
	
	if (BUTTON_PIN_INTERNE < 8) {
		BUTTON_GPIO_INTERNE->CRL &= ~(0xF << (BUTTON_PIN_INTERNE*4)); 
		BUTTON_GPIO_INTERNE->CRL |= GPIO_INPUT_FLOATING_MODE<<(BUTTON_PIN_INTERNE*4)	;	 // On met tous les Pins de broche A à ANalog Input sauf broche PA.5 qui correspond au LED GREEN: Output 2MHz et GP output push-pull
	}
	else {
		BUTTON_GPIO_INTERNE->CRH &= ~(0xF <<((BUTTON_PIN_INTERNE-8)*4));
		BUTTON_GPIO_INTERNE->CRH |= GPIO_INPUT_FLOATING_MODE<<((BUTTON_PIN_INTERNE-8)*4);
	}
}


int boutonAppuye_Interne(void) {
	return BUTTON_GPIO_INTERNE->IDR &(1<<BUTTON_PIN_INTERNE);
}


void allumerDEL_Interne(void) {
			LED_GPIO_INTERNE->ODR |= (0x01 << LED_PIN_INTERNE) ; //On essaie de mettre en position PA5 de GPIOC_ODR un 1 comme ca allume le LED GREEN
}


void eteindreDEL_Interne(void) { // Allumer un LED externe, PB8/D15 OUTPUT, Bouton Poussoir PB9/D14
	LED_GPIO_INTERNE->ODR &= ~(0x01 << LED_PIN_EXTERNE) ; //On essaie de mettre en position PA5 de GPIOC_ODR un 0 comme ca eteint le LED GREEN
}


void commuterDEL_Interne(void) {
	LED_GPIO_INTERNE->ODR ^= (0x01 << LED_PIN_INTERNE);
}



//FONCTIONS POUR LE DEL EXTERNE
void initGPIO_Externe(void) {
	RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4) ;

	// CRL pour les 8 premiers portes, CRH pour les 8 dernières portes
	if (LED_PIN_EXTERNE < 8) {
		LED_GPIO_EXTERNE->CRL &= ~(0xF << (LED_PIN_EXTERNE*4)); 
		LED_GPIO_EXTERNE->CRL |= GPIO_OUTPUT_PPULL_MODE<<(LED_PIN_EXTERNE*4)	;	 // On met tous les Pins de broche A à ANalog Input sauf broche PA.5 qui correspond au LED GREEN: Output 2MHz et GP output push-pull
	}
	else {
		LED_GPIO_EXTERNE->CRH &= ~(0xF <<((LED_PIN_EXTERNE-8)*4));
		LED_GPIO_EXTERNE->CRH |= GPIO_OUTPUT_PPULL_MODE<<((LED_PIN_EXTERNE-8)*4);
	}
	if (BUTTON_PIN_EXTERNE < 8) {
		BUTTON_GPIO_EXTERNE->CRL &= ~(0xF << (BUTTON_PIN_EXTERNE*4)); 
		BUTTON_GPIO_EXTERNE->CRL |= GPIO_INPUT_FLOATING_MODE<<(BUTTON_PIN_EXTERNE*4)	;	 // On met tous les Pins de broche A à ANalog Input sauf broche PA.5 qui correspond au LED GREEN: Output 2MHz et GP output push-pull
	}
	else {
		BUTTON_GPIO_EXTERNE->CRH &= ~(0xF <<((BUTTON_PIN_EXTERNE-8)*4));
		BUTTON_GPIO_EXTERNE->CRH |= GPIO_INPUT_FLOATING_MODE<<((BUTTON_PIN_EXTERNE-8)*4);
	}
}


int boutonAppuye_Externe(void) {
	return BUTTON_GPIO_EXTERNE->IDR &(1<<BUTTON_PIN_EXTERNE);
}


void allumerDEL_Externe(void) { // On essaie de mettre en position PA5 de GPIOC_ODR un 1 comme ca allume le LED GREEN
			LED_GPIO_EXTERNE->ODR |= (0x01 << LED_PIN_EXTERNE) ; 	
}							


void eteindreDEL_Externe(void) { // Allumer un LED externe, PB8/D15 OUTPUT, Bouton Poussoir PB9/D14
	LED_GPIO_EXTERNE->ODR &= ~(0x01 << LED_PIN_EXTERNE) ; // On essaie de mettre en position PA5 de GPIOC_ODR un 0 comme ca eteint le LED GREEN
}


void commuterDEL_Externe(void) {
	LED_GPIO_EXTERNE->ODR ^= (0x01 << LED_PIN_EXTERNE);
}

