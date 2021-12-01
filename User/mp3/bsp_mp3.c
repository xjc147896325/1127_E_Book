/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  jOKERII
  * @version V1.0
  * @date    2021-06-19
  * @brief   led应用函数接口
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
  * @brief  初始化控制LED的IO
  * @param  无
  * @retval 无
  */
void MP3_Usart_Init(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
			
	RCC_AHB1PeriphClockCmd(MP3_USART_RX_GPIO_CLK|MP3_USART_TX_GPIO_CLK,ENABLE);
	
	/* 使能 USART 时钟 */
	RCC_APB2PeriphClockCmd(MP3_USART_CLK, ENABLE);
	
	/* GPIO初始化 */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	/* 配置Tx引脚为复用功能  */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = MP3_USART_TX_PIN  ;  
	GPIO_Init(MP3_USART_TX_GPIO_PORT, &GPIO_InitStructure);
	
	/* 配置Rx引脚为复用功能 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = MP3_USART_RX_PIN;
	GPIO_Init(MP3_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
	/* 连接 PXx 到 USARTx_Tx*/
	GPIO_PinAFConfig(MP3_USART_RX_GPIO_PORT,MP3_USART_RX_SOURCE,MP3_USART_RX_AF);
	
	/*  连接 PXx 到 USARTx__Rx*/
	GPIO_PinAFConfig(MP3_USART_TX_GPIO_PORT,MP3_USART_TX_SOURCE,MP3_USART_TX_AF);
	
	/* 配置串MP3_USART 模式 */
	/* 波特率设置：MP3_USART_BAUDRATE */
	USART_InitStructure.USART_BaudRate = MP3_USART_BAUDRATE;
	/* 字长(数据位+校验位)：8 */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	/* 停止位：1个停止位 */
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	/* 校验位选择：不使用校验 */
	USART_InitStructure.USART_Parity = USART_Parity_No;
	/* 硬件流控制：不使用硬件流 */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	/* USART模式控制：同时使能接收和发送 */
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* 完成USART初始化配置 */
	USART_Init(MP3_USART, &USART_InitStructure); 
	
	
  /* 使能串口 */
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
