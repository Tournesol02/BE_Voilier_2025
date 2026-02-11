#include <stm32f10x.h>
#include <stdint.h>

#define GPIO_ANALOG_INPUT 0

void initADC();
int recupADC(void); 
void sendinfoADC();