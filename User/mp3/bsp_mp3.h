/**
  ******************************************************************************
  * @file    bsp_mp3.c
  * @author  jOKERII
  * @version V1.1 for SB
  * @date    2021-11-29
  * @brief   led应用函数接口
  ******************************************************************************
  * @attention
  *

  ******************************************************************************
  */
#ifndef __BSP_MP3_H
#define	__BSP_MP3_H

#include "stm32f4xx.h"

//引脚定义
/*******************************************************/
//CON1
#define MP3_CON1_PIN                  GPIO_Pin_4                 
#define MP3_CON1_GPIO_PORT            GPIOA                      
#define MP3_CON1_GPIO_CLK             RCC_AHB1Periph_GPIOA

//CON2
#define MP3_CON2_PIN                  GPIO_Pin_5                 
#define MP3_CON2_GPIO_PORT            GPIOA                      
#define MP3_CON2_GPIO_CLK             RCC_AHB1Periph_GPIOA

//CON3
#define MP3_CON3_PIN                  GPIO_Pin_6                
#define MP3_CON3_GPIO_PORT            GPIOA                       
#define MP3_CON3_GPIO_CLK             RCC_AHB1Periph_GPIOA

//IO0
#define MP3_IO0_PIN                  GPIO_Pin_7                 
#define MP3_IO0_GPIO_PORT            GPIOE                      
#define MP3_IO0_GPIO_CLK             RCC_AHB1Periph_GPIOE
			
//IO1
#define MP3_IO1_PIN                  GPIO_Pin_8                 
#define MP3_IO1_GPIO_PORT            GPIOE                      
#define MP3_IO1_GPIO_CLK             RCC_AHB1Periph_GPIOE
			
//IO2      
#define MP3_IO2_PIN                  GPIO_Pin_9                 
#define MP3_IO2_GPIO_PORT            GPIOE                      
#define MP3_IO2_GPIO_CLK             RCC_AHB1Periph_GPIOE
			
//IO3      
#define MP3_IO3_PIN                  GPIO_Pin_10                
#define MP3_IO3_GPIO_PORT            GPIOE                       
#define MP3_IO3_GPIO_CLK             RCC_AHB1Periph_GPIOE

//IO4
#define MP3_IO4_PIN                  GPIO_Pin_11                 
#define MP3_IO4_GPIO_PORT            GPIOE                      
#define MP3_IO4_GPIO_CLK             RCC_AHB1Periph_GPIOE
			
//IO5
#define MP3_IO5_PIN                  GPIO_Pin_12                 
#define MP3_IO5_GPIO_PORT            GPIOE                      
#define MP3_IO5_GPIO_CLK             RCC_AHB1Periph_GPIOE
			
//IO6      
#define MP3_IO6_PIN                  GPIO_Pin_13                 
#define MP3_IO6_GPIO_PORT            GPIOE                      
#define MP3_IO6_GPIO_CLK             RCC_AHB1Periph_GPIOE
			
//IO7      
#define MP3_IO7_PIN                  GPIO_Pin_14                
#define MP3_IO7_GPIO_PORT            GPIOE                       
#define MP3_IO7_GPIO_CLK             RCC_AHB1Periph_GPIOE


/************************************************************/




/* 带参宏，可以像内联函数一样使用 */
#define MP3_CON1(a)	if (a)	\
					GPIO_SetBits(MP3_CON1_GPIO_PORT,MP3_CON1_PIN);\
					else		\
					GPIO_ResetBits(MP3_CON1_GPIO_PORT,MP3_CON1_PIN)
					
#define MP3_CON2(a)	if (a)	\
					GPIO_SetBits(MP3_CON2_GPIO_PORT,MP3_CON2_PIN);\
					else		\
					GPIO_ResetBits(MP3_CON2_GPIO_PORT,MP3_CON2_PIN)
					
#define MP3_CON3(a)	if (a)	\
					GPIO_SetBits(MP3_CON3_GPIO_PORT,MP3_CON3_PIN);\
					else		\
					GPIO_ResetBits(MP3_CON3_GPIO_PORT,MP3_CON3_PIN)
					
#define MP3_IO0(a)	if (a)	\
					GPIO_SetBits(MP3_IO0_GPIO_PORT,MP3_IO0_PIN);\
					else		\
					GPIO_ResetBits(MP3_IO0_GPIO_PORT,MP3_IO0_PIN)
					
#define MP3_IO1(a)	if (a)	\
					GPIO_SetBits(MP3_IO1_GPIO_PORT,MP3_IO1_PIN);\
					else		\
					GPIO_ResetBits(MP3_IO1_GPIO_PORT,MP3_IO1_PIN)
					
#define MP3_IO2(a)	if (a)	\
					GPIO_SetBits(MP3_IO2_GPIO_PORT,MP3_IO2_PIN);\
					else		\
					GPIO_ResetBits(MP3_IO2_GPIO_PORT,MP3_IO2_PIN)
					
#define MP3_IO3(a)	if (a)	\
					GPIO_SetBits(MP3_IO3_GPIO_PORT,MP3_IO3_PIN);\
					else		\
					GPIO_ResetBits(MP3_IO3_GPIO_PORT,MP3_IO3_PIN)
					
#define MP3_IO4(a)	if (a)	\
					GPIO_SetBits(MP3_IO4_GPIO_PORT,MP3_IO4_PIN);\
					else		\
					GPIO_ResetBits(MP3_IO4_GPIO_PORT,MP3_IO4_PIN)
					
#define MP3_IO5(a)	if (a)	\
					GPIO_SetBits(MP3_IO5_GPIO_PORT,MP3_IO5_PIN);\
					else		\
					GPIO_ResetBits(MP3_IO5_GPIO_PORT,MP3_IO5_PIN)
					
#define MP3_IO6(a)	if (a)	\
					GPIO_SetBits(MP3_IO6_GPIO_PORT,MP3_IO6_PIN);\
					else		\
					GPIO_ResetBits(MP3_IO6_GPIO_PORT,MP3_IO6_PIN)
					
#define MP3_IO7(a)	if (a)	\
					GPIO_SetBits(MP3_IO7_GPIO_PORT,MP3_IO7_PIN);\
					else		\
					GPIO_ResetBits(MP3_IO7_GPIO_PORT,MP3_IO7_PIN)
					


void MP3_GPIO_Config(void);

#endif /* __BSP_MP3_H */
