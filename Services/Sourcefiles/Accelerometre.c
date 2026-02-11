#include <stm32f10x.h>
#include "Horloge.h"
#include "stdlib.h"
#include "MySPI.h"
#include "stdint.h"
#include "Accelerometre.h"
#include "Servo.h"


void initAccelo(void) {
	MySPI_Init(SPI1);
	// Power_CTL register = 0x2D ? write 0x08 (MEASURE = 1)
	MySPI_Clear_NSS();
	MySPI_Send(0x31); // DATA_FORMAT
	MySPI_Send(0b00001101); // Justify met le MSB à gauche et b0 et b1 donne une resolution de +-2g
	MySPI_Set_NSS();

	MySPI_Clear_NSS();
	MySPI_Send(0x2D & 0x3F); // Écriture de l'adresse (pas de bit de read!)
	MySPI_Send(0x08); // Affectation du bit MEASURE
	MySPI_Set_NSS();
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; // Activation de l'horloge Utiliser une service pour cela peut-être ???
	for (volatile int i = 0; i < 10000; i++); // small delay
}


uint16_t * RecupAccelo(void) { // Recuperation des donnees de l'accelerometre
  static uint16_t Messie[3];
  uint8_t buf[6];
  MySPI_Clear_NSS(); 
  // Lecture multi-octet à partir de 0x32 (X0, X1, Y0, Y1, Z0 et Z1)
  MySPI_Send(0x80 | 0x40 | 0x32); // On envoie RW MB A5 ... A0 pour recuperer les données
  for (int i = 0; i < 6; i++) {buf[i] = (uint8_t)MySPI_Read();} // Lecture des 6 registres en séquenciel
  MySPI_Set_NSS();

  // Conversion des données récupérés en uint16_t
  Messie[0] = (uint16_t)(buf[1] << 8 | buf[0]); // X
  Messie[1] = (uint16_t)(buf[3] << 8 | buf[2]); // Y
  Messie[2] = (uint16_t)(buf[5] << 8 | buf[4]); // Z
  return Messie;
}


void initLacheur(void) {
	GPIOB->CRH &= ~(0xF << (0 * 4));
	GPIOB->CRH |=  (0xA << (0 * 4)); //On met GPIOB.8 en mode output 2Mhz, alternate pp

  Timer_Init(TIM4, 0xFFFF, 22);
}


void LacheVoile(int AngelLim, uint16_t moyennen) {
	volatile uint16_t Val_lim = 0x1E20 - 60*AngelLim;
	if (moyennen<Val_lim){
		Servo_Moteur(0, TIM4, 3); // PB7 (TIM4Ch3)
	}
}


//int actualiserTableau(int i) {
//	moyenne[i] = RecupAccelo()[2]; // Récuperation et ajout de la valeur plus récente dans le tableau dans la position i
//  i++;
//	if (i >= LONGUEUR_MOY) {i = 0;} // Géstion de la position i dans le tableau pour la moyenne glissante
//	return i;
//}


//uint16_t moyenneGlissante() {
//	sum = 0;
//	for (int j = 0; j < LONGUEUR_MOY; j++){sum += moyenne[j];} moy = sum / LONGUEUR_MOY; // Calcul de la moyenne glissante
//	return(moy);
//	}
// À faire : Gestion par interruption

