#include <stm32f10x.h>
#include "DriverGPIO.h"

// Constantes
#define In_Floating 0x4
#define In_PullDown 0x8
#define In_PullUp 0x8
#define In_Analog 0x0
#define Out_Ppull 0x3
#define Out_OD 0x7
#define AltOut_Ppull 0xB
#define AltOut_OD 0xF


void MyGPIO_Init(GPIO_TypeDef * GPIO, char pin, char conf) {
	int shift_pin;

	//Start clock for relevant GPIO
	if(GPIO == GPIOA) {
		RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
	}
	else if(GPIO == GPIOB) {
		RCC -> APB2ENR |= RCC_APB2ENR_IOPBEN;
	}
	else if(GPIO == GPIOC) {
		RCC -> APB2ENR |= RCC_APB2ENR_IOPCEN;
	}
	else if(GPIO == GPIOD) {
		RCC -> APB2ENR |= RCC_APB2ENR_IOPDEN;
	}
	if(pin < 8) {//CRL zone
		shift_pin = pin*4;
		GPIO -> CRL &= ~(0xF << shift_pin);
		//PullUp and PullDown have the same conf number, so we need to change the ODR to diferenciate them both
		if(conf == In_PullUp) {
			GPIO -> CRL |= ( In_PullUp << shift_pin);
			GPIO -> ODR |= (1<<pin);
		}
		else if(conf == In_PullDown) {
			GPIO -> CRL |= ( In_PullDown << shift_pin);
			GPIO -> ODR &= ~(1<<pin);
		}
		else {
			GPIO -> CRL |= ( conf << shift_pin);
		}
	}
	else {//CRH zone
		shift_pin = (pin-8)*4;
		GPIO -> CRH &= ~(0xF << shift_pin);
		if(conf == In_PullUp) {
			GPIO -> CRH |= ( In_PullUp << shift_pin);
			GPIO -> ODR |= (1<<pin);
		}
		else if(conf == In_PullDown) {
			GPIO -> CRH |= ( In_PullDown << shift_pin);
			GPIO -> ODR &= ~(1<<pin);
		}
		else {
			GPIO -> CRH |= ( conf << shift_pin);
		}
	}
}


int MyGPIO_Read(GPIO_TypeDef * GPIO, char GPIO_Pin) {
	return(GPIO -> IDR & (1 << GPIO_Pin));
}


void MyGPIO_Set(GPIO_TypeDef * GPIO, char GPIO_Pin) {
	GPIO -> BSRR = (1<<GPIO_Pin);//1 on set zone
}


void MyGPIO_Reset(GPIO_TypeDef * GPIO, char GPIO_Pin) {
	GPIO -> BSRR = (1<<(GPIO_Pin+16));//1 on reset zone
}


void MYGPIO_PinOn (GPIO_TypeDef *GPIO , char GPIO_Pin){
	GPIO->ODR |= (1<<GPIO_Pin); 
};

void MYGPIO_PinOff (GPIO_TypeDef *GPIO , char GPIO_Pin){
	GPIO->ODR &= ~(1<<GPIO_Pin); 
};


void MyGPIO_Toggle(GPIO_TypeDef * GPIO, char GPIO_Pin) {
	GPIO -> ODR = GPIO -> ODR ^ (0x1 << GPIO_Pin);
}

