#ifndef __BSP_INFRARED_H
#define	__BSP_INFRARED_H

#include "stm32f4xx.h"

//引脚定义
/*******************************************************/
#define INFRARED0_PIN                  GPIO_Pin_1                 
#define INFRARED0_GPIO_PORT            GPIOD                      
#define INFRARED0_GPIO_CLK             RCC_AHB1Periph_GPIOD

#define INFRARED1_PIN                  GPIO_Pin_2                 
#define INFRARED1_GPIO_PORT            GPIOD                     
#define INFRARED1_GPIO_CLK             RCC_AHB1Periph_GPIOD

#define INFRARED2_PIN                  GPIO_Pin_3                 
#define INFRARED2_GPIO_PORT            GPIOD                      
#define INFRARED2_GPIO_CLK             RCC_AHB1Periph_GPIOD

#define INFRARED3_PIN                  GPIO_Pin_4                 
#define INFRARED3_GPIO_PORT            GPIOD                      
#define INFRARED3_GPIO_CLK             RCC_AHB1Periph_GPIOD

#define INFRARED4_PIN                  GPIO_Pin_5                 
#define INFRARED4_GPIO_PORT            GPIOD                      
#define INFRARED4_GPIO_CLK             RCC_AHB1Periph_GPIOD

#define INFRARED5_PIN                  GPIO_Pin_6                 
#define INFRARED5_GPIO_PORT            GPIOD                      
#define INFRARED5_GPIO_CLK             RCC_AHB1Periph_GPIOD

#define INFRARED6_PIN                  GPIO_Pin_7                 
#define INFRARED6_GPIO_PORT            GPIOD                      
#define INFRARED6_GPIO_CLK             RCC_AHB1Periph_GPIOD

#define INFRARED7_PIN                  GPIO_Pin_7                 
#define INFRARED7_GPIO_PORT            GPIOE                      
#define INFRARED7_GPIO_CLK             RCC_AHB1Periph_GPIOE

#define INFRARED8_PIN                  GPIO_Pin_8                 
#define INFRARED8_GPIO_PORT            GPIOE                      
#define INFRARED8_GPIO_CLK             RCC_AHB1Periph_GPIOE

#define INFRARED9_PIN                  GPIO_Pin_9                 
#define INFRARED9_GPIO_PORT            GPIOE                      
#define INFRARED9_GPIO_CLK             RCC_AHB1Periph_GPIOE
/*******************************************************/

 /** 按键按下标置宏
	* 按键按下为高电平，设置 KEY_ON=1， KEY_OFF=0
	* 若按键按下为低电平，把宏设置成KEY_ON=0 ，KEY_OFF=1 即可
	*/
#define INFRARED_ON		1
#define INFRARED_OFF	0

void Infrared_GPIO_Config(void);
uint8_t Infrared_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin);

#endif /* __LED_H */

