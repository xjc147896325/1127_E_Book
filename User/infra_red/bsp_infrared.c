/**
  ******************************************************************************
  * @file    bsp_infrared.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ����Ӧ��bsp��ɨ��ģʽ��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F407 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
  
#include "bsp_Infrared.h" 

/**
  * @brief  ����Infrared�õ���I/O��
  * @param  ��
  * @retval ��
  */
void Infrared_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*��������GPIO�ڵ�ʱ��*/
	RCC_AHB1PeriphClockCmd(INFRARED0_GPIO_CLK|
							INFRARED1_GPIO_CLK|
							INFRARED2_GPIO_CLK|
							INFRARED3_GPIO_CLK|
							INFRARED4_GPIO_CLK|
							INFRARED5_GPIO_CLK|
							INFRARED6_GPIO_CLK|
							INFRARED7_GPIO_CLK|
							INFRARED8_GPIO_CLK|
							INFRARED9_GPIO_CLK,
							ENABLE);
	
  /*ѡ�񰴼�������*/
	GPIO_InitStructure.GPIO_Pin = INFRARED0_PIN|
									INFRARED1_PIN|
									INFRARED2_PIN|
									INFRARED3_PIN|
									INFRARED4_PIN|
									INFRARED5_PIN|
									INFRARED6_PIN|
									INFRARED7_PIN|
									INFRARED8_PIN|
									INFRARED9_PIN; 
  
  /*��������Ϊ����ģʽ*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 
  
  /*������������*/
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	
  /*ʹ������Ľṹ���ʼ������*/
	GPIO_Init(INFRARED0_GPIO_PORT, &GPIO_InitStructure);   
	GPIO_Init(INFRARED1_GPIO_PORT, &GPIO_InitStructure);   
	GPIO_Init(INFRARED2_GPIO_PORT, &GPIO_InitStructure);   
	GPIO_Init(INFRARED3_GPIO_PORT, &GPIO_InitStructure);   
	GPIO_Init(INFRARED4_GPIO_PORT, &GPIO_InitStructure);   
	GPIO_Init(INFRARED5_GPIO_PORT, &GPIO_InitStructure);   
	GPIO_Init(INFRARED6_GPIO_PORT, &GPIO_InitStructure);   
	GPIO_Init(INFRARED7_GPIO_PORT, &GPIO_InitStructure);   
	GPIO_Init(INFRARED8_GPIO_PORT, &GPIO_InitStructure);   
	GPIO_Init(INFRARED9_GPIO_PORT, &GPIO_InitStructure);  
}

/**
  * @brief   ����Ƿ���Infrared����   
  *	@param 	GPIOx:����Ķ˿�, x�����ǣ�A...K�� 
	*	@param 	GPIO_PIN:����Ķ˿�λ�� ������GPIO_PIN_x��x������0...15��
  * @retval  Infrared��״̬
  *		@arg INFRARED_ON:Infrared����
  *		@arg INFRARED_OFF:Infraredû����
  */
uint8_t Infrared_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{			
	/*����Ƿ���Infrared���� */
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == INFRARED_ON )  
	{	 
		return 	INFRARED_ON;	 
	}
	else
		return INFRARED_OFF;
}
/*********************************************END OF FILE**********************/
