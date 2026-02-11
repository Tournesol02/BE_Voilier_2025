#ifndef ACC_H
#define ACC_H
#include <stm32f10x.h>
#include <stdint.h>

#define LONGUEUR_MOY 10
#define ANGLE_LIMITE 60 // Angle ou les voiles seront lachés, SE MODIFIE

//uint16_t moyenne[LONGUEUR_MOY];
//uint32_t sum;
//uint16_t i;
//volatile uint32_t moy; // Volatile pour pouvoir le regarder dans Keil µVision

void initAccelo(void);
void initLacheur(void);
uint16_t * RecupAccelo(void);
void LacheVoile(int AngelLim, uint16_t moyennen);

//uint16_t moyenneGlissante();
//int actualiserTableau(int i );
#endif 