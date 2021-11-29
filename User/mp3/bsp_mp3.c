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

 /**
  * @brief  初始化控制LED的IO
  * @param  无
  * @retval 无
  */
void MP3_GPIO_Config(void)
{		
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*开启LED相关的GPIO外设时钟*/
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

	/*选择要控制的GPIO引脚*/														   
	GPIO_InitStructure.GPIO_Pin = MP3_CON1_PIN|MP3_CON2_PIN;	

	/*设置引脚模式为输出模式*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   

	/*设置引脚的输出类型为推挽输出*/
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

	/*设置引脚为上拉模式*/
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;


	/*设置引脚速率为2MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 

	/*调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO*/
	GPIO_Init(MP3_CON1_GPIO_PORT, &GPIO_InitStructure);	

	/*选择要控制的GPIO引脚*/															   
	GPIO_InitStructure.GPIO_Pin = MP3_CON3_PIN;	
	/*设置引脚为上拉模式*/
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	
	GPIO_Init(MP3_CON3_GPIO_PORT, &GPIO_InitStructure);	

	
	/*选择要控制的GPIO引脚*/															   
	GPIO_InitStructure.GPIO_Pin = MP3_IO0_PIN|
									MP3_IO1_PIN|
									MP3_IO2_PIN|
									MP3_IO3_PIN|
									MP3_IO4_PIN|
									MP3_IO5_PIN|
									MP3_IO6_PIN;
	/*设置引脚为上拉模式*/
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	GPIO_Init(MP3_IO0_GPIO_PORT, &GPIO_InitStructure);	

	MP3_CON1(1);
	MP3_CON2(1);
	MP3_CON3(0);
	MP3_IO0(1);
		
}
/*********************************************END OF FILE**********************/
