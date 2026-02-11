#ifndef DRIVERGPIO_H_
#define DRIVERGPIO_H_
#include "stm32f10x.h"
#define In_Floating 0x4
#define In_PullDown 0x8
#define In_PullUp 0x8
#define In_Analog 0x0
#define Out_Ppull 0x3
#define Out_OD 0x7
#define AltOut_Ppull 0xB
#define AltOut_OD 0xF
extern void MyGPIO_Init(GPIO_TypeDef * GPIO, char pin, char conf );
extern int MyGPIO_Read(GPIO_TypeDef * GPIO, char GPIO_Pin); // renvoie 0 ou autre chose different de 0
extern void MyGPIO_Set(GPIO_TypeDef * GPIO, char GPIO_Pin);
extern void MyGPIO_Reset(GPIO_TypeDef * GPIO, char GPIO_Pin);
extern void MyGPIO_Toggle(GPIO_TypeDef * GPIO, char GPIO_Pin);
void MYGPIO_PinOff (GPIO_TypeDef *GPIO , char GPIO_Pin);
void MYGPIO_PinOn (GPIO_TypeDef *GPIO , char GPIO_Pin);
#endif
