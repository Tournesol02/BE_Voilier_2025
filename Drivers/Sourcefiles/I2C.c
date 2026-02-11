#include <stm32f10x.h>
#include "I2C.h"


void initI2C() {
	RCC -> APB1ENR |= 0x1 << 21; // Enable clock
	I2C1 -> CR1 |= 0x1 << 0; // Peripheral enable
	I2C1 -> CR1 &= ~(0x1 << 1); //  I2C mode
}