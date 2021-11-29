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
  
#include "bsp_mp3.h"   

 /**
  * @brief  ��ʼ������LED��IO
  * @param  ��
  * @retval ��
  */
void MP3_GPIO_Config(void)
{		
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*����LED��ص�GPIO����ʱ��*/
	RCC_AHB1PeriphClockCmd ( MP3_CON1_GPIO_CLK|
						   MP3_CON2_GPIO_CLK|
						   MP3_CON3_GPIO_CLK, ENABLE); 

	RCC_AHB1PeriphClockCmd ( MP3_IO0_GPIO_CLK|
						   MP3_IO2_GPIO_CLK|
						   MP3_IO3_GPIO_CLK|
						   MP3_IO4_GPIO_CLK|
						   MP3_IO5_GPIO_CLK|
						   MP3_IO6_GPIO_CLK|
						   MP3_IO1_GPIO_CLK, ENABLE); 

	/*ѡ��Ҫ���Ƶ�GPIO����*/														   
	GPIO_InitStructure.GPIO_Pin = MP3_CON1_PIN|MP3_CON2_PIN;	

	/*��������ģʽΪ���ģʽ*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   

	/*�������ŵ��������Ϊ�������*/
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

	/*��������Ϊ����ģʽ*/
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;


	/*������������Ϊ2MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 

	/*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/
	GPIO_Init(MP3_CON1_GPIO_PORT, &GPIO_InitStructure);	

	/*ѡ��Ҫ���Ƶ�GPIO����*/															   
	GPIO_InitStructure.GPIO_Pin = MP3_CON3_PIN;	
	/*��������Ϊ����ģʽ*/
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	
	GPIO_Init(MP3_CON3_GPIO_PORT, &GPIO_InitStructure);	

	
	/*ѡ��Ҫ���Ƶ�GPIO����*/															   
	GPIO_InitStructure.GPIO_Pin = MP3_IO0_PIN|
									MP3_IO1_PIN|
									MP3_IO2_PIN|
									MP3_IO3_PIN|
									MP3_IO4_PIN|
									MP3_IO5_PIN|
									MP3_IO6_PIN;
	/*��������Ϊ����ģʽ*/
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	GPIO_Init(MP3_IO0_GPIO_PORT, &GPIO_InitStructure);	

	MP3_CON1(1);
	MP3_CON2(1);
	MP3_CON3(0);
	MP3_IO0(1);
		
}
/*********************************************END OF FILE**********************/
