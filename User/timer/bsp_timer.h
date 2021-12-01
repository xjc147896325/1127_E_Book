/**
  ******************************************************************************
  * @file    timer.h
  * @author  jOKERII
  * @version v1.0
  * @date    20-11-08
  * @brief   Í·ÎÄ¼þ
						 

  ******************************************************************************
  */
	
#ifndef __BSP_TIMER_H
#define __BSP_TIMER_H

#include "stm32f4xx.h"



void TIM4_PWM_Init(uint16_t arr, uint16_t psc, GPIO_TypeDef *GPIOx, uint16_t pinx);
void TIM14_PWM_Init(uint16_t arr, uint16_t psc, GPIO_TypeDef *GPIOx, uint16_t pinx);

void TIM1_PWM_Init(uint16_t arr,uint16_t psc);

void Set_Pwm1(TIM_TypeDef *timx, uint16_t setvalue);
void Set_Pwm2(TIM_TypeDef *timx, uint16_t setvalue);

#endif

