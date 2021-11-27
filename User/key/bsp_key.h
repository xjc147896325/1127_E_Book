#ifndef __KEY_H
#define	__KEY_H

#include "stm32f4xx.h"

//���Ŷ���
/*******************************************************/
#define KEY1_PIN                  GPIO_Pin_2                 
#define KEY1_GPIO_PORT            GPIOE                      
#define KEY1_GPIO_CLK             RCC_AHB1Periph_GPIOE

#define KEY2_PIN                  GPIO_Pin_3                 
#define KEY2_GPIO_PORT            GPIOE                      
#define KEY2_GPIO_CLK             RCC_AHB1Periph_GPIOE

#define KEY3_PIN                  GPIO_Pin_4                 
#define KEY3_GPIO_PORT            GPIOE                      
#define KEY3_GPIO_CLK             RCC_AHB1Periph_GPIOE

#define KEY0_PIN                  GPIO_Pin_0                 
#define KEY0_GPIO_PORT            GPIOA                      
#define KEY0_GPIO_CLK             RCC_AHB1Periph_GPIOA
/*******************************************************/

 /** �������±��ú�
	* ��������Ϊ�ߵ�ƽ������ KEY_ON=1�� KEY_OFF=0
	* ����������Ϊ�͵�ƽ���Ѻ����ó�KEY_ON=0 ��KEY_OFF=1 ����
	*/
#define KEY_ON	1
#define KEY_OFF	0

void Key_GPIO_Config(void);
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin);

#endif /* __LED_H */

