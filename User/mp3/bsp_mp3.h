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
#include "bsp_debug_usart.h"
#include <stdio.h>

//引脚定义
/*******************************************************/
#define MP3_USART                             USART6

/* 不同的串口挂载的总线不一样，时钟使能函数也不一样，移植时要注意
* 串口1和6是      RCC_APB2PeriphClockCmd
* 串口2/3/4/5是    RCC_APB1PeriphClockCmd
*/


#define MP3_USART_CLK                         RCC_APB2Periph_USART6
#define MP3_USART_BAUDRATE                    9600  //串口波特率

#define MP3_USART_RX_GPIO_PORT                GPIOC
#define MP3_USART_RX_GPIO_CLK                 RCC_AHB1Periph_GPIOC
#define MP3_USART_RX_PIN                      GPIO_Pin_7
#define MP3_USART_RX_AF                       GPIO_AF_USART6
#define MP3_USART_RX_SOURCE                   GPIO_PinSource7

#define MP3_USART_TX_GPIO_PORT                GPIOC
#define MP3_USART_TX_GPIO_CLK                 RCC_AHB1Periph_GPIOC
#define MP3_USART_TX_PIN                      GPIO_Pin_6
#define MP3_USART_TX_AF                       GPIO_AF_USART6
#define MP3_USART_TX_SOURCE                   GPIO_PinSource6

#define MP3_USART_IRQHandler                  USART6_IRQHandler
#define MP3_USART_IRQ                 		  USART6_IRQn
/************************************************************/


void MP3_Usart_Init(void);
void MP3_Control(uint16_t num);

#endif /* __BSP_MP3_H */
