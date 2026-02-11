#include "Servo.h"
#include "DriverGPIO.h"
#include "PWM.h"
#include "Horloge.h"


void Servo_Moteur(int angle, TIM_TypeDef * Timer, int Channel) { // Controle du moteur
  int dutyCycle = (5* angle + 5*90)/90; // 5-10 % Duty Cycle
  Set_DutyCycle_PWM(Timer, Channel, dutyCycle);
}


void initServo(TIM_TypeDef * Timer, int Channel) { // Config du moteur servo
  if (Timer == TIM4) {
    Timer_Init(TIM4, 0xFFFF, 22); // Pour obtenir un période de 20 ms

    if (Channel == 3){
      MyGPIO_Init(GPIOB, 8, AltOut_Ppull); // Output push pull alternate
      MyTimer_PWM(TIM4, 3); // TIM4 CH3 pour PB8
    }
    else{
      //printf("Ce pilote n'existe pas");
    }
  }
  else{
    //printf("Ce pilote n'existe pas");
  }
}

