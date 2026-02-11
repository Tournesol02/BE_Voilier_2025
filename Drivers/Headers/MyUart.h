#include "stm32f10x.h"


void My_USART_Config(USART_TypeDef* , uint32_t );
void USART_Send_Char(USART_TypeDef* , char );
void USART_Send_String(USART_TypeDef*, char*);
void USART_IT_Receive_Enable(USART_TypeDef*);
void Init_IT_Receive(void (*Receive_IT_function) (int));
