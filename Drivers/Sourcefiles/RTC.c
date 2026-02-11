#include "RTC.h"


void initRTC() {
  RTC -> PRLL = 0x7FFF; // Obtenir un période de 1 seconde
  RTC -> PRLH = 0xFFFF; // Le plus grand possible
}


int getTime() {
  return(RTC -> PRLH);
}

