//Definitions

//INTERNE
#define LED_PIN_INTERNE (5) // 5 pour le LED de Arduino 
#define BUTTON_GPIO_INTERNE (GPIOA) //GPIOA pour l'Arduion
#define LED_GPIO_INTERNE (GPIOA) //GPIOA pour Arduino
#define BUTTON_PIN_INTERNE (13) //13 pour Arduino

//EXTERNE
#define LED_PIN_EXTERNE (8) // 8 pour la porte PB8
#define BUTTON_GPIO_EXTERNE (GPIOB) //GPIOB pour externe
#define LED_GPIO_EXTERNE (GPIOB) //GPIOB pour Externe
#define BUTTON_PIN_EXTERNE (9) //9 pour bouton poussoir

//STATIQUES
#define GPIO_OUTPUT_PPULL_MODE (2) //Mis en GP output 2MHz en mode PP
#define GPIO_INPUT_PUPD_MODE (8) //Pour mettre à Pull up/down
#define GPIO_INPUT_FLOATING_MODE (4) 

//si on est sur l'arduino ou sur le led externe
#define INTERNE  1 // 1 c'est vrai, 0 faux

//FONCTIONS
void initGPIO_Interne(void);
int boutonAppuye_Interne(void);
void allumerDEL_Interne(void);
void eteindreDEL_Interne(void);
void commuterDEL_Interne(void);
void allume_bit_Interne(void);

void initGPIO_Externe(void);
int boutonAppuye_Externe(void);
void allumerDEL_Externe(void);
void eteindreDEL_Externe(void);
void commuterDEL_Externe(void);
void allume_bit_Externe(void);


