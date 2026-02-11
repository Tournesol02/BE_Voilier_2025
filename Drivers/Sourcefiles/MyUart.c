#include <stm32f10x.h>
#include "DriverGPIO.h"



void My_USART_Config(USART_TypeDef* USARTx, uint32_t baudrate) { //QUE POUR USART_CR1_RE
	// Configuration PA9 (Tx) en Alternate Function Push-Pull
	MyGPIO_Init(GPIOA, 9 , AltOut_Ppull);
	// Configuration PA10 (Rx) en Input Floating
	MyGPIO_Init(GPIOA, 10 , In_Floating);
	NVIC_EnableIRQ(USART1_IRQn);
	NVIC_SetPriority(USART1_IRQn, 3<<4);
	
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	USARTx->CR1 |= USART_CR1_UE;
	USARTx->BRR = baudrate;
	USARTx->CR1 |= USART_CR1_TE;
  USARTx->CR1 |= USART_CR1_RE;
};


void USART_Send_Char(USART_TypeDef* USARTx, char car) {
    while ((USARTx->SR & USART_SR_TXE)==0){}
    USARTx->DR = car; 
};


void USART_Send_String(USART_TypeDef *USARTx, char *pString) {
    while (*pString != '\0') {
        USART_Send_Char(USARTx, *pString);
        pString++;
    }
};


void (*pFnc_Receive)(char);


void USART_IT_Receive_Enable(USART_TypeDef* USARTx) {
    USARTx->CR1 |= USART_CR1_RXNEIE;
};


void Init_IT_Receive(void (*Receive_IT_function) (char)) {
	pFnc_Receive = Receive_IT_function;
};


void USART1_IRQHandler(void) {
        signed char commande = USART1->DR;
        if (pFnc_Receive != 0) {
            pFnc_Receive(commande);
        }
};

