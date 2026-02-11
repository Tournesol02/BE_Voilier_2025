#include <stm32f10x.h>
#include <ADC.h>
#include <MyUart.h>
#include <stdint.h>
#include <stdio.h>

//Pont diviseur du tension, coeff. = 1/13
//Alors 13V -> 12V*1/13 = 0.92V

//Tension pile donné sur GPIOA.2
void initADC(){
		//Initialisation de ADC
	
	RCC->APB2ENR |= (0x1<<10); //Initialisation du clock interne du ADC2
	RCC->APB2ENR |= (0x1<<2);	//GPIOA clk enable
	ADC2->CR2 |= (0x1); // ON/OFF ADC2
	
	//Init de la broche PA2 en mode analog input
	GPIOA->CRL &= ~(0x00000F00);
	
	ADC2->CR2 |= (0x1<<20); //External trigger enable
	ADC2->CR2 |= (0b111<<17);	//SWSTART
	ADC2->CR2 |= (0x1<<1); //Continous conversion
	ADC2->SQR3 = 2;
	
	//Essai de faire un nouveau Threshold/Seuil
	ADC2->CR1 |= (0x1<<23); //Watchdog enable pour mettre un threshold HIGH
	ADC2->HTR &= ~(0x0FFF);
	
	//########################MAHOUT AIDEZ NOUS############################æ
	//ADC2->HTR |= 0x0475; //Changement du threshold (0.92V/3.3V)*4096
	//ADC2->HTR |= 0x0BBB; //Faut demander le prof pour ce HIGH THRESHOLD
	ADC2->CR2 |= (0x1); //ON ADC2
}

int recupADC(){
	int data;
	data = ADC2->DR;
	return data;
}

void sendinfoADC(){
	int valu = recupADC();
	char meld[60];
	char meld2[50];
	
	int test = valu*3.3/4096;
	test = test*13*100/12;
	int tension = (13*valu)/ADC2->HTR;
	int p2 = (13*valu)/0x0FFF;
	snprintf(meld, sizeof(meld),"Pourcentage de la pile : riktig: %d next %d next %d \r\n", tension, test, p2);
	snprintf(meld2, sizeof(meld2),"Tension de la pile : %dV\r\n", tension);
	
	USART_Send_String(USART1, meld2);
}

