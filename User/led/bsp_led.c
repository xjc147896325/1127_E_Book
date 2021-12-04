/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  jOKERII
  * @version V1.0
  * @date    2021-06-19
  * @brief   ledӦ�ú����ӿ�
  ******************************************************************************
  * @attention
  *

  ******************************************************************************
  */
  
#include "bsp_led.h"   

 /**
  * @brief  ��ʼ������LED��IO
  * @param  ��
  * @retval ��
  */
void LED_GPIO_Config(void)
{		
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*����LED��ص�GPIO����ʱ��*/
	RCC_AHB1PeriphClockCmd ( LED1_GPIO_CLK|
						   LED2_GPIO_CLK|
						   LED3_GPIO_CLK|
						   LED4_GPIO_CLK|
						   Light0_GPIO_CLK|
						   Light1_GPIO_CLK|
						   Light2_GPIO_CLK|
						   Light3_GPIO_CLK|
						   Light4_GPIO_CLK, ENABLE); 

	/*ѡ��Ҫ���Ƶ�GPIO����*/															   
	GPIO_InitStructure.GPIO_Pin = LED1_PIN;	

	/*��������ģʽΪ���ģʽ*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   

	/*�������ŵ��������Ϊ�������*/
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

	/*��������Ϊ����ģʽ*/
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	/*������������Ϊ2MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 

	/*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/
	GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);	

	/*ѡ��Ҫ���Ƶ�GPIO����*/															   
	GPIO_InitStructure.GPIO_Pin = LED2_PIN;	
	GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStructure);	

	/*ѡ��Ҫ���Ƶ�GPIO����*/															   
	GPIO_InitStructure.GPIO_Pin = LED3_PIN;	
	GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStructure);	

	/*ѡ��Ҫ���Ƶ�GPIO����*/															   
	GPIO_InitStructure.GPIO_Pin = LED4_PIN;	
	GPIO_Init(LED4_GPIO_PORT, &GPIO_InitStructure);	


	/*ѡ��Ҫ���Ƶ�GPIO����*/															   
	GPIO_InitStructure.GPIO_Pin = Light0_PIN;	
	GPIO_Init(Light0_GPIO_PORT, &GPIO_InitStructure);	

	/*ѡ��Ҫ���Ƶ�GPIO����*/															   
	GPIO_InitStructure.GPIO_Pin = Light1_PIN;	
	GPIO_Init(Light1_GPIO_PORT, &GPIO_InitStructure);	

	/*ѡ��Ҫ���Ƶ�GPIO����*/															   
	GPIO_InitStructure.GPIO_Pin = Light2_PIN;	
	GPIO_Init(Light2_GPIO_PORT, &GPIO_InitStructure);	


	/*ѡ��Ҫ���Ƶ�GPIO����*/															   
	GPIO_InitStructure.GPIO_Pin = Light3_PIN;	
	GPIO_Init(Light3_GPIO_PORT, &GPIO_InitStructure);	

	/*ѡ��Ҫ���Ƶ�GPIO����*/															   
	GPIO_InitStructure.GPIO_Pin = Light4_PIN;	
	GPIO_Init(Light4_GPIO_PORT, &GPIO_InitStructure);	




	/*�ر�LED��*/
	LED_OFF;		
	Light_OFF;		
}
/*********************************************END OF FILE**********************/
