/**
  ******************************************************************************
  * @file    bsp_infrared.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   按键应用bsp（扫描模式）
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火  STM32 F407 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
  
#include "bsp_Infrared.h" 

/**
  * @brief  配置Infrared用到的I/O口
  * @param  无
  * @retval 无
  */
void Infrared_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*开启按键GPIO口的时钟*/
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
	
  /*选择按键的引脚*/
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
  
  /*设置引脚为输入模式*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 
  
  /*设置引脚下拉*/
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	
  /*使用上面的结构体初始化按键*/
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
  * @brief   检测是否有Infrared触发   
  *	@param 	GPIOx:具体的端口, x可以是（A...K） 
	*	@param 	GPIO_PIN:具体的端口位， 可以是GPIO_PIN_x（x可以是0...15）
  * @retval  Infrared的状态
  *		@arg INFRARED_ON:Infrared触发
  *		@arg INFRARED_OFF:Infrared没触发
  */
uint8_t Infrared_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{			
	/*检测是否有Infrared触发 */
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == INFRARED_ON )  
	{	 
		return 	INFRARED_ON;	 
	}
	else
		return INFRARED_OFF;
}
/*********************************************END OF FILE**********************/
