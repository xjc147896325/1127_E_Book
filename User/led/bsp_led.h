/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  jOKERII
  * @version V1.1 for SB
  * @date    2021-11-20
  * @brief   led应用函数接口
  ******************************************************************************
  * @attention
  *

  ******************************************************************************
  */
#ifndef __BSP_LED_H
#define	__BSP_LED_H

#include "stm32f4xx.h"

//引脚定义
/*******************************************************/
//R 红色灯
#define LED1_PIN                  GPIO_Pin_2                 
#define LED1_GPIO_PORT            GPIOC                      
#define LED1_GPIO_CLK             RCC_AHB1Periph_GPIOC

//Y 黄色灯
#define LED2_PIN                  GPIO_Pin_3                 
#define LED2_GPIO_PORT            GPIOC                      
#define LED2_GPIO_CLK             RCC_AHB1Periph_GPIOC

//B 蓝色灯
#define LED3_PIN                  GPIO_Pin_1                
#define LED3_GPIO_PORT            GPIOC                       
#define LED3_GPIO_CLK             RCC_AHB1Periph_GPIOC

//W 白色灯
#define LED4_PIN                  GPIO_Pin_0                
#define LED4_GPIO_PORT            GPIOC                       
#define LED4_GPIO_CLK             RCC_AHB1Periph_GPIOC

//灯0 red
#define Light1_PIN                  GPIO_Pin_9                
#define Light1_GPIO_PORT            GPIOC                      
#define Light1_GPIO_CLK             RCC_AHB1Periph_GPIOC

//灯1 green
#define Light2_PIN                  GPIO_Pin_10                
#define Light2_GPIO_PORT            GPIOC                      
#define Light2_GPIO_CLK             RCC_AHB1Periph_GPIOC

//灯2 green
#define Light3_PIN                  GPIO_Pin_11               
#define Light3_GPIO_PORT            GPIOC                       
#define Light3_GPIO_CLK             RCC_AHB1Periph_GPIOC

//灯3 green
#define Light4_PIN                  GPIO_Pin_12              
#define Light4_GPIO_PORT            GPIOC                       
#define Light4_GPIO_CLK             RCC_AHB1Periph_GPIOC

//灯4 red
#define Light0_PIN                  GPIO_Pin_8                
#define Light0_GPIO_PORT            GPIOC                       
#define Light0_GPIO_CLK             RCC_AHB1Periph_GPIOC

/************************************************************/


/** 控制LED灯亮灭的宏，
	* LED低电平亮，设置ON=0，OFF=1
	* 若LED高电平亮，把宏设置成ON=1 ，OFF=0 即可
	*/
#define ON  0
#define OFF 1

/* 带参宏，可以像内联函数一样使用 */
#define LED1(a)	if (a)	\
					GPIO_SetBits(LED1_GPIO_PORT,LED1_PIN);\
					else		\
					GPIO_ResetBits(LED1_GPIO_PORT,LED1_PIN)

#define LED2(a)	if (a)	\
					GPIO_SetBits(LED2_GPIO_PORT,LED2_PIN);\
					else		\
					GPIO_ResetBits(LED2_GPIO_PORT,LED2_PIN)

#define LED3(a)	if (a)	\
					GPIO_SetBits(LED3_GPIO_PORT,LED3_PIN);\
					else		\
					GPIO_ResetBits(LED3_GPIO_PORT,LED3_PIN)

#define LED4(a)	if (a)	\
					GPIO_SetBits(LED4_GPIO_PORT,LED4_PIN);\
					else		\
					GPIO_ResetBits(LED4_GPIO_PORT,LED4_PIN)


/* 带参宏，可以像内联函数一样使用 */
#define Light0(a)	if (a)	\
					GPIO_SetBits(Light0_GPIO_PORT,Light0_PIN);\
					else		\
					GPIO_ResetBits(Light0_GPIO_PORT,Light0_PIN)

#define Light1(a)	if (a)	\
					GPIO_SetBits(Light1_GPIO_PORT,Light1_PIN);\
					else		\
					GPIO_ResetBits(Light1_GPIO_PORT,Light1_PIN)

#define Light2(a)	if (a)	\
					GPIO_SetBits(Light2_GPIO_PORT,Light2_PIN);\
					else		\
					GPIO_ResetBits(Light2_GPIO_PORT,Light2_PIN)

#define Light3(a)	if (a)	\
					GPIO_SetBits(Light3_GPIO_PORT,Light3_PIN);\
					else		\
					GPIO_ResetBits(Light3_GPIO_PORT,Light3_PIN)

#define Light4(a)	if (a)	\
					GPIO_SetBits(Light4_GPIO_PORT,Light4_PIN);\
					else		\
					GPIO_ResetBits(Light4_GPIO_PORT,Light4_PIN)


/* 直接操作寄存器的方法控制IO */
#define	digitalHi(p,i)			 {p->BSRRL=i;}		//设置为高电平
#define digitalLo(p,i)			 {p->BSRRH=i;}		//输出低电平
#define digitalToggle(p,i)	 	 {p->ODR ^=i;}		//输出反转状态

/* 定义控制IO的宏 */
#define LED1_TOGGLE		digitalToggle(LED1_GPIO_PORT,LED1_PIN)
#define LED1_OFF		digitalHi(LED1_GPIO_PORT,LED1_PIN)
#define LED1_ON			digitalLo(LED1_GPIO_PORT,LED1_PIN)

#define LED2_TOGGLE		digitalToggle(LED2_GPIO_PORT,LED2_PIN)
#define LED2_OFF		digitalHi(LED2_GPIO_PORT,LED2_PIN)
#define LED2_ON			digitalLo(LED2_GPIO_PORT,LED2_PIN)

#define LED3_TOGGLE		digitalToggle(LED3_GPIO_PORT,LED3_PIN)
#define LED3_OFF		digitalHi(LED3_GPIO_PORT,LED3_PIN)
#define LED3_ON			digitalLo(LED3_GPIO_PORT,LED3_PIN)

#define LED4_TOGGLE		digitalToggle(LED3_GPIO_PORT,LED4_PIN)
#define LED4_OFF		digitalHi(LED3_GPIO_PORT,LED4_PIN)
#define LED4_ON			digitalLo(LED3_GPIO_PORT,LED4_PIN)

#define LED_OFF 		LED1_OFF;LED2_OFF;LED3_OFF;LED4_OFF
#define Light_OFF 		Light0(1);Light1(1);Light2(1);Light3(1);Light4(1);
#define LED_ON	 		LED1_ON;LED2_ON;LED3_ON;LED4_ON

void LED_GPIO_Config(void);

#endif /* __LED_H */
