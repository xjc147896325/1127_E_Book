/**
  ******************************************************************************
  * @file    drv_time.c
  * @author  xjc
  * @version v1.0
  * @date    20-09-17
  * @brief   �жϺ�����it��
			 TIM2_Init(uint16_t arr, uint16_t psc)
			 TIM3_Init(uint16_t arr, uint16_t psc)
			 TIM4_PWM_Init(uint16_t arr, uint16_t psc, GPIO_TypeDef *GPIOx, uint16_t pinx)
			 
  ******************************************************************************
  */
#include "bsp_timer.h"


void TIM14_PWM_Init(uint16_t arr, uint16_t psc, GPIO_TypeDef *GPIOx, uint16_t pinx)
{	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef        TIM_OCInitStructure;	
	uint8_t pin_source;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14,ENABLE);  	//TIM14ʱ��ʹ��
	
	switch(pinx)
	{
		case(GPIO_Pin_0):
		{
			pin_source = GPIO_PinSource0;
			break;
		}
		case(GPIO_Pin_1):
		{
			pin_source = GPIO_PinSource1;
			break;
		}
		case(GPIO_Pin_2):
		{
			pin_source = GPIO_PinSource2;
			break;
		}
		case(GPIO_Pin_3):
		{
			pin_source = GPIO_PinSource3;
			break;
		}
		case(GPIO_Pin_4):
		{
			pin_source = GPIO_PinSource4;
			break;
		}
		case(GPIO_Pin_5):
		{
			pin_source = GPIO_PinSource5;
			break;
		}
		case(GPIO_Pin_6):
		{
			pin_source = GPIO_PinSource6;
			break;
		}
		case(GPIO_Pin_7):
		{
			pin_source = GPIO_PinSource7;
			break;
		}
		case(GPIO_Pin_8):
		{
			pin_source = GPIO_PinSource8;
			break;
		}
		case(GPIO_Pin_9):
		{
			pin_source = GPIO_PinSource9;
			break;
		}
		case(GPIO_Pin_10):
		{
			pin_source = GPIO_PinSource10;
			break;
		}
		case(GPIO_Pin_11):
		{
			pin_source = GPIO_PinSource11;
			break;
		}
		case(GPIO_Pin_12):
		{
			pin_source = GPIO_PinSource12;
			break;
		}
		case(GPIO_Pin_13):
		{
			pin_source = GPIO_PinSource13;
			break;
		}
		case(GPIO_Pin_14):
		{
			pin_source = GPIO_PinSource14;
			break;
		}
		case(GPIO_Pin_15):
		{
			pin_source = GPIO_PinSource15;
			break;
		}
		default:
		{
;
		}
	}
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*����LED��ص�GPIO����ʱ��*/
	RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOA, ENABLE); 

	/*ѡ��Ҫ���Ƶ�GPIO����*/															   
	GPIO_InitStructure.GPIO_Pin = pinx;	

	/*��������ģʽΪ���ģʽ*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;   

	/*�������ŵ��������Ϊ�������*/
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

	/*��������Ϊ����ģʽ*/
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	/*������������Ϊ2MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 

	/*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/
	GPIO_Init(GPIOx, &GPIO_InitStructure);	



	GPIO_PinAFConfig(GPIOx,pin_source,GPIO_AF_TIM14);              //GPIO����Ϊ��ʱ��9	
	
//	GPIO_Format_Init(GPIOx, pinx, GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
	
	TIM_TimeBaseStructure.TIM_Prescaler     = psc;                //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period        = arr;                //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM14,&TIM_TimeBaseStructure);                //��ʼ����ʱ��e
	
	//��ʼ��TIM4 Channel1 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM1;        //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High ;    //�������:TIM����Ƚϼ��Ե�
	
	TIM_OC1Init(TIM14, &TIM_OCInitStructure);                      //����Tָ���Ĳ�����ʼ������TIM4OC1
	TIM_OC1PreloadConfig(TIM14, TIM_OCPreload_Enable);             //ʹ��TIM14��CCR1�ϵ�Ԥװ�ؼĴ���

	TIM_ARRPreloadConfig(TIM14,ENABLE);//ARPEʹ�� 	
	
	TIM_Cmd(TIM14, ENABLE);  //ʹ��TIM4

}  



void Set_Pwm1(TIM_TypeDef *timx, uint16_t setvalue)
{
	 TIM_SetCompare1(timx,setvalue);
}

void Set_Pwm2(TIM_TypeDef *timx, uint16_t setvalue)
{
	 TIM_SetCompare2(timx,setvalue);
}















