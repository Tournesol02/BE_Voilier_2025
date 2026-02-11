#include "stm32f10x.h"
#include "PWM.h"

void MyTimer_PWM(TIM_TypeDef * Timer , int Channel){
	int pwrmd;
	#if POWERMODE //Powermode 1
			pwrmd = 0b110;
	#else
			pwrmd = 0b111; //Powermode 2
	#endif

				if (Channel 		== 1){
					Timer->CCMR1 	&= ~(0b111<<4); //On clear les trois bits qui sont de pwm
					Timer->CCMR1 	|= (pwrmd<<4); //On affecte le powermode au bits de lecture pour le µ-controlleur
					Timer->CCMR1 	|= TIM_CCMR1_OC1PE; //Update preload, il n'affecte pas le valeur avant que la prochaine cycle
					Timer->CCER 	= TIM_CCER_CC1E; //Enable le pin voulu basculer
				}
				else if (Channel == 2){
					Timer->CCMR1 		&= ~(0b111<<12); //Le TIMx_CCMR1 configure deux channels, de bit [6:4] CH1, [14:12] CH2 (OC2M = Output Channel 2 )
					Timer->CCMR1 		|= (pwrmd<<12); 
					Timer->CCMR1 		|= TIM_CCMR1_OC2PE; 
					Timer->CCER 		|= TIM_CCER_CC2E; 
				}
				else if (Channel == 3){
					Timer->CCMR1 		&= ~(0b111<<4);
					Timer->CCMR2 		|= (pwrmd<<4); 
					Timer->CCMR2 		|= TIM_CCMR2_OC3PE; 
					Timer->CCER 		|= TIM_CCER_CC3E; 
				}
				else if (Channel == 4){
					Timer->CCMR1		&= ~(0b111<<12);
					Timer->CCMR2 		|= (pwrmd<<12);
					Timer->CCMR2 		|= TIM_CCMR2_OC4PE;
					Timer->CCER 		|= TIM_CCER_CC4E; 
				}
				
				//En dessous d'ici, on a l'aide du plus gentil chat que je connais
			  // Enable auto-reload preload -- //Ensures that your initial configuration — PWM mode, duty cycle, period — actually takes effect before the timer starts counting.	
				Timer->CR1 |= TIM_CR1_ARPE;
				// Force update event to load ARR and CCR values immediately
				Timer->EGR |= TIM_EGR_UG;
				// Start the timer
				Timer->CR1 |= TIM_CR1_CEN;
				
				switch (Channel) {
					case 1:
						if (Timer == TIM1){GPIOA->CRH &= ~(0xF<<0*4); GPIOA->CRH |= (0xA<<0*4); TIM1->BDTR |= 1<<15; }
						if (Timer == TIM2){GPIOA->CRL &= ~(0xF<<0*4); GPIOA->CRL |= (0xA<<0*4);}
						if (Timer == TIM3){GPIOA->CRL &= ~(0xF<<6*4); GPIOA->CRL |= (0xA<<6*4);}
						if (Timer == TIM4){GPIOB->CRL &= ~(0xF<<5*4); GPIOB->CRL |= (0xA<<5*4);}
						break;
					case 2:
						if (Timer == TIM1){GPIOA->CRH &= ~(0xF<<1*4); GPIOA->CRL |= (0xA<<1*4); TIM1->BDTR |= 1<<15;}
						if (Timer == TIM2){GPIOA->CRL &= ~(0xF<<1*4); GPIOA->CRL |= (0xA<<1*4);}
						if (Timer == TIM3){GPIOA->CRL &= ~(0xF<<7*4); GPIOA->CRL |= (0xA<<7*4);}
						if (Timer == TIM4){GPIOB->CRL &= ~(0xF<<7*4); GPIOB->CRL |= (0xA<<7*4);}
						break;
					case 3:
						if (Timer == TIM1){GPIOA->CRH &= ~(0xF<<2*4); GPIOA->CRH |= (0xA<<2*4); TIM1->BDTR |= 1<<15;}
						if (Timer == TIM2){GPIOA->CRL &= ~(0xF<<2*4); GPIOA->CRL |= (0xA<<2*4);}
						if (Timer == TIM3){GPIOB->CRL &= ~(0xF<<0*4); GPIOB->CRL |= (0xA<<0*4);}
						if (Timer == TIM4){GPIOB->CRH &= ~(0xF<<0*4); GPIOB->CRH |= (0xA<<0*4);}
						break;
					case 4:
						if (Timer == TIM1){GPIOA->CRH &= ~(0xF<<3*4); GPIOA->CRH |= (0xA<<3*4); TIM1->BDTR |= 1<<15;}
						if (Timer == TIM2){GPIOA->CRL &= ~(0xF<<3*4); GPIOA->CRL |= (0xA<<3*4);}
						if (Timer == TIM3){GPIOB->CRL &= ~(0xF<<1*4); GPIOB->CRL |= (0xA<<1*4);}
						if (Timer == TIM4){GPIOB->CRH &= ~(0xF<<1*4); GPIOB->CRH |= (0xA<<1*4);}
						
					}
}

//Une fonction qui met le bon PWM voulu
int Set_DutyCycle_PWM(TIM_TypeDef *Timer, int Channel, int DutyC){
		int CCR_VAL = (Timer -> ARR + 1) * DutyC / 100;
		switch (Channel){
			case 1: Timer->CCR1 = CCR_VAL;
			break;
			case 2: Timer->CCR2 = CCR_VAL;
			break;
			case 3: Timer->CCR3 = CCR_VAL;
			break;
			case 4: Timer->CCR4 = CCR_VAL;
			break;
			default: break;
}
return 0;
Timer->EGR |= TIM_EGR_UG;
}

// NOuvelle Set_D	
int Set_DutyCycle_PWM_Plateau(TIM_TypeDef *Timer, int Channel, int DutyC){
     int CCR_VAL = (Timer->ARR + 1) * DutyC / 100;
     switch (Channel){
         case 1:
            Timer->CCR1 = CCR_VAL;
            break;
         case 2:
            Timer->CCR2 = CCR_VAL;
            break;
         case 3:
            Timer->CCR3 = CCR_VAL;
            break;
         case 4:
            Timer->CCR4 = CCR_VAL;
            break;
         default:
            return -1; // channel invalide
     }
     Timer->EGR |= TIM_EGR_UG; // update event
     return 0;
}
