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

char song_start[] = {0xAA, 0x02, 0x00, 0xAC};
char song_cricle[]={0xAA, 0x18, 0x01, 0x01, 0xC4};
char song_cricle_5[]={0xAA, 0x19, 0x02, 0x00, 0x05, 0xCA};
char song0[]={0xAA, 0x08, 0x0B, 0x02, 0x2F, 0x30, 0x30, 0x30, 0x30, 0x31, 0x2A, 0x4D, 0x50, 0x33, 0xD9};
char song_noncricle[]={0xAA, 0x18, 0x01, 0x02, 0xC5};
char song1[]={0xAA, 0x08, 0x0B, 0x02, 0x2F, 0x30, 0x30, 0x30, 0x30, 0x32, 0x2A, 0x4D, 0x50, 0x33, 0xDA};
char song2[]={0xAA, 0x08, 0x0B, 0x02, 0x2F, 0x30, 0x30, 0x30, 0x30, 0x33, 0x2A, 0x4D, 0x50, 0x33, 0xDB};
char song3[]={0xAA, 0x08, 0x0B, 0x02, 0x2F, 0x30, 0x30, 0x30, 0x30, 0x34, 0x2A, 0x4D, 0x50, 0x33, 0xDC};
char song4[]={0xAA, 0x08, 0x0B, 0x02, 0x2F, 0x30, 0x30, 0x30, 0x30, 0x35, 0x2A, 0x4D, 0x50, 0x33, 0xDD};
char song5[]={0xAA, 0x08, 0x0B, 0x02, 0x2F, 0x30, 0x30, 0x30, 0x30, 0x36, 0x2A, 0x4D, 0x50, 0x33, 0xDE};
char song6[]={0xAA, 0x08, 0x0B, 0x02, 0x2F, 0x30, 0x30, 0x30, 0x30, 0x37, 0x2A, 0x4D, 0x50, 0x33, 0xDF};


 /**
  * @brief  ��ʼ������LED��IO
  * @param  ��
  * @retval ��
  */
void MP3_Usart_Init(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
			
	RCC_AHB1PeriphClockCmd(MP3_USART_RX_GPIO_CLK|MP3_USART_TX_GPIO_CLK,ENABLE);
	
	/* ʹ�� USART ʱ�� */
	RCC_APB2PeriphClockCmd(MP3_USART_CLK, ENABLE);
	
	/* GPIO��ʼ�� */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	/* ����Tx����Ϊ���ù���  */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = MP3_USART_TX_PIN  ;  
	GPIO_Init(MP3_USART_TX_GPIO_PORT, &GPIO_InitStructure);
	
	/* ����Rx����Ϊ���ù��� */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = MP3_USART_RX_PIN;
	GPIO_Init(MP3_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
	/* ���� PXx �� USARTx_Tx*/
	GPIO_PinAFConfig(MP3_USART_RX_GPIO_PORT,MP3_USART_RX_SOURCE,MP3_USART_RX_AF);
	
	/*  ���� PXx �� USARTx__Rx*/
	GPIO_PinAFConfig(MP3_USART_TX_GPIO_PORT,MP3_USART_TX_SOURCE,MP3_USART_TX_AF);
	
	/* ���ô�MP3_USART ģʽ */
	/* ���������ã�MP3_USART_BAUDRATE */
	USART_InitStructure.USART_BaudRate = MP3_USART_BAUDRATE;
	/* �ֳ�(����λ+У��λ)��8 */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	/* ֹͣλ��1��ֹͣλ */
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	/* У��λѡ�񣺲�ʹ��У�� */
	USART_InitStructure.USART_Parity = USART_Parity_No;
	/* Ӳ�������ƣ���ʹ��Ӳ���� */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	/* USARTģʽ���ƣ�ͬʱʹ�ܽ��պͷ��� */
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* ���USART��ʼ������ */
	USART_Init(MP3_USART, &USART_InitStructure); 
	
	
  /* ʹ�ܴ��� */
	USART_Cmd(MP3_USART, ENABLE);
}

void MP3_Control(uint16_t num)
{
	switch(num)	{
		case(0): {
			Usart_SendNumString(MP3_USART,song_cricle,5);
			Usart_SendNumString(MP3_USART,song_cricle_5,6);
			Usart_SendNumString(MP3_USART,song0,15);
			break;
		}
		case(1): {
			Usart_SendNumString(MP3_USART,song_noncricle,5);
			Usart_SendNumString(MP3_USART,song1,15);
			break;
		}
		case(2): {
			Usart_SendNumString(MP3_USART,song_noncricle,5);
			Usart_SendNumString(MP3_USART,song2,15);
			break;
		}
		case(3): {
			Usart_SendNumString(MP3_USART,song_noncricle,5);
			Usart_SendNumString(MP3_USART,song3,15);
			break;
		}
		case(4): {
			Usart_SendNumString(MP3_USART,song_noncricle,5);
			Usart_SendNumString(MP3_USART,song4,15);
			break;
		}
		case(5): {
			Usart_SendNumString(MP3_USART,song_noncricle,5);
			Usart_SendNumString(MP3_USART,song5,15);
			break;
		}
		case(6): {
			Usart_SendNumString(MP3_USART,song_noncricle,5);
			Usart_SendNumString(MP3_USART,song6,15);
			break;
		}
		default: {
			Usart_SendNumString(MP3_USART,song_cricle,5);
			Usart_SendNumString(MP3_USART,song_cricle_5,6);
			Usart_SendNumString(MP3_USART,song0,15);
		}
	}
	//Usart_SendString(MP3_USART,song_start);
	
	return ;
}

/*********************************************END OF FILE**********************/
