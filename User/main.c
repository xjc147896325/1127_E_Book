/**
  *********************************************************************
  * @file    main.c
  * @author  jOKERII
  * @version V1.0
  * @date    2021-11-27
  * @brief   
  *********************************************************************
  * @attention
  *
  *
  **********************************************************************
  */ 
 
/*
*************************************************************************
*                             包含的头文件
*************************************************************************
*/ 
/* FreeRTOS头文件 */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

/* 硬件bsp头文件 */
#include "bsp_led.h"
#include "bsp_mp3.h"
#include "bsp_infrared.h"
#include "bsp_debug_usart.h"
#include "bsp_key.h"
#include "bsp_timer.h"

/* 标准库头文件 */
#include <string.h>
/**************************** 任务句柄 ********************************/
/* 
 * 任务句柄是一个指针，用于指向一个任务，当任务创建好之后，它就具有了一个任务句柄
 * 以后我们要想操作这个任务都需要通过这个任务句柄，如果是自身的任务操作自己，那么
 * 这个句柄可以为NULL。
 */
static TaskHandle_t AppTaskCreate_Handle = NULL;/* 创建任务句柄 */
static TaskHandle_t LED_Task_Handle = NULL;/* LED任务句柄 */
static TaskHandle_t KEY_Task_Handle = NULL;/* KEY任务句柄 */
static TaskHandle_t Uart_Task_Handle = NULL;/* UART任务句柄 */
static TaskHandle_t Book_1_Task_Handle = NULL;/* Book_1任务句柄 */
static TaskHandle_t Book_2_Task_Handle = NULL;/* Book_2任务句柄 */
static TaskHandle_t Book_3_Task_Handle = NULL;/* Book_3任务句柄 */
static TaskHandle_t Book_4_Task_Handle = NULL;/* Book_4任务句柄 */

/********************************** 内核对象句柄 *********************************/
/*
 * 信号量，消息队列，事件标志组，软件定时器这些都属于内核的对象，要想使用这些内核
 * 对象，必须先创建，创建成功之后会返回一个相应的句柄。实际上就是一个指针，后续我
 * 们就可以通过这个句柄操作这些内核对象。
 *
 * 内核对象说白了就是一种全局的数据结构，通过这些数据结构我们可以实现任务间的通信，
 * 任务间的事件同步等各种功能。至于这些功能的实现我们是通过调用这些内核对象的函数
 * 来完成的
 * 
 */
SemaphoreHandle_t BinarySem_Handle =NULL;
SemaphoreHandle_t Book_1_BinarySem_Handle =NULL;
SemaphoreHandle_t Book_2_BinarySem_Handle =NULL;
SemaphoreHandle_t Book_3_BinarySem_Handle =NULL;
SemaphoreHandle_t Book_4_BinarySem_Handle =NULL;


/******************************* 全局变量声明 ************************************/
/*
 * 当我们在写应用程序的时候，可能需要用到一些全局变量。
 */
 
extern char Usart_Rx_Buf[USART_RBUFF_SIZE];

/*
*************************************************************************
*                             函数声明
*************************************************************************
*/
static void AppTaskCreate(void);/* 用于创建任务 */

static void LED_Task(void* pvParameters);/* Test_Task任务实现 */
static void KEY_Task(void* pvParameters);/* KEY_Task任务实现 */
static void Uart_Task(void* pvParameters);/* UART_Task任务实现 */
static void Book_1_Task(void* pvParameters);/* Book_1_Task任务实现 */
static void Book_2_Task(void* pvParameters);/* Book_2_Task任务实现 */
static void Book_3_Task(void* pvParameters);/* Book_3_Task任务实现 */
static void Book_4_Task(void* pvParameters);/* Book_4_Task任务实现 */

static void BSP_Init(void);/* 用于初始化板载相关资源 */

/*****************************************************************
  * @brief  主函数
  * @param  无
  * @retval 无
  * @note   第一步：开发板硬件初始化 
            第二步：创建APP应用任务
            第三步：启动FreeRTOS，开始多任务调度
  ****************************************************************/
int main(void)
{	
  BaseType_t xReturn = pdPASS;/* 定义一个创建信息返回值，默认为pdPASS */
  
  /* 开发板硬件初始化 */
  BSP_Init();
  
  printf("RTOS_Init\n\n");
  
   /* 创建AppTaskCreate任务 */
  xReturn = xTaskCreate((TaskFunction_t )AppTaskCreate,  /* 任务入口函数 */
                        (const char*    )"AppTaskCreate",/* 任务名字 */
                        (uint16_t       )512,  /* 任务栈大小 */
                        (void*          )NULL,/* 任务入口函数参数 */
                        (UBaseType_t    )1, /* 任务的优先级 */
                        (TaskHandle_t*  )&AppTaskCreate_Handle);/* 任务控制块指针 */ 
  /* 启动任务调度 */           
  if(pdPASS == xReturn)
    vTaskStartScheduler();   /* 启动任务，开启调度 */
  else
    return -1;  
  
  while(1);   /* 正常不会执行到这里 */    
}


/***********************************************************************
  * @ 函数名  ： AppTaskCreate
  * @ 功能说明： 为了方便管理，所有的任务创建函数都放在这个函数里面
  * @ 参数    ： 无  
  * @ 返回值  ： 无
  **********************************************************************/
static void AppTaskCreate(void)
{
	BaseType_t xReturn = pdPASS;/* 定义一个创建信息返回值，默认为pdPASS */
	
	taskENTER_CRITICAL();           //进入临界区
  
	  /* 创建 BinarySem */
	BinarySem_Handle = xSemaphoreCreateBinary();	 
	if(NULL != BinarySem_Handle)
	printf("BinarySem_Handle二值信号量创建成功!\r\n");
  
	  /* 创建 Book_2_BinarySem */
	Book_1_BinarySem_Handle = xSemaphoreCreateBinary();	 
	if(NULL != Book_1_BinarySem_Handle)
	printf("Book_1_BinarySem_Handle二值信号量创建成功!\r\n");  
  
	  /* 创建 Book_2_BinarySem */
	Book_2_BinarySem_Handle = xSemaphoreCreateBinary();	 
	if(NULL != Book_2_BinarySem_Handle)
	printf("Book_2_BinarySem_Handle二值信号量创建成功!\r\n");  
	
	  /* 创建 Book_3_BinarySem */
	Book_3_BinarySem_Handle = xSemaphoreCreateBinary();	 
	if(NULL != Book_3_BinarySem_Handle)
	printf("Book_3_BinarySem_Handle二值信号量创建成功!\r\n");	
	
	  /* 创建 Book_4_BinarySem */
	Book_4_BinarySem_Handle = xSemaphoreCreateBinary();	 
	if(NULL != Book_4_BinarySem_Handle)
	printf("Book_4_BinarySem_Handle二值信号量创建成功!\r\n");
	
	//给出二值信号量 ，发送接收到新数据标志，供前台程序查询
	xSemaphoreGive(Book_1_BinarySem_Handle);	//释放二值信号量

  /* 创建led_Task任务 */
	xReturn = xTaskCreate((TaskFunction_t )LED_Task, /* 任务入口函数 */
						(const char*    )"LED_Task",/* 任务名字 */
						(uint16_t       )512,   /* 任务栈大小 */
						(void*          )NULL,	/* 任务入口函数参数 */
						(UBaseType_t    )2,	    /* 任务的优先级 */
						(TaskHandle_t*  )&LED_Task_Handle);/* 任务控制块指针 */
	if(pdPASS == xReturn)
	printf("创建Test_Task任务成功!\r\n");
	
	/* 创建Uart_Task任务 */
	xReturn = xTaskCreate((TaskFunction_t )Uart_Task,  /* 任务入口函数 */
						(const char*    )"Uart_Task",/* 任务名字 */
						(uint16_t       )512,  /* 任务栈大小 */
						(void*          )NULL,/* 任务入口函数参数 */
						(UBaseType_t    )3, /* 任务的优先级 */
						(TaskHandle_t*  )&Uart_Task_Handle);/* 任务控制块指针 */ 
	if(pdPASS == xReturn)
	printf("创建Uart_Task任务成功!\r\n");
	
	/* 创建KEY_Task任务 */
	xReturn = xTaskCreate((TaskFunction_t )KEY_Task,  /* 任务入口函数 */
						(const char*    )"KEY_Task",/* 任务名字 */
						(uint16_t       )512,  /* 任务栈大小 */
						(void*          )NULL,/* 任务入口函数参数 */
						(UBaseType_t    )4, /* 任务的优先级 */
						(TaskHandle_t*  )&KEY_Task_Handle);/* 任务控制块指针 */ 
	if(pdPASS == xReturn)
	printf("创建KEY_Task任务成功!\r\n");
	
	/* 创建Book_1_Task任务 */
	xReturn = xTaskCreate((TaskFunction_t )Book_1_Task,  /* 任务入口函数 */
						(const char*    )"Book_1_Task",/* 任务名字 */
						(uint16_t       )512,  /* 任务栈大小 */
						(void*          )NULL,/* 任务入口函数参数 */
						(UBaseType_t    )5, /* 任务的优先级 */
						(TaskHandle_t*  )&Book_1_Task_Handle);/* 任务控制块指针 */ 
	if(pdPASS == xReturn)
	printf("创建Book_1_Task任务成功!\r\n");
	
	/* 创建Book_2_Task任务 */
	xReturn = xTaskCreate((TaskFunction_t )Book_2_Task,  /* 任务入口函数 */
						(const char*    )"Book_2_Task",/* 任务名字 */
						(uint16_t       )512,  /* 任务栈大小 */
						(void*          )NULL,/* 任务入口函数参数 */
						(UBaseType_t    )6, /* 任务的优先级 */
						(TaskHandle_t*  )&Book_2_Task_Handle);/* 任务控制块指针 */ 
	if(pdPASS == xReturn)
	printf("创建Book_2_Task任务成功!\r\n");
	
	/* 创建Book_3_Task任务 */
	xReturn = xTaskCreate((TaskFunction_t )Book_3_Task,  /* 任务入口函数 */
						(const char*    )"Book_3_Task",/* 任务名字 */
						(uint16_t       )512,  /* 任务栈大小 */
						(void*          )NULL,/* 任务入口函数参数 */
						(UBaseType_t    )7, /* 任务的优先级 */
						(TaskHandle_t*  )&Book_3_Task_Handle);/* 任务控制块指针 */ 
	if(pdPASS == xReturn)
	printf("创建Book_3_Task任务成功!\r\n");
	
	/* 创建Book_4_Task任务 */
	xReturn = xTaskCreate((TaskFunction_t )Book_4_Task,  /* 任务入口函数 */
						(const char*    )"Book_4_Task",/* 任务名字 */
						(uint16_t       )512,  /* 任务栈大小 */
						(void*          )NULL,/* 任务入口函数参数 */
						(UBaseType_t    )8, /* 任务的优先级 */
						(TaskHandle_t*  )&Book_4_Task_Handle);/* 任务控制块指针 */ 
	if(pdPASS == xReturn)
	printf("创建Book_4_Task任务成功!\r\n");
	

	vTaskDelete(AppTaskCreate_Handle); //删除AppTaskCreate任务

	taskEXIT_CRITICAL();            //退出临界区
}



/**********************************************************************
  * @ 函数名  ： LED_Task
  * @ 功能说明： LED_Task任务主体
  * @ 参数    ：   
  * @ 返回值  ： 无
  ********************************************************************/
static void LED_Task(void* parameter)
{	 
  while (1) {
    LED1_ON;
    //printf("Test_Task Running,LED1_ON\r\n");
    vTaskDelay(500);   /* 延时500个tick */
    
    LED1_OFF;     
    //printf("Test_Task Running,LED1_OFF\r\n");
    vTaskDelay(500);   /* 延时500个tick */
  }
}

/**********************************************************************
  * @ 函数名  ： Uart_Task
  * @ 功能说明： Uart_Task任务主体
  * @ 参数    ：   
  * @ 返回值  ： 无
  ********************************************************************/
static void Uart_Task(void* parameter)
{	
	BaseType_t xReturn = pdPASS;/* 定义一个创建信息返回值，默认为pdPASS */
	while (1) {
	//获取二值信号量 xSemaphore,没获取到则一直等待
		xReturn = xSemaphoreTake(BinarySem_Handle,/* 二值信号量句柄 */
							  portMAX_DELAY); /* 等待时间 */
		if(pdPASS == xReturn) {
			LED2_TOGGLE;
			printf("收到数据:%s\n",Usart_Rx_Buf);
			memset(Usart_Rx_Buf,0,USART_RBUFF_SIZE);/* 清零 */
		}
	}
}

/**********************************************************************
  * @ 函数名  ： KEY_Task
  * @ 功能说明： Test_Task任务主体
  * @ 参数    ：   
  * @ 返回值  ： 无
  ********************************************************************/
static void KEY_Task(void* parameter)
{	
	
	while (1) {
	//获取二值信号量 xSemaphore,没获取到则一直等待
		vTaskDelay(100);
	}
}

/**********************************************************************
  * @ 函数名  ： Book_1_Task
  * @ 功能说明： Book_1_Task任务主体
  * @ 参数    ：   
  * @ 返回值  ： 无
  ********************************************************************/
static void Book_1_Task(void* parameter)
{	
	BaseType_t xReturn = pdPASS;/* 定义一个创建信息返回值，默认为pdPASS */
	uint8_t flag = 1;

	while (1) {
		//获取二值信号量 Book_4_BinarySem_Handle,没获取到则一直等待
		xReturn = xSemaphoreTake(Book_1_BinarySem_Handle,/* 二值信号量句柄 */
							  portMAX_DELAY); /* 等待时间 */
		
		Light_OFF;


		if(pdPASS == xReturn) {
			Light0(0); //red

			while(flag) {
				if(!Infrared_Scan(INFRARED0_GPIO_PORT,INFRARED0_PIN)) {
					vTaskDelay(10);
					if(!Infrared_Scan(INFRARED0_GPIO_PORT,INFRARED0_PIN)) {
						flag = 0;
					}
				}
				else {
					if(!Infrared_Scan(INFRARED1_GPIO_PORT,INFRARED1_PIN)) {
						vTaskDelay(10);
						if(!Infrared_Scan(INFRARED1_GPIO_PORT,INFRARED1_PIN)) {
						MP3_Control(1);
						vTaskDelay(2000);
						MP3_Control(0);
						}
					}
				}
			}
			flag = 1;
			//do something
			Light0(1);
			Light2(0); // green
			MP3_Control(2);
			vTaskDelay(4500);
			MP3_Control(0);
			
			while(flag) {
				if(!Infrared_Scan(INFRARED1_GPIO_PORT,INFRARED1_PIN)) {
					vTaskDelay(10);
					if(!Infrared_Scan(INFRARED1_GPIO_PORT,INFRARED1_PIN)) {
						flag = 0;
					}
				}
				else {
					vTaskDelay(10);
				}
			}
			flag = 1;
			//do other thing
			MP3_Control(5);
			Set_Pwm1(TIM14, 50);
			vTaskDelay(900);
			Set_Pwm1(TIM14, 0);
			vTaskDelay(2600);
			MP3_Control(0);
			
			  //给出二值信号量 ，发送接收到新数据标志，供前台程序查询
			xSemaphoreGive(Book_2_BinarySem_Handle);	//释放二值信号量
			  //给出二值信号量 ，发送接收到新数据标志，供前台程序查询
			xSemaphoreGive(Book_1_BinarySem_Handle);	//释放二值信号量

			vTaskDelay(100);
		}
	}
}

/**********************************************************************
  * @ 函数名  ： Book_2_Task
  * @ 功能说明： Book_2_Task任务主体
  * @ 参数    ：   
  * @ 返回值  ： 无
  ********************************************************************/
static void Book_2_Task(void* parameter)
{	
	BaseType_t xReturn = pdPASS;/* 定义一个创建信息返回值，默认为pdPASS */
	uint8_t flag = 1;

	while (1) {
		//获取二值信号量 Book_2_BinarySem_Handle,没获取到则一直等待
		xReturn = xSemaphoreTake(Book_2_BinarySem_Handle,/* 二值信号量句柄 */
							  portMAX_DELAY); /* 等待时间 */

		xReturn &= xSemaphoreTake(Book_1_BinarySem_Handle,/* 二值信号量句柄 */
							  portMAX_DELAY); /* 等待时间 */

		if(pdPASS == xReturn) {
			while(flag) {
				if(!Infrared_Scan(INFRARED2_GPIO_PORT,INFRARED2_PIN)) {
					vTaskDelay(10);
					if(!Infrared_Scan(INFRARED2_GPIO_PORT,INFRARED2_PIN)) {
						flag = 0;
					}
				}
				else {
					vTaskDelay(10);
				}
			}
			flag = 1;
			//do something
			MP3_Control(3);
			vTaskDelay(3000);
			MP3_Control(0);
			Light1(0);//red
			
			while(flag) {
				if(!Infrared_Scan(INFRARED3_GPIO_PORT,INFRARED3_PIN)) {
					vTaskDelay(10);
					if(!Infrared_Scan(INFRARED3_GPIO_PORT,INFRARED3_PIN)) {
						flag = 0;
					}
				}
				else {
					vTaskDelay(10);
				}
			}
			flag = 1;
			while(flag) {
				if(!Infrared_Scan(INFRARED4_GPIO_PORT,INFRARED4_PIN)) {
					vTaskDelay(10);
					if(!Infrared_Scan(INFRARED4_GPIO_PORT,INFRARED4_PIN)) {
						flag = 0;
					}
				}
				else {
					vTaskDelay(10);
				}
			}
			flag = 1;
			while(flag) {
				if(!Infrared_Scan(INFRARED5_GPIO_PORT,INFRARED5_PIN)) {
					vTaskDelay(10);
					if(!Infrared_Scan(INFRARED5_GPIO_PORT,INFRARED5_PIN)) {
						flag = 0;
					}
				}
				else {
					vTaskDelay(10);
				}
			}
			flag = 1;
			//do other thing
			Light1(1);
			Light3(0);//green
			MP3_Control(3);			
			Set_Pwm1(TIM4, 50);
			vTaskDelay(900);
			Set_Pwm1(TIM4, 0);

			vTaskDelay(2100);
			MP3_Control(0);
			
			  //给出二值信号量 ，发送接收到新数据标志，供前台程序查询
			xSemaphoreGive(Book_3_BinarySem_Handle);	//释放二值信号量
			  //给出二值信号量 ，发送接收到新数据标志，供前台程序查询
			xSemaphoreGive(Book_2_BinarySem_Handle);	//释放二值信号量
			  //给出二值信号量 ，发送接收到新数据标志，供前台程序查询
			xSemaphoreGive(Book_1_BinarySem_Handle);	//释放二值信号量
		
			vTaskDelay(100);

		}
	}
}

/**********************************************************************
  * @ 函数名  ： Book_3_Task
  * @ 功能说明： Book_3_Task任务主体
  * @ 参数    ：   
  * @ 返回值  ： 无
  ********************************************************************/
static void Book_3_Task(void* parameter)
{	
	BaseType_t xReturn = pdPASS;/* 定义一个创建信息返回值，默认为pdPASS */
	uint8_t flag = 1;



	while (1) {
	//获取二值信号量 Book_3_BinarySem_Handle,没获取到则一直等待
		xReturn = xSemaphoreTake(Book_3_BinarySem_Handle,/* 二值信号量句柄 */
							  portMAX_DELAY); /* 等待时间 */
		xReturn &= xSemaphoreTake(Book_2_BinarySem_Handle,/* 二值信号量句柄 */
								  portMAX_DELAY); /* 等待时间 */

		xReturn &= xSemaphoreTake(Book_1_BinarySem_Handle,/* 二值信号量句柄 */
								  portMAX_DELAY); /* 等待时间 */
	
		if(pdPASS == xReturn) {
			while(flag) {
				if(!Infrared_Scan(INFRARED6_GPIO_PORT,INFRARED6_PIN)) {
					vTaskDelay(10);
					if(!Infrared_Scan(INFRARED6_GPIO_PORT,INFRARED6_PIN)) {
						flag = 0;
					}
				}
				else {
					vTaskDelay(10);
				}
			}
			flag = 1;
			//do something
			MP3_Control(6);			
			Set_Pwm2(TIM4, 50);
			vTaskDelay(900);
			Set_Pwm2(TIM14, 0);

			vTaskDelay(5100);
			MP3_Control(0);
			
			  //给出二值信号量 ，发送接收到新数据标志，供前台程序查询
			xSemaphoreGive(Book_4_BinarySem_Handle);	//释放二值信号量
			  //给出二值信号量 ，发送接收到新数据标志，供前台程序查询
			xSemaphoreGive(Book_3_BinarySem_Handle);	//释放二值信号量
			  //给出二值信号量 ，发送接收到新数据标志，供前台程序查询
			xSemaphoreGive(Book_2_BinarySem_Handle);	//释放二值信号量
			  //给出二值信号量 ，发送接收到新数据标志，供前台程序查询
			xSemaphoreGive(Book_1_BinarySem_Handle);	//释放二值信号量
			

			vTaskDelay(100);

		}
	}
}

/**********************************************************************
  * @ 函数名  ： Book_4_Task
  * @ 功能说明： Book_4_Task任务主体
  * @ 参数    ：   
  * @ 返回值  ： 无
  ********************************************************************/
static void Book_4_Task(void* parameter)
{	
	BaseType_t xReturn = pdPASS;/* 定义一个创建信息返回值，默认为pdPASS */
	uint8_t flag = 1;
	while (1)
	{
		//获取二值信号量 Book_4_BinarySem_Handle,没获取到则一直等待
		xReturn = xSemaphoreTake(Book_4_BinarySem_Handle,/* 二值信号量句柄 */
								  portMAX_DELAY); /* 等待时间 */
		xReturn = xSemaphoreTake(Book_3_BinarySem_Handle,/* 二值信号量句柄 */
								  portMAX_DELAY); /* 等待时间 */
		xReturn &= xSemaphoreTake(Book_2_BinarySem_Handle,/* 二值信号量句柄 */
								  portMAX_DELAY); /* 等待时间 */
		xReturn &= xSemaphoreTake(Book_1_BinarySem_Handle,/* 二值信号量句柄 */
								  portMAX_DELAY); /* 等待时间 */


		if(pdPASS == xReturn) {
			while(flag) {
				if(!Infrared_Scan(INFRARED7_GPIO_PORT,INFRARED7_PIN)) {
					vTaskDelay(10);
					if(!Infrared_Scan(INFRARED7_GPIO_PORT,INFRARED7_PIN)) {
						flag = 0;
					}
				}
				else {
					vTaskDelay(10);
				}
			}
			flag = 1;
			//do something
			MP3_Control(4);
			vTaskDelay(6000);
			MP3_Control(0);
//			Light4(0);//red


			while(flag) {
				if(!Infrared_Scan(INFRARED8_GPIO_PORT,INFRARED8_PIN)) {
					vTaskDelay(10);
					if(!Infrared_Scan(INFRARED8_GPIO_PORT,INFRARED8_PIN)) {
						flag = 0;
					}
				}
				else {
					vTaskDelay(10);
				}
			}
			flag = 1;
			//do other thing
			Light4(0);//green
			MP3_Control(3);
			Set_Pwm3(TIM4, 50);
			vTaskDelay(900);
			Set_Pwm3(TIM4, 0);
			vTaskDelay(2100);
			MP3_Control(0);

			while(flag) {
				if(!Infrared_Scan(INFRARED9_GPIO_PORT,INFRARED9_PIN)) {
					vTaskDelay(10);
					if(!Infrared_Scan(INFRARED9_GPIO_PORT,INFRARED9_PIN)) {
						flag = 0;
					}
				}
				else {
					vTaskDelay(10);
				}
			}
			flag = 1;	
			Set_Pwm1(TIM14, 250);
			Set_Pwm1(TIM4, 250);
			Set_Pwm2(TIM4, 250);
			Set_Pwm3(TIM4, 250);
			vTaskDelay(900);
			Set_Pwm1(TIM14, 0);
			Set_Pwm1(TIM4, 0);
			Set_Pwm2(TIM4, 0);
			Set_Pwm3(TIM4, 0);
//			  //给出二值信号量 ，发送接收到新数据标志，供前台程序查询
//			xSemaphoreGive(Book_4_BinarySem_Handle);	//释放二值信号量
//			  //给出二值信号量 ，发送接收到新数据标志，供前台程序查询
//			xSemaphoreGive(Book_3_BinarySem_Handle);	//释放二值信号量
//			  //给出二值信号量 ，发送接收到新数据标志，供前台程序查询
//			xSemaphoreGive(Book_2_BinarySem_Handle);	//释放二值信号量
			  //给出二值信号量 ，发送接收到新数据标志，供前台程序查询
			xSemaphoreGive(Book_1_BinarySem_Handle);	//释放二值信号量
			

			vTaskDelay(100);

		}
	}
}

/***********************************************************************
  * @ 函数名  ： BSP_Init
  * @ 功能说明： 板级外设初始化，所有板子上的初始化均可放在这个函数里面
  * @ 参数    ：   
  * @ 返回值  ： 无
  *********************************************************************/
static void BSP_Init(void)
{
	uint16_t i = 1000;
	/*
	 * STM32中断优先级分组为4，即4bit都用来表示抢占优先级，范围为：0~15
	 * 优先级分组只需要分组一次即可，以后如果有其他的任务需要用到中断，
	 * 都统一用这个优先级分组，千万不要再分组，切忌。
	 */
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
	
	/* LED 初始化 */
	LED_GPIO_Config();	
	
	/* LED 初始化 */
	MP3_Usart_Init();
	while(i--);
	MP3_Control(0);
	
	/* DMA初始化	*/
	USARTx_DMA_Config();
	/* 串口初始化	*/
	Debug_USART_Config();
  
	/* infrared初始化	*/
	Infrared_GPIO_Config();
	
	TIM14_PWM_Init(1999, 839, GPIOA, GPIO_Pin_7); //tim14 ch1
	TIM4_PWM_Init(1999, 839, GPIOB, GPIO_Pin_7); //tim4 ch2
	TIM4_PWM_Init(1999, 839, GPIOB, GPIO_Pin_8); //tim4 ch3
	TIM4_PWM_Init(1999, 839, GPIOB, GPIO_Pin_9); //tim4 ch4

//	Set_Pwm1(TIM14, 250);
//	Set_Pwm2(TIM4, 250);
//	Set_Pwm3(TIM4, 250);
//	Set_Pwm4(TIM4, 250);
//	while(1);   /* 正常不会执行到这里 */    

	Light0(0);
	Light1(0);
	Light2(0);
	Light3(0);
	Light4(0);
	
	printf("Init finish\r\n");
}

/********************************END OF FILE****************************/
